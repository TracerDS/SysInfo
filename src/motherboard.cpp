#include "pch.hpp"
#include <SysInfo/motherboard.hpp>
#include <SysInfo/misc.hpp>
#include <format>

namespace SysInfo::Motherboard {
    struct RawSMBIOSData {
        BYTE Used20CallingMethod;
        BYTE MajorVersion;
        BYTE MinorVersion;
        BYTE Revision;
        DWORD Length;
        BYTE SMBIOSTableData[0xBB3];
    };

    using BIOSCharacteristics = MotherboardInfo::BIOSCharacteristics;
    using BIOSCharacteristicsExt = MotherboardInfo::BIOSCharacteristicsExt;
    using WakeUpType = MotherboardInfo::WakeUpType;
    using BaseboardFlags = MotherboardInfo::BaseboardFlags;
    using BaseboardType = MotherboardInfo::BaseboardType;

    BIOSCharacteristics::BIOSCharacteristics(const std::uint64_t& value) noexcept {
        _reserved = value & 0x1;
        _unknown = value & 0x2;
        charsSupported = value & 0x4;
        ISA = value & 0x8;
        MCA = value & 0x10;
        EISA = value & 0x20;
        PCI = value & 0x40;
        PCMCIA_CARD = value & 0x80;
        PAP = value & 0x100;
        APM = value & 0x200;
        upgradeable = value & 0x400;
        shadowing = value & 0x800;
        VLVESA = value & 0x1000;
        ESCD = value & 0x2000;
        cdBoot = value & 0x4000;
        selectableBoot = value & 0x8000;
        biosRom = value & 0x10000;
        PCMCIA_BOOT = value & 0x20000;
        EDD = value & 0x40000;
        floppyNEC9800 = value & 0x80000;
        floppyToshiba = value & 0x100000;
        floppy360 = value & 0x200000;
        floppy1228 = value & 0x400000;
        floppy720 = value & 0x800000;
        floppy2949 = value & 0x1000000;
        printScreen = value & 0x2000000;
        keyboard8042 = value & 0x4000000;
        serialServices = value & 0x8000000;
        printerServices = value & 0x10000000;
        CGA_MONO = value & 0x2000000;
        NEC_PC98 = value & 0x4000000;
        _reservedBIOSVendor = static_cast<std::uint16_t>((value & 0xFFFF00000000) >> 32);
        _reservedSystemVendor = static_cast<std::uint16_t>((value & 0xFFFF000000000000) >> 48);
    }
    BIOSCharacteristics::operator std::uint64_t() const noexcept {
        std::uint64_t value = 0;
        value |= (static_cast<std::uint64_t>(_reserved) & 0x1);
        value |= (static_cast<std::uint64_t>(_unknown) & 0x1) << 1;
        value |= (static_cast<std::uint64_t>(charsSupported) & 0x1) << 2;
        value |= (static_cast<std::uint64_t>(ISA) & 0x1) << 3;
        value |= (static_cast<std::uint64_t>(MCA) & 0x1) << 4;
        value |= (static_cast<std::uint64_t>(EISA) & 0x1) << 5;
        value |= (static_cast<std::uint64_t>(PCI) & 0x1) << 6;
        value |= (static_cast<std::uint64_t>(PCMCIA_CARD) & 0x1) << 7;
        value |= (static_cast<std::uint64_t>(PAP) & 0x1) << 8;
        value |= (static_cast<std::uint64_t>(APM) & 0x1) << 9;
        value |= (static_cast<std::uint64_t>(upgradeable) & 0x1) << 10;
        value |= (static_cast<std::uint64_t>(shadowing) & 0x1) << 11;
        value |= (static_cast<std::uint64_t>(VLVESA) & 0x1) << 12;
        value |= (static_cast<std::uint64_t>(ESCD) & 0x1) << 13;
        value |= (static_cast<std::uint64_t>(cdBoot) & 0x1) << 14;
        value |= (static_cast<std::uint64_t>(selectableBoot) & 0x1) << 15;
        value |= (static_cast<std::uint64_t>(biosRom) & 0x1) << 16;
        value |= (static_cast<std::uint64_t>(PCMCIA_BOOT) & 0x1) << 17;
        value |= (static_cast<std::uint64_t>(EDD) & 0x1) << 18;
        value |= (static_cast<std::uint64_t>(floppyNEC9800) & 0x1) << 19;
        value |= (static_cast<std::uint64_t>(floppyToshiba) & 0x1) << 20;
        value |= (static_cast<std::uint64_t>(floppy360) & 0x1) << 21;
        value |= (static_cast<std::uint64_t>(floppy1228) & 0x1) << 22;
        value |= (static_cast<std::uint64_t>(floppy720) & 0x1) << 23;
        value |= (static_cast<std::uint64_t>(floppy2949) & 0x1) << 24;
        value |= (static_cast<std::uint64_t>(printScreen) & 0x1) << 25;
        value |= (static_cast<std::uint64_t>(keyboard8042) & 0x1) << 26;
        value |= (static_cast<std::uint64_t>(serialServices) & 0x1) << 27;
        value |= (static_cast<std::uint64_t>(printerServices) & 0x1) << 28;
        value |= (static_cast<std::uint64_t>(CGA_MONO) & 0x1) << 29;
        value |= (static_cast<std::uint64_t>(NEC_PC98) & 0x1) << 30;
        value |= (static_cast<std::uint64_t>(_reservedBIOSVendor) & 0xFFFF) << 32;
        value |= (static_cast<std::uint64_t>(_reservedSystemVendor) & 0xFFFF) << 48;
        return value;
    }

    BIOSCharacteristicsExt::BIOSCharacteristicsExt(const std::uint16_t& value) noexcept {
        ACPI = value & 0x1;
        legacyUSB = value & 0x2;
        AGP = value & 0x4;
        I2OBOOT = value & 0x8;
        LS120SuperDisk = value & 0x10;
        ATAPI = value & 0x20;
        boot1394 = value & 0x40;
        smartBattery = value & 0x80;
        biosBoot = value & 0x100;
        networkBoot = value & 0x200;
        targetedContent = value & 0x400;
        UEFI = value & 0x800;
        virtualMachine = value & 0x1000;
        _reserved = value & 0xE000;
    }
    BIOSCharacteristicsExt::operator std::uint16_t() const noexcept {
        std::uint16_t value = 0;
        value |= (ACPI & 0x1);
        value |= (legacyUSB & 0x1) << 1;
        value |= (AGP & 0x1) << 2;
        value |= (I2OBOOT & 0x1) << 3;
        value |= (LS120SuperDisk & 0x1) << 4;
        value |= (ATAPI & 0x1) << 5;
        value |= (boot1394 & 0x1) << 6;
        value |= (smartBattery & 0x1) << 7;
        value |= (biosBoot & 0x1) << 8;
        value |= (networkBoot & 0x1) << 9;
        value |= (targetedContent & 0x1) << 10;
        value |= (UEFI & 0x1) << 11;
        value |= (virtualMachine & 0x1) << 12;
        value |= (_reserved & 0x7) << 13;
        return value;
    }

    BaseboardFlags::BaseboardFlags(const std::uint8_t& value) noexcept {
        motherboard = value & 0x1;
        requireAux = value & 0x2;
        removable = value & 0x4;
        replaceable = value & 0x8;
        hotSwappable = value & 0x10;
        _reserved = value & 0xE0;
    }
    BaseboardFlags::operator std::uint8_t() const noexcept {
        std::uint8_t value = 0;
        value |= (motherboard & 0x1) << 1;
        value |= (requireAux & 0x1) << 2;
        value |= (removable & 0x1) << 3;
        value |= (replaceable & 0x1) << 4;
        value |= (hotSwappable & 0x1) << 5;
        value |= (_reserved & 0x7) << 6;
        return value;
    }

    std::string MotherboardInfo::BaseboardTypeToString(const BaseboardType& type) noexcept {
        switch (type) {
            case BaseboardType::UNKNOWN:
            default:
                return "UNKNOWN";
            case BaseboardType::OTHER:
                return "OTHER";
            case BaseboardType::SERVER_BLADE:
                return "SERVER_BLADE";
            case BaseboardType::CONNECTIVITY_SWITCH:
                return "CONNECTIVITY_SWITCH";
            case BaseboardType::SYSTEM_MANAGEMENT_MODULE:
                return "SYSTEM_MANAGEMENT_MODULE";
            case BaseboardType::PROCESSOR_MODULE:
                return "PROCESSOR_MODULE";
            case BaseboardType::IO_MODULE:
                return "IO_MODULE";
            case BaseboardType::MEMORY_MODULE:
                return "MEMORY_MODULE";
            case BaseboardType::DAUGHTER_BOARD:
                return "DAUGHTER_BOARD";
            case BaseboardType::MOTHERBOARD:
                return "MOTHERBOARD";
            case BaseboardType::PROCESSOR_MEMORY_MODULE:
                return "PROCESSOR_MEMORY_MODULE";
            case BaseboardType::PROCESSOR_IO_MODULE:
                return "PROCESSOR_IO_MODULE";
            case BaseboardType::INTERCONNECT_BOARD:
                return "INTERCONNECT_BOARD";
        }
    }
    std::string MotherboardInfo::WakeUpTypeToString(const WakeUpType& type) noexcept {
        switch (type) {
            case WakeUpType::RESERVED:
                return "RESERVED";
            case WakeUpType::OTHER:
                return "OTHER";
            case WakeUpType::UNKNOWN:
            default:
                return "UNKNOWN";
            case WakeUpType::APM_TIMER:
                return "APM_TIMER";
            case WakeUpType::MODEM_RING:
                return "MODEM_RING";
            case WakeUpType::LAN_REMOTE:
                return "LAN_REMOTE";
            case WakeUpType::POWER_SWITCH:
                return "POWER_SWITCH";
            case WakeUpType::PCI_PME:
                return "PCI_PME";
            case WakeUpType::AC_POWER_RESTORED:
                return "AC_POWER_RESTORED";
        }
    }

    MotherboardInfo::MotherboardInfo() noexcept {}
    MotherboardInfo::MotherboardInfo(
        const BIOSCharacteristics& biosChars,
        const BIOSCharacteristicsExt& biosCharsExt,
        const std::pair<std::uint8_t, std::uint8_t>& systemBiosVersion,
        const std::pair<std::uint8_t, std::uint8_t>& ecfVersion,
        const std::uint16_t& biosAddress,
        const std::uint32_t& biosRomSize,
        const std::string& uuid,
        const std::string& vendor,
        const std::string& biosVersion,
        const std::string& releaseDate,
        const std::string& manufacturer,
        const std::string& productName,
        const std::string& version,
        const std::string& serial,
        const WakeUpType& wakeUpType,
        const std::string& SKUNumber,
        const std::string& family,
        const BaseboardFlags& featureFlags,
        const BaseboardType& boardType
    ) noexcept :
        m_biosChars(biosChars),
        m_biosCharsExt(biosCharsExt),
        m_systemBiosVersion(systemBiosVersion),
        m_ecfVersion(ecfVersion),
        m_biosAddress(biosAddress),
        m_romSize(biosRomSize),
        m_uuid(uuid),
        m_vendor(vendor),
        m_biosVersion(biosVersion),
        m_releaseDate(releaseDate),
        m_manufacturer(manufacturer),
        m_productName(productName),
        m_version(version),
        m_serial(serial),
        m_wakeUpType(wakeUpType),
        m_SKUNumber(SKUNumber),
        m_family(family),
        m_featureFlags(featureFlags),
        m_boardType(boardType)
    {
        m_initialized = true;
    }

    const BIOSCharacteristics& MotherboardInfo::GetBIOSCharacteristics()
        const noexcept { return m_biosChars; }
    const BIOSCharacteristicsExt& MotherboardInfo::GetBIOSCharacteristicsExt()
        const noexcept { return m_biosCharsExt; }
    const std::pair<std::uint8_t, std::uint8_t>& MotherboardInfo::GetSystemBIOSVersion()
        const noexcept { return m_systemBiosVersion; }
    const std::pair<std::uint8_t, std::uint8_t>& MotherboardInfo::GetECFVersion()
        const noexcept { return m_ecfVersion; }

    const std::string& MotherboardInfo::GetUUID() const noexcept { return m_uuid; }
    const std::string& MotherboardInfo::GetVendor() const noexcept { return m_vendor; }
    const std::string& MotherboardInfo::GetBiosVersion() const noexcept { return m_biosVersion; }
    const std::string& MotherboardInfo::GetReleaseDate() const noexcept { return m_releaseDate; }
    const std::string& MotherboardInfo::GetManufacturer() const noexcept { return m_manufacturer; }
    const std::string& MotherboardInfo::GetProductName() const noexcept { return m_productName; }
    const std::string& MotherboardInfo::GetVersion() const noexcept { return m_version; }
    const std::string& MotherboardInfo::GetSerial() const noexcept { return m_serial; }
    const WakeUpType& MotherboardInfo::GetWakeUpType() const noexcept { return m_wakeUpType; }
    const std::string& MotherboardInfo::GetSKUNumber() const noexcept { return m_SKUNumber; }
    const std::string& MotherboardInfo::GetFamily() const noexcept { return m_family; }
    const BaseboardFlags& MotherboardInfo::GetBaseboardFlags()
        const noexcept { return m_featureFlags; }
    const BaseboardType& MotherboardInfo::GetBaseboardType()
        const noexcept { return m_boardType; }

    EXPORT std::future<MotherboardInfo> GetMotherboardInfoFuture() noexcept {
#ifdef SYSINFO_USE_CACHE
        static MotherboardInfo moboInfo;
#endif
        return std::async(std::launch::async, []() -> MotherboardInfo {
#ifdef SYSINFO_USE_CACHE
            if (moboInfo.IsInitialized())
                return moboInfo;
#endif

            auto smBiosDataSize = GetSystemFirmwareTable('RSMB', 0, nullptr, 0);

            auto procHeap = GetProcessHeap();
            auto smBiosData = static_cast<RawSMBIOSData*>(
                HeapAlloc(procHeap, HEAP_ZERO_MEMORY, smBiosDataSize)
            );
            if (!smBiosData)
                return {};

            auto bytesWritten = GetSystemFirmwareTable('RSMB', 0, smBiosData, smBiosDataSize);
            if (bytesWritten != smBiosDataSize) {
                HeapFree(procHeap, 0, smBiosData);
                return {};
            }
            if (bytesWritten < 0x1A) {
                HeapFree(procHeap, 0, smBiosData);
                return {};
            }

            auto& data = smBiosData->SMBIOSTableData;

            // Type 0

            std::string vendorName;
            std::string biosVersion;
            std::string biosReleaseDate;

            std::pair<std::uint8_t, std::uint8_t> systemBiosVersion;
            std::uint16_t biosAddress;
            std::uint32_t biosRomSize;
            std::pair<std::uint8_t, std::uint8_t> ecfVersion;

            BIOSCharacteristics biosCharacteristics;
            BIOSCharacteristicsExt biosCharacteristicsExt;

            std::uint32_t smbiosIndex = 0;
            {
                std::uint8_t type = data[smbiosIndex++];
                std::uint8_t length = data[smbiosIndex++];
                std::uint16_t handle = Core::Misc::ReadWord(data + smbiosIndex);
                smbiosIndex += 2;

                std::uint8_t vendorIndex = data[smbiosIndex++] - 1;
                std::uint8_t biosIndex = data[smbiosIndex++] - 1;
                biosAddress = Core::Misc::ReadWord(data + smbiosIndex);
                smbiosIndex += 2;

                std::uint8_t biosDateIndex = data[smbiosIndex++] - 1;
                std::uint8_t biosRomSizeTemp = data[smbiosIndex++];

                biosCharacteristics = Core::Misc::ReadQword(
                    data + smbiosIndex
                );
                smbiosIndex += 8;
                biosCharacteristicsExt = Core::Misc::ReadWord(
                    data + smbiosIndex
                );
                smbiosIndex += 2;

                // major
                systemBiosVersion.first = data[smbiosIndex++];
                // minor
                systemBiosVersion.second = data[smbiosIndex++];

                ecfVersion.first = data[smbiosIndex++];
                ecfVersion.second = data[smbiosIndex++];
                auto biosRomSizeExt = Core::Misc::ReadWord(data + smbiosIndex);
                smbiosIndex += 2;

                if (biosRomSizeTemp == 0xFF) {
                    biosRomSize = biosRomSizeExt & 0x3FFF;
                    if (biosRomSizeExt & 0x4000) {
                        biosRomSize <<= 10; // to MB *= 1024 (2^10)
                    }
                } else {
                    biosRomSize = biosRomSizeTemp;
                }
                biosRomSize <<= 10; // to KB

                char* stringList = reinterpret_cast<char*>(data + length);
                std::size_t index = 0;
                std::size_t size = 0;
                std::array<std::string, 3> smbiosStringValues;
                if (vendorIndex > smbiosStringValues.size()) return {};
                if (biosIndex > smbiosStringValues.size()) return {};
                if (biosDateIndex > smbiosStringValues.size()) return {};

                for (auto& value : smbiosStringValues) {
                    size = strlen(stringList + index);
                    value = std::string(stringList + index, size);
                    index += size + 1;
                }
                vendorName = smbiosStringValues[vendorIndex];
                biosVersion = smbiosStringValues[biosIndex];
                biosReleaseDate = smbiosStringValues[biosDateIndex];

                smbiosIndex += static_cast<std::uint32_t>(index) + 1;
            }

            // Type 1

            std::string manufacturer;
            std::string productName;
            std::string version;
            std::string serial;
            std::string uuid(35, 0);
            WakeUpType wakeUpType;
            std::string skuNumber;
            std::string pcFamily;
            {
                std::uint8_t type = data[smbiosIndex++];
                std::uint8_t length = data[smbiosIndex++];
                std::uint16_t handle = Core::Misc::ReadWord(data + smbiosIndex);
                smbiosIndex += 2;

                std::uint8_t manufacturerIndex = data[smbiosIndex++] - 1;
                std::uint8_t productIndex = data[smbiosIndex++] - 1;
                std::uint8_t versionIndex = data[smbiosIndex++] - 1;
                std::uint8_t serialIndex = data[smbiosIndex++] - 1;

                uuid = std::format(
                    "{:02X}{:02X}{:02X}{:02X}-"
                    "{:02X}{:02X}{:02X}{:02X}-"
                    "{:02X}{:02X}{:02X}{:02X}-"
                    "{:02X}{:02X}{:02X}{:02X}",
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++],
                    data[smbiosIndex++], data[smbiosIndex++]
                );
                
                switch (data[smbiosIndex++]) {
                    case 0:
                        wakeUpType = WakeUpType::RESERVED;
                        break;
                    case 1:
                        wakeUpType = WakeUpType::OTHER;
                        break;
                    case 2:
                    default:
                        wakeUpType = WakeUpType::UNKNOWN;
                        break;
                    case 3:
                        wakeUpType = WakeUpType::APM_TIMER;
                        break;
                    case 4:
                        wakeUpType = WakeUpType::MODEM_RING;
                        break;
                    case 5:
                        wakeUpType = WakeUpType::LAN_REMOTE;
                        break;
                    case 6:
                        wakeUpType = WakeUpType::POWER_SWITCH;
                        break;
                    case 7:
                        wakeUpType = WakeUpType::PCI_PME;
                        break;
                    case 8:
                        wakeUpType = WakeUpType::AC_POWER_RESTORED;
                        break;
                }
                std::uint8_t skuIndex = data[smbiosIndex++] - 1;
                std::uint8_t familyIndex = data[smbiosIndex++] - 1;

                char* stringList = reinterpret_cast<char*>(data + smbiosIndex);

                std::size_t size = 0;
                std::size_t index = 0;
                std::array<std::string, 6> smbiosStringValues;
                if (manufacturerIndex >= smbiosStringValues.size()) return {};
                if (productIndex >= smbiosStringValues.size()) return {};
                if (versionIndex >= smbiosStringValues.size()) return {};
                if (serialIndex >= smbiosStringValues.size()) return {};

                for (auto& value : smbiosStringValues) {
                    size = strlen(stringList + index);
                    value = std::string(stringList + index, size);
                    index += size + 1;
                }

                manufacturer = smbiosStringValues[manufacturerIndex];
                productName = smbiosStringValues[productIndex];
                version = smbiosStringValues[versionIndex];
                serial = smbiosStringValues[serialIndex];
                skuNumber = smbiosStringValues[skuIndex];
                pcFamily = smbiosStringValues[familyIndex];

                smbiosIndex += static_cast<std::uint32_t>(index) + 1;
            }

            BaseboardFlags featureFlags;
            BaseboardType boardType;
            {
                std::uint8_t type = data[smbiosIndex++];
                std::uint8_t length = data[smbiosIndex++];
                std::uint16_t handle = Core::Misc::ReadWord(data + smbiosIndex);
                smbiosIndex += 2;

                std::uint8_t manufacturerIndex = data[smbiosIndex++] - 1;
                std::uint8_t productIndex = data[smbiosIndex++] - 1;
                std::uint8_t versionIndex = data[smbiosIndex++] - 1;
                std::uint8_t serialIndex = data[smbiosIndex++] - 1;
                std::uint8_t assetIndex = data[smbiosIndex++] - 1;
                featureFlags = data[smbiosIndex++];
                std::uint8_t chassisIndex = data[smbiosIndex++] - 1;
                std::uint16_t chassisHandle = Core::Misc::ReadWord(data + smbiosIndex);
                smbiosIndex += 2;
                switch (data[smbiosIndex++]) {
                    case 1:
                    default:
                        boardType = BaseboardType::UNKNOWN;
                        break;
                    case 2:
                        boardType = BaseboardType::OTHER;
                        break;
                    case 3:
                        boardType = BaseboardType::SERVER_BLADE;
                        break;
                    case 4:
                        boardType = BaseboardType::CONNECTIVITY_SWITCH;
                        break;
                    case 5:
                        boardType = BaseboardType::SYSTEM_MANAGEMENT_MODULE;
                        break;
                    case 6:
                        boardType = BaseboardType::PROCESSOR_MODULE;
                        break;
                    case 7:
                        boardType = BaseboardType::IO_MODULE;
                        break;
                    case 8:
                        boardType = BaseboardType::MEMORY_MODULE;
                        break;
                    case 9:
                        boardType = BaseboardType::DAUGHTER_BOARD;
                        break;
                    case 10:
                        boardType = BaseboardType::MOTHERBOARD;
                        break;
                    case 11:
                        boardType = BaseboardType::PROCESSOR_MEMORY_MODULE;
                        break;
                    case 12:
                        boardType = BaseboardType::PROCESSOR_IO_MODULE;
                        break;
                    case 13:
                        boardType = BaseboardType::INTERCONNECT_BOARD;
                        break;
                }
            }

            HeapFree(procHeap, 0, smBiosData);

#ifndef SYSINFO_USE_CACHE
            auto
#endif
            moboInfo = MotherboardInfo(
                biosCharacteristics, biosCharacteristicsExt, systemBiosVersion,
                ecfVersion, biosAddress, biosRomSize, uuid,
                vendorName, biosVersion, biosReleaseDate, manufacturer,
                productName, version, serial, wakeUpType, skuNumber, pcFamily,

                featureFlags, boardType
            );
            return moboInfo;
        });
    }

    EXPORT FUTURE(MotherboardInfo) GetMotherboardInfo() noexcept {
#ifdef SYSINFO_USE_FUTURE
        return GetMotherboardInfoFuture();
#else
        auto info = GetMotherboardInfoFuture();
        info.wait();
        return info.get();
#endif
    }
}