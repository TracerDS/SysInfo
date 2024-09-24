#include "pch.hpp"
#include <SysInfo/os.hpp>
#include <SysInfo/utf8.hpp>

#include <iostream>
#include <windows.h>
#include <lm.h>
#include <vector>
#include <string>

#pragma comment(lib, "Netapi32.lib")

namespace SysInfo::OS {
    using User = OSInfo::User;
    using PrivilegeLevel = User::PrivilegeLevel;

    EXPORT std::future<OSInfo> GetOSInfoFuture() noexcept {
#ifdef SYSINFO_USE_CACHE
        static OSInfo osInfo;
#endif
        return std::async(std::launch::async, []() -> OSInfo {
#ifdef SYSINFO_USE_CACHE
            if (osInfo.IsInitialized())
                return osInfo;
#endif
            std::wstring computerName;
            {
                DWORD size = 0;
                GetComputerNameExW(ComputerNamePhysicalDnsFullyQualified, nullptr, &size);
                computerName.resize(size);
                GetComputerNameExW(ComputerNamePhysicalDnsFullyQualified, &computerName[0], &size);
            }
            std::wstring systemLocale(LOCALE_NAME_MAX_LENGTH, L'\0');
            GetSystemDefaultLocaleName(systemLocale.data(), static_cast<int>(systemLocale.size()));

            std::wstring userLocale(LOCALE_NAME_MAX_LENGTH, L'\0');
            GetUserDefaultLocaleName(userLocale.data(), static_cast<int>(userLocale.size()));

            GetLocaleInfoEx(systemLocale.c_str(), LOCALE_SLANGUAGE,
                systemLocale.data(), static_cast<int>(systemLocale.size())
            );
            GetLocaleInfoEx(userLocale.c_str(), LOCALE_SLANGUAGE,
                userLocale.data(), static_cast<int>(userLocale.size())
            );
            

            USER_INFO_3* userInfo;
            DWORD entries{ 0 };
            DWORD totalEntries{ 0 };

            if (NetUserEnum(
                nullptr,
                3,
                0,
                reinterpret_cast<LPBYTE*>(&userInfo),
                MAX_PREFERRED_LENGTH,
                &entries,
                &totalEntries,
                nullptr
            ) != NERR_Success) {
                entries = 0;
            }

            std::vector<User> users;
            
            for (DWORD i = 0; i < entries; i++) {
                std::string name = UTF8::ToUTF8(userInfo[i].usri3_name);
                std::string fullName = UTF8::ToUTF8(userInfo[i].usri3_full_name);
                auto passwordAge = userInfo[i].usri3_password_age;
                PrivilegeLevel privileges;
                switch (userInfo[i].usri3_priv) {
                    case USER_PRIV_GUEST:
                    default:
                        privileges = PrivilegeLevel::GUEST;
                        break;
                    case USER_PRIV_USER:
                        privileges = PrivilegeLevel::USER;
                        break;
                    case USER_PRIV_ADMIN:
                        privileges = PrivilegeLevel::ADMIN;
                        break;
                }
                std::string homeDir = UTF8::ToUTF8(userInfo[i].usri3_home_dir);
                std::string scriptPath = UTF8::ToUTF8(userInfo[i].usri3_script_path);
                std::string comment = UTF8::ToUTF8(userInfo[i].usri3_comment);
                std::string userComment = UTF8::ToUTF8(userInfo[i].usri3_usr_comment);
                DWORD flags = userInfo[i].usri3_flags;
                DWORD authFlags = userInfo[i].usri3_auth_flags;
                std::string params = UTF8::ToUTF8(userInfo[i].usri3_parms);
                std::string workstationsString = UTF8::ToUTF8(userInfo[i].usri3_workstations);

                std::array<std::string, 8> workstations;
                {
                    auto end = workstationsString.end();
                    std::string::iterator prevIt = workstationsString.begin();
                    std::string::iterator nextIt;

                    int ii = 0;
                    while ((nextIt = std::find(prevIt, end, ',')) != end && ii < workstations.size()) {
                        workstations[ii++] = std::string(prevIt, nextIt);
                        prevIt = nextIt + 1;
                    }

                    if(ii <= 7)
                        workstations[ii] = std::string(prevIt, nextIt);
                }
                std::uint32_t lastLogon = userInfo[i].usri3_last_logon;
                std::uint32_t lastLogoff = userInfo[i].usri3_last_logoff;
                std::uint32_t expireTime = userInfo[i].usri3_acct_expires;
                std::uint32_t maxStorage = userInfo[i].usri3_max_storage;
                std::uint32_t unitsPerWeek = userInfo[i].usri3_units_per_week;
                BYTE* logonHours = userInfo[i].usri3_logon_hours;

                /*
                users.push_back(User(
                    name, fullName, passwordAge, privileges, homeDir,
                    scriptPath, comment, userComment, flags, authFlags,
                    params, workstations
                ));
                */
            }

            return {};
        });
    }

    EXPORT FUTURE(OSInfo) GetOSInfo() noexcept {
#ifdef SYSINFO_USE_FUTURE
        return GetOSInfoFuture();
#else
        auto info = GetOSInfoFuture();
        info.wait();
        return info.get();
#endif
    }
}