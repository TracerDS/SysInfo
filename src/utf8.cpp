#include "pch.hpp"
#include <SysInfo/utf8.hpp>

namespace SysInfo::UTF8 {
    std::wstring FromUTF8(const std::string& string) noexcept {
        std::wstring data;
        if (string.empty())
            return data;

        const auto stringSize = string.size();
#ifdef _WIN32
        const auto size = MultiByteToWideChar(
            CP_UTF8, 0, string.c_str(), static_cast<int>(stringSize),
            nullptr, 0
        );
        data.resize(size + 1);
        MultiByteToWideChar(
            CP_UTF8, 0, string.c_str(), static_cast<int>(stringSize),
            data.data(), size
        );
#else
        const auto size = std::mbstowcs(nullptr, string.c_str(), stringSize) + 1;
        data.resize(size + 1);
        std::mbstowcs(data.data(), string.c_str(), stringSize);
#endif
        return data;
    }

    std::string ToUTF8(const std::wstring& string) noexcept {
        std::string data;
        if (string.empty())
            return data;

        const auto stringSize = string.size();
#ifdef _WIN32
        const auto size = WideCharToMultiByte(
            CP_UTF8, 0, string.c_str(), static_cast<int>(stringSize),
            nullptr, 0, nullptr, nullptr
        );

        data.resize(size);
        WideCharToMultiByte(
            CP_UTF8, 0, string.c_str(), static_cast<int>(stringSize),
            data.data(), size, nullptr, nullptr
        );
#else
        const auto size = std::wcstombs(nullptr, string.c_str(), stringSize) + 1;
        data.resize(size);
        std::wcstombs(data.data(), string.c_str(), stringSize);
#endif
        return data;
    }
}