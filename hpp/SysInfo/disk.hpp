#pragma once

#include <SysInfo/dll.hpp>

namespace SysInfo::Disk {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT DiskInfo : public Core::StructInit {
    public:
        class EXPORT Disk : public Core::StructInit {
        public:
            enum class Type {
                UNKNOWN,
                INVALID,
                REMOVABLE,
                HARDDRIVE,
                NETWORK,
                CDROM,
                RAMDISK
            };

            Disk(
                const std::string& letter,
                const std::string& volumeName,
                const std::string& fileSystem,
                const std::string& serial,
                const Type& type,
                const std::uint64_t freeBytes,
                const std::uint64_t totalBytes,
                const std::uint64_t freeBytesAvailable
            ) noexcept;

            const std::string& GetLetter() const noexcept;
            const std::string& GetVolumeName() const noexcept;
            const std::string& GetFileSystem() const noexcept;
            const std::string& GetSerial() const noexcept;
            const Type& GetType() const noexcept;
            const std::uint64_t& GetFreeBytes() const noexcept;
            const std::uint64_t& GetTotalBytes() const noexcept;
            const std::uint64_t& GetFreeBytesAvailable() const noexcept;

            static std::string DiskTypeToString(const Type& type) noexcept;
        protected:
            const std::string m_letter;
            const std::string m_volumeName;
            const std::string m_fileSystem;
            const std::string m_serial;
            const Type m_type;
            const std::uint64_t m_freeBytes;
            const std::uint64_t m_totalBytes;
            const std::uint64_t m_freeBytesAvailable;
        };

        DiskInfo (
            std::vector<Disk> disks
        ) noexcept;

        const std::vector<Disk>& GetDisks() const noexcept;
    protected:
        const std::vector<Disk> m_disks;
    };
#pragma warning(pop)

    EXPORT std::future<DiskInfo> GetDiskInfoFuture() noexcept;
    EXPORT FUTURE(DiskInfo) GetDiskInfo() noexcept;
}