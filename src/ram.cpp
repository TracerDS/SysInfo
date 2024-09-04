#include "pch.hpp"
#include <SysInfo/ram.hpp>
#include <SysInfo/com.hpp>
#include <SysInfo/misc.hpp>

namespace SysInfo::RAM {
    using RAMStick = RAMInfo::RAMStick;

    RAMInfo::RAMInfo() noexcept {}
    RAMInfo::RAMInfo(const std::vector<RAMStick>& sticks) noexcept
        : m_sticks(sticks)
    {
        m_initialized = true;
    }

    const std::vector<RAMStick>& RAMInfo::GetSticks() const noexcept {
        return m_sticks;
    }

    RAMStick::RAMStick(
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
    ) noexcept :
        m_name(name),
        m_caption(caption),
        m_description(description),
        m_speed(speed),
        m_clockSpeed(clockSpeed),
        m_minVoltage(minVoltage),
        m_configuredVoltage(configuredVoltage),
        m_maxVoltage(maxVoltage),
        m_capacity(capacity),
        m_manufacturer(manufacturer),
        m_partNumber(partNumber),
        m_serial(serial),
        m_bankName(bankName),
        m_deviceLocator(deviceLocator)
    {}

    const std::string& RAMStick::GetName() const noexcept { return m_name; }
    const std::string& RAMStick::GetCaption() const noexcept { return m_caption; }
    const std::string& RAMStick::GetDescription() const noexcept { return m_description; }
    const std::uint32_t& RAMStick::GetSpeed() const noexcept { return m_speed; }
    const std::uint32_t& RAMStick::GetClockSpeed() const noexcept { return m_clockSpeed; }
    const std::uint32_t& RAMStick::GetMinVoltage() const noexcept { return m_minVoltage; }
    const std::uint32_t& RAMStick::GetConfiguredVoltage() const noexcept { return m_configuredVoltage; }
    const std::uint32_t& RAMStick::GetMaxVoltage() const noexcept { return m_maxVoltage; }
    const std::uint64_t& RAMStick::GetCapacity() const noexcept { return m_capacity; }
    const std::string& RAMStick::GetManufacturer() const noexcept { return m_manufacturer; }
    const std::string& RAMStick::GetPartNumber() const noexcept { return m_partNumber; }
    const std::string& RAMStick::GetSerial() const noexcept { return m_serial; }
    const std::string& RAMStick::GetBankName() const noexcept { return m_bankName; }
    const std::string& RAMStick::GetDeviceLocator() const noexcept { return m_deviceLocator; }

#ifdef SYSINFO_USE_FUTURE
    EXPORT
#endif
    std::future<RAMInfo> GetRAMInfoFuture() noexcept {
        static RAMInfo ramInfo;
        return std::async(std::launch::async, [] {
            if (ramInfo.IsInitialized())
                return ramInfo;

            COM::COMWrapper com;
            com.Connect();
            auto results = com.Query("SELECT * FROM Win32_PhysicalMemory");
            std::vector<RAMStick> sticks;
            sticks.reserve(results.size());
            for (auto& stick : results) {
                std::string name = stick["Name"];
                std::string caption = stick["Caption"];
                std::string description = stick["Description"];
                std::uint32_t speed = Misc::stoui32(stick["Speed"]);
                std::uint32_t clockSpeed = Misc::stoui32(stick["ConfiguredClockSpeed"]);
                std::uint32_t minVoltage = Misc::stoui32(stick["MinVoltage"]);
                std::uint32_t configuredVoltage = Misc::stoui32(stick["ConfiguredVoltage"]);
                std::uint32_t maxVoltage = Misc::stoui32(stick["MaxVoltage"]);
                std::uint64_t capacity = Misc::stoui64(stick["Capacity"]);
                std::string manufacturer = stick["Manufacturer"];
                std::string partNumber = stick["PartNumber"];
                std::string serial = stick["SerialNumber"];
                std::string bankName = stick["BankLabel"];
                std::string deviceLocator = stick["DeviceLocator"];

                sticks.emplace_back(
                    name,
                    caption,
                    description,
                    speed,
                    clockSpeed,
                    minVoltage,
                    configuredVoltage,
                    maxVoltage,
                    capacity,
                    manufacturer,
                    partNumber,
                    serial,
                    bankName,
                    deviceLocator
                );
            }

            ramInfo = RAMInfo(sticks);
            return ramInfo;
        });
    }

    EXPORT FUTURE(RAMInfo) GetRAMInfo() noexcept {
#ifdef SYSINFO_USE_FUTURE
        return GetRAMInfoFuture();
#else
        auto info = GetRAMInfoFuture();
        info.wait();
        return info.get();
#endif
    }
}