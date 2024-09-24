#include "pch.hpp"
#include <SysInfo/disk.hpp>
#include <SysInfo/utf8.hpp>
#include <SysInfo/misc.hpp>
#include <winioctl.h>

#pragma comment(lib, "setupapi.lib")

namespace SysInfo::Disk {
    using Disk = DiskInfo::Disk;

    Disk::Disk(
        const std::string& letter,
        const std::string& volumeName,
        const std::string& fileSystem,
        const std::string& serial,
        const Type& type,
        const std::uint64_t freeBytes,
        const std::uint64_t totalBytes,
        const std::uint64_t freeBytesAvailable
    ) noexcept : m_letter(letter),
        m_volumeName(volumeName),
        m_fileSystem(fileSystem),
        m_serial(serial),
        m_type(type),
        m_freeBytes(freeBytes),
        m_totalBytes(totalBytes),
        m_freeBytesAvailable(freeBytesAvailable)
    {}

    const std::string& Disk::GetLetter() const noexcept { return m_letter; }
    const std::string& Disk::GetVolumeName() const noexcept { return m_volumeName; }
    const std::string& Disk::GetFileSystem() const noexcept { return m_fileSystem; }
    const std::string& Disk::GetSerial() const noexcept { return m_serial; }
    const Disk::Type& Disk::GetType() const noexcept { return m_type; }
    const std::uint64_t& Disk::GetFreeBytes() const noexcept { return m_freeBytes; }
    const std::uint64_t& Disk::GetTotalBytes() const noexcept { return m_totalBytes; }
    const std::uint64_t& Disk::GetFreeBytesAvailable() const noexcept { return m_freeBytesAvailable; }

    std::string Disk::DiskTypeToString(const Disk::Type& type) noexcept {
        switch (type) {
            case Disk::Type::UNKNOWN:
            default:
                return "UNKNOWN";
            case Disk::Type::INVALID:
                return "INVALID";
            case Disk::Type::REMOVABLE:
                return "REMOVABLE";
            case Disk::Type::HARDDRIVE:
                return "HARDDRIVE";
            case Disk::Type::NETWORK:
                return "NETWORK";
            case Disk::Type::CDROM:
                return "CDROM";
            case Disk::Type::RAMDISK:
                return "RAMDISK";
        }
    }

    DiskInfo::DiskInfo(
        std::vector<DiskInfo::Disk> disks
    ) noexcept : m_disks(disks) {}

    const std::vector<DiskInfo::Disk>& DiskInfo::GetDisks() const noexcept {
        return m_disks;
    }

    EXPORT std::future<DiskInfo> GetDiskInfoFuture() noexcept {
#ifdef SYSINFO_USE_CACHE
        static DiskInfo diskInfo;
#endif
        return std::async(std::launch::async, []() -> DiskInfo {
#ifdef SYSINFO_USE_CACHE
            if (diskInfo.IsInitialized())
                return diskInfo;
#endif
            std::vector<Disk> disks;

            DWORD drivesBitmask = GetLogicalDrives();
            if (!drivesBitmask)
                return { disks };

            for (auto i = 0; i < 26; i++) {
                if (!(drivesBitmask & (1 << i)))
                    continue;

                wchar_t driveLetter[4] = L"A:\\";
                driveLetter[0] = L'A' + i;

                Disk::Type type;

                switch (GetDriveTypeW(driveLetter)) {
                    case DRIVE_UNKNOWN:
                    default:
                        type = Disk::Type::UNKNOWN;
                        break;
                    case DRIVE_NO_ROOT_DIR:
                        type = Disk::Type::INVALID;
                        break;
                    case DRIVE_REMOVABLE:
                        type = Disk::Type::REMOVABLE;
                        break;
                    case DRIVE_FIXED:
                        type = Disk::Type::HARDDRIVE;
                        break;
                    case DRIVE_REMOTE:
                        type = Disk::Type::NETWORK;
                        break;
                    case DRIVE_CDROM:
                        type = Disk::Type::CDROM;
                        break;
                    case DRIVE_RAMDISK:
                        type = Disk::Type::RAMDISK;
                        break;
                }
                std::array<wchar_t, MAX_PATH + 1> volumeName{ 0 };
                std::array<wchar_t, MAX_PATH + 1> fileSystem{ 0 };

                DWORD maxComponentLength = 0;
                DWORD fileSystemFlags = 0;

                auto prevErr = GetErrorMode();
                SetErrorMode(SEM_FAILCRITICALERRORS);

                GetVolumeInformationW(
                    driveLetter, volumeName.data(), static_cast<DWORD>(volumeName.size()),
                    nullptr, &maxComponentLength, &fileSystemFlags,
                    fileSystem.data(), static_cast<DWORD>(fileSystem.size())
                );

                SetErrorMode(prevErr);

                ULARGE_INTEGER freeBytesAvailable = { 0 };
                ULARGE_INTEGER totalBytes = { 0 };
                ULARGE_INTEGER totalFreeBytes = { 0 };

                GetDiskFreeSpaceExW(driveLetter, &freeBytesAvailable,
                    &totalBytes, &totalFreeBytes);

                std::wstring devicePath = L"\\\\.\\PhysicalDrive" + std::to_wstring(i);
                HANDLE driveHandle = CreateFileW(devicePath.c_str(), 0,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr, OPEN_EXISTING, 0, nullptr
                );

                std::string vendorName;
                std::string productName;
                std::string productRevision;
                std::string serial;

                if (driveHandle != INVALID_HANDLE_VALUE) {
                    STORAGE_PROPERTY_QUERY query{};
                    query.PropertyId = StorageDeviceProperty;
                    query.QueryType = PropertyStandardQuery;

                    char buffer[10000];
                    DWORD bytesReturned;

                    if (DeviceIoControl(driveHandle, IOCTL_STORAGE_QUERY_PROPERTY,
                        &query, sizeof(query), &buffer, sizeof(buffer), &bytesReturned, nullptr
                    )) {
                        auto deviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(buffer);
                        if (deviceDescriptor->Version >= sizeof(STORAGE_DEVICE_DESCRIPTOR)) {
                            auto vendorIdOffset = deviceDescriptor->VendorIdOffset;
                            auto productIdOffset = deviceDescriptor->ProductIdOffset;
                            auto productRevisionOffset = deviceDescriptor->ProductRevisionOffset;
                            auto serialNumberOffset = deviceDescriptor->SerialNumberOffset;

                            if (vendorIdOffset)
                                vendorName = reinterpret_cast<char*>(&buffer[vendorIdOffset]);
                            if (productIdOffset)
                                productName = reinterpret_cast<char*>(&buffer[productIdOffset]);
                            if (productRevisionOffset)
                                productRevision = reinterpret_cast<char*>(&buffer[productRevisionOffset]);
                            if (serialNumberOffset)
                                serial = reinterpret_cast<char*>(&buffer[serialNumberOffset]);
                        }
                    }

                    CloseHandle(driveHandle);
                }

                Core::Misc::ltrim(vendorName);
                Core::Misc::ltrim(productName);
                Core::Misc::ltrim(productRevision);
                Core::Misc::ltrim(serial);

                Core::Misc::rtrim(vendorName);
                Core::Misc::rtrim(productName);
                Core::Misc::rtrim(productRevision);
                Core::Misc::rtrim(serial);

                disks.emplace_back(
                    UTF8::ToUTF8(driveLetter),
                    UTF8::ToUTF8(volumeName.data()),
                    UTF8::ToUTF8(fileSystem.data()),
                    serial,
                    type,
                    totalFreeBytes.QuadPart,
                    totalBytes.QuadPart,
                    freeBytesAvailable.QuadPart
                );
            }

#ifndef SYSINFO_USE_CACHE
            auto
#endif
            diskInfo = DiskInfo(disks);
            return diskInfo;
        });
    }

    EXPORT FUTURE(DiskInfo) GetDiskInfo() noexcept {
#ifdef SYSINFO_USE_FUTURE
        return GetDiskInfoFuture();
#else
        auto info = GetDiskInfoFuture();
        info.wait();
        return info.get();
#endif
    }
}