#pragma once

#include <SysInfo/dll.hpp>
#include <vector>
#include <string>
#include <cstdint>

namespace SysInfo::RAM {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT RAMInfo : public Core::StructInit {
    public:
        class EXPORT RAMStick : public StructInit {
        public:
            RAMStick(
                std::string name,
                std::string caption,
                std::string description,
                std::uint32_t speed,
                std::uint32_t clockSpeed,
                std::uint32_t minVoltage,
                std::uint32_t configuredVoltage,
                std::uint32_t maxVoltage,
                std::uint64_t capacity,
                std::string manufacturer,
                std::string partNumber,
                std::string serial,
                std::string bankName,
                std::string deviceLocator
            ) noexcept;

            const std::string& GetName() const noexcept;
            const std::string& GetCaption() const noexcept;
            const std::string& GetDescription() const noexcept;
            const std::uint32_t& GetSpeed() const noexcept;
            const std::uint32_t& GetClockSpeed() const noexcept;
            const std::uint32_t& GetMinVoltage() const noexcept;
            const std::uint32_t& GetConfiguredVoltage() const noexcept;
            const std::uint32_t& GetMaxVoltage() const noexcept;
            const std::uint64_t& GetCapacity() const noexcept;
            const std::string& GetManufacturer() const noexcept;
            const std::string& GetPartNumber() const noexcept;
            const std::string& GetSerial() const noexcept;
            const std::string& GetBankName() const noexcept;
            const std::string& GetDeviceLocator() const noexcept;
        protected:
            std::string m_name;
            std::string m_caption;
            std::string m_description;
            std::uint32_t m_speed;
            std::uint32_t m_clockSpeed;
            std::uint32_t m_minVoltage;
            std::uint32_t m_configuredVoltage;
            std::uint32_t m_maxVoltage;
            std::uint64_t m_capacity;
            std::string m_manufacturer;
            std::string m_partNumber;
            std::string m_serial;
            std::string m_bankName;
            std::string m_deviceLocator;
        };

        RAMInfo() noexcept;
        RAMInfo(const std::vector<RAMStick>& sticks) noexcept;

        const std::vector<RAMStick>& GetSticks() const noexcept;
    protected:
        std::vector<RAMStick> m_sticks;
    };
#pragma warning(pop)

    EXPORT std::future<RAMInfo> GetRAMInfoFuture() noexcept;
    EXPORT FUTURE(RAMInfo) GetRAMInfo() noexcept;
}
