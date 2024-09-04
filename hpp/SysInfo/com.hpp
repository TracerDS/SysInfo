#pragma once

#include <Wbemidl.h>
#include <unordered_map>
#include <string>
#include <vector>

namespace SysInfo::COM {
    class COMWrapper {
        void SetLastError(const HRESULT& res) noexcept;
    public:
        using COMEntry = std::unordered_map<std::string, std::string>;

        COMWrapper() noexcept;
        ~COMWrapper() noexcept;

        void Connect(const char* path = "ROOT\\CIMV2") noexcept;
        void Uninitialize() noexcept;

        std::vector<std::string> GetEnumeratedElements(const char* path) noexcept;
        std::vector<COMEntry> Query(const char* query) noexcept;

        bool IsInitialized() const noexcept;
        bool IsConnected() const noexcept;
        std::string GetLastError() const noexcept;
        HRESULT GetLastErrorCode() const noexcept;
    protected:
        IEnumWbemClassObject* m_enumerator{ nullptr };
        IWbemLocator* m_locator{ nullptr };
        IWbemServices* m_services{ nullptr };

        bool m_isInitInitialized{ false };
        bool m_isInitialized{ false };
        bool m_isConnected{ false };

        std::string m_lastError{};
        HRESULT m_lastErrorCode{};
    };
}