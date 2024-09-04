#pragma once

#include <SysInfo/dll.hpp>
#include <string>
#include <unordered_map>
#include <cstdint>

namespace SysInfo::CPU {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT CPUInfo : public StructInit {
    public:
        enum class Architecture {
            UNKNOWN,
            AMD64,
            ARM,
            ARM64,
            IA64,
            INTEL,
        };
        enum class ProcType {
            UNKNOWN,
            OEM,
            IOP,
            DUAL,
        };

        CPUInfo() noexcept;
        CPUInfo(
            const Architecture& architecture,
            const ProcType& procType,
            const std::string& procID,
            const std::uint16_t& cores,
            const std::uint16_t& threads,
            const std::uint16_t& procRevision,
            const std::uint32_t& clockSpeed,
            const std::string& socket,
            const std::string& vendor,
            const std::string& brand,
            const std::unordered_map<std::string, bool>& features
        ) noexcept;

        const Architecture& GetArchitecture() const noexcept;
        const ProcType& GetProcessorType() const noexcept;
        const std::string& GetProcessorID() const noexcept;
        const std::uint16_t& GetCores() const noexcept;
        const std::uint16_t& GetThreads() const noexcept;
        const std::uint16_t& GetProcessorRevision() const noexcept;
        const std::uint32_t& GetClockSpeed() const noexcept;
        const std::string& GetSocket() const noexcept;
        const std::string& GetProcessorVendorName() const noexcept;
        const std::string& GetProcessorName() const noexcept;
        const std::unordered_map<std::string, bool>& GetFeatures() const noexcept;

        std::string GetArchitectureString() const noexcept;
        std::string GetProcessorTypeString() const noexcept;

        static Architecture ValueToArchitecture(std::uint16_t value) noexcept;
        static std::string ArchitectureToString(const Architecture& arch) noexcept;
        static std::string ProcessorTypeToString(const ProcType& type) noexcept;

    protected:
        Architecture m_architecture;
        ProcType m_procType;
        std::string m_procID;
        std::uint16_t m_cores;
        std::uint16_t m_threads;
        std::uint16_t m_procRevision;
        std::uint32_t m_clockSpeed;
        std::string m_socket;
        std::string m_vendor;
        std::string m_brand;
        std::unordered_map<std::string, bool> m_features;
    };
#pragma warning(pop)

    EXPORT FUTURE(CPUInfo) GetCPUInfo() noexcept;
}