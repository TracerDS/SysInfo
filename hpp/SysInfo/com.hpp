#pragma once

#include <Wbemidl.h>
#include <unordered_map>
#include <string>
#include <vector>

namespace SysInfo::Core::COM {
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
        IEnumWbemClassObject* m_enumerator;
        IWbemLocator* m_locator;
        IWbemServices* m_services;

        bool m_isInitInitialized;
        bool m_isInitialized;
        bool m_isConnected;

        std::string m_lastError;
        HRESULT m_lastErrorCode;
    };
}