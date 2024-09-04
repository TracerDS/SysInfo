#include "pch.hpp"
#include <SysInfo/misc.hpp>

namespace SysInfo::Misc {
    std::int8_t stoi8(const std::string_view& string) noexcept {
        try {
            return std::stoi(string.data());
        } catch (...) {
            return 0;
        }
    }
    std::int16_t stoi16(const std::string_view& string) noexcept {
        try {
            return std::stoi(string.data());
        } catch (...) {
            return 0;
        }
    }
    std::int32_t stoi32(const std::string_view& string) noexcept {
        try {
            return std::stoi(string.data());
        } catch (...) {
            return 0;
        }
    }
    std::int64_t stoi64(const std::string_view& string) noexcept {
        try {
            return std::stoll(string.data());
        } catch (...) {
            return 0;
        }
    }
    std::uint8_t stoui8(const std::string_view& string) noexcept {
        try {
            return static_cast<std::uint8_t>(stoui32(string));
        } catch (...) {
            return 0;
        }
    }
    std::uint16_t stoui16(const std::string_view& string) noexcept {
        try {
            return static_cast<std::uint16_t>(stoui32(string));
        } catch (...) {
            return 0;
        }
    }
    std::uint32_t stoui32(const std::string_view& string) noexcept {
        try {
            return std::stoul(string.data());
        } catch (...) {
            return 0;
        }
    }
    std::uint64_t stoui64(const std::string_view& string) noexcept {
        try {
            return std::stoull(string.data());
        } catch (...) {
            return 0;
        }
    }

    std::uint16_t ReadWord(std::uint8_t ptr[2]) {
        return (ptr[0] << 8) | ptr[1];
    }
    
    std::uint32_t ReadDword(std::uint8_t ptr[4]) {
        return (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
    }
    std::uint32_t ReadDword(std::uint16_t ptr[2]) {
        return (ptr[0] << 16) | ptr[1];
    }

    std::uint64_t ReadQword(std::uint8_t ptr[8]) {
        std::uint64_t d1 = ptr[0];
        std::uint64_t d2 = ptr[1];
        std::uint64_t d3 = ptr[2];
        std::uint64_t d4 = ptr[3];
        std::uint64_t d5 = ptr[4];
        std::uint64_t d6 = ptr[5];
        std::uint64_t d7 = ptr[6];
        std::uint64_t d8 = ptr[7];
        return (d1 << 56) | (d2 << 48) | (d3 << 40) | (d4 << 32)
            | (d5 << 24) | (d6 << 16) | (d7 << 8) | d8;
    }
    std::uint64_t ReadQword(std::uint16_t ptr[4]) {
        std::uint64_t d1 = ptr[0];
        std::uint64_t d2 = ptr[1];
        std::uint64_t d3 = ptr[2];
        std::uint64_t d4 = ptr[3];
        return (d1 << 48) | (d2 << 32) | (d3 << 16) | d4;
    }
    std::uint64_t ReadQword(std::uint32_t ptr[2]) {
        return ((std::uint64_t) ptr[0] << 32) | ptr[1];
    }
}