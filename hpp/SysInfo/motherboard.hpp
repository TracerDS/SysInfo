#pragma once

#include <SysInfo/dll.hpp>
#include <cstdint>
#include <string>

namespace SysInfo::Motherboard {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT MotherboardInfo : public StructInit {
    public:
        struct BIOSCharacteristics {
            std::uint8_t _reserved : 2;
            std::uint8_t _unknown : 1;
            std::uint8_t charsSupported : 1;
            std::uint8_t ISA : 1;
            std::uint8_t MCA : 1;
            std::uint8_t EISA : 1;
            std::uint8_t PCI : 1;
            std::uint8_t PCMCIA_CARD : 1;
            std::uint8_t PAP : 1;
            std::uint8_t APM : 1;
            std::uint8_t upgradeable : 1;
            std::uint8_t shadowing : 1;
            std::uint8_t VLVESA : 1;
            std::uint8_t ESCD : 1;
            std::uint8_t cdBoot : 1;
            std::uint8_t selectableBoot : 1;
            std::uint8_t biosRom : 1;
            std::uint8_t PCMCIA_BOOT : 1;
            std::uint8_t EDD : 1;
            std::uint8_t floppyNEC9800 : 1;
            std::uint8_t floppyToshiba : 1;
            std::uint8_t floppy360 : 1;
            std::uint8_t floppy1228 : 1;
            std::uint8_t floppy720 : 1;
            std::uint8_t floppy2949 : 1;
            std::uint8_t printScreen : 1;
            std::uint8_t keyboard8042 : 1;
            std::uint8_t serialServices : 1;
            std::uint8_t printerServices : 1;
            std::uint8_t CGA_MONO : 1;
            std::uint8_t NEC_PC98 : 1;
            std::uint16_t _reservedBIOSVendor;
            std::uint16_t _reservedSystemVendor;

            BIOSCharacteristics(const std::uint64_t& value = 0) noexcept;

            operator std::uint64_t() const noexcept;
        };

        struct BIOSCharacteristicsExt {
            std::uint8_t ACPI : 1;
            std::uint8_t legacyUSB : 1;
            std::uint8_t AGP : 1;
            std::uint8_t I2OBOOT : 1;
            std::uint8_t LS120SuperDisk : 1;
            std::uint8_t ATAPI : 1;
            std::uint8_t boot1394 : 1;
            std::uint8_t smartBattery : 1;
            std::uint8_t biosBoot : 1;
            std::uint8_t networkBoot : 1;
            std::uint8_t targetedContent : 1;
            std::uint8_t UEFI : 1;
            std::uint8_t virtualMachine : 1;
            std::uint8_t _reserved : 3;

            BIOSCharacteristicsExt(const std::uint16_t& value = 0) noexcept;

            operator std::uint16_t() const noexcept;
        };

        struct BaseboardFlags {
            std::uint8_t motherboard : 1;
            std::uint8_t requireAux : 1;
            std::uint8_t removable : 1;
            std::uint8_t replaceable : 1;
            std::uint8_t hotSwappable : 1;
            std::uint8_t _reserved : 3;

            BaseboardFlags(const std::uint8_t& value = 0) noexcept;
            operator std::uint8_t() const noexcept;
        };

        enum class BaseboardType {
            UNKNOWN = 1,
            OTHER = 2,
            SERVER_BLADE = 3,
            CONNECTIVITY_SWITCH = 4,
            SYSTEM_MANAGEMENT_MODULE = 5,
            PROCESSOR_MODULE = 6,
            IO_MODULE = 7,
            MEMORY_MODULE = 8,
            DAUGHTER_BOARD = 9,
            MOTHERBOARD = 10,
            PROCESSOR_MEMORY_MODULE = 11,
            PROCESSOR_IO_MODULE = 12,
            INTERCONNECT_BOARD = 13,
        };
        static std::string BaseboardTypeToString(const BaseboardType& type) noexcept;

        enum class WakeUpType {
            RESERVED = 0,
            OTHER = 1,
            UNKNOWN = 2,
            APM_TIMER = 3,
            MODEM_RING = 4,
            LAN_REMOTE = 5,
            POWER_SWITCH = 6,
            PCI_PME = 7,
            AC_POWER_RESTORED = 8,
        };
        static std::string WakeUpTypeToString(const WakeUpType& type) noexcept;

        MotherboardInfo() noexcept;

        MotherboardInfo(
            const BIOSCharacteristics& biosChars,
            const BIOSCharacteristicsExt& biosCharsExt,
            const std::pair<std::uint8_t, std::uint8_t>& systemBiosVersion,
            const std::pair<std::uint8_t, std::uint8_t>& ecfVesion,
            const std::uint16_t& biosAddress,
            const std::uint32_t& biosRomSize,
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
        ) noexcept;

        const BIOSCharacteristics& GetBIOSCharacteristics() const noexcept;
        const BIOSCharacteristicsExt& GetBIOSCharacteristicsExt() const noexcept;
        const std::pair<std::uint8_t, std::uint8_t>& GetSystemBIOSVersion() const noexcept;
        // ECF - Embedded Controller Firmware
        const std::pair<std::uint8_t, std::uint8_t>& GetECFVersion() const noexcept;

        const std::string& GetVendor() const noexcept;
        const std::string& GetBiosVersion() const noexcept;
        const std::string& GetReleaseDate() const noexcept;
        const std::string& GetManufacturer() const noexcept;
        const std::string& GetProductName() const noexcept;
        const std::string& GetVersion() const noexcept;
        const std::string& GetSerial() const noexcept;
        const WakeUpType& GetWakeUpType() const noexcept;
        const std::string& GetSKUNumber() const noexcept;
        const std::string& GetFamily() const noexcept;
        const BaseboardFlags& GetBaseboardFlags() const noexcept;
        const BaseboardType& GetBaseboardType() const noexcept;
    protected:
        BIOSCharacteristics m_biosChars;
        BIOSCharacteristicsExt m_biosCharsExt;
        std::pair<std::uint8_t, std::uint8_t> m_systemBiosVersion;
        std::pair<std::uint8_t, std::uint8_t> m_ecfVersion;
        std::uint16_t m_biosAddress;
        std::uint32_t m_romSize;
        std::string m_vendor;
        std::string m_biosVersion;
        std::string m_releaseDate;
        std::string m_manufacturer;
        std::string m_productName;
        std::string m_version;
        std::string m_serial;
        WakeUpType m_wakeUpType;
        std::string m_SKUNumber;
        std::string m_family;
        BaseboardFlags m_featureFlags;
        BaseboardType m_boardType;
    };
#pragma warning(pop)

    EXPORT FUTURE(MotherboardInfo) GetMotherboardInfo() noexcept;
}
