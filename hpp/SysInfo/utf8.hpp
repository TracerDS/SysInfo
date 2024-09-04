#pragma once

#include <string>

namespace SysInfo::UTF8 {
    constexpr std::wstring FromUTF8(const std::wstring& string) noexcept { return string; }
    std::wstring FromUTF8(const std::string& string) noexcept;
    
    constexpr std::string ToUTF8(const std::string& string) noexcept { return string; }
    std::string ToUTF8(const std::wstring& string) noexcept;
}
