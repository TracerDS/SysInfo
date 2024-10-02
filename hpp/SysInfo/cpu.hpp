#pragma once

#include <SysInfo/dll.hpp>
#include <string>
#include <unordered_map>
#include <cstdint>

namespace SysInfo::CPU {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT CPUInfo : public Core::StructInit {
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
            const std::unordered_map<std::string, bool>& features,
            const std::uint64_t& procTimestamp
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
        const std::uint64_t& GetProcessorTimestamp() const noexcept;

        std::string GetArchitectureString() const noexcept;
        std::string GetProcessorTypeString() const noexcept;

        static Architecture ValueToArchitecture(std::uint16_t value) noexcept;
        static std::string ArchitectureToString(const Architecture& arch) noexcept;
        static std::string ProcessorTypeToString(const ProcType& type) noexcept;

    protected:
        const Architecture m_architecture;
        const ProcType m_procType;
        const std::string m_procID;
        const std::uint16_t m_cores;
        const std::uint16_t m_threads;
        const std::uint16_t m_procRevision;
        const std::uint32_t m_clockSpeed;
        const std::string m_socket;
        const std::string m_vendor;
        const std::string m_brand;
        const std::unordered_map<std::string, bool> m_features;
        const std::uint64_t m_procTimestamp;
    };
#pragma warning(pop)

    EXPORT std::future<CPUInfo> GetCPUInfoFuture() noexcept;
    EXPORT FUTURE(CPUInfo) GetCPUInfo() noexcept;
}