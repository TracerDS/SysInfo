#include "pch.hpp"
#include <SysInfo/os.hpp>
#include <SysInfo/utf8.hpp>

#include <vector>
#include <string>

#include <windows.h>
#include <lm.h>

#pragma comment(lib, "Netapi32.lib")

namespace SysInfo::OS {
    using WindowsVersion = OSInfo::WindowsVersion;
    using ProductType = WindowsVersion::ProductType;

    using User = OSInfo::User;
    using PrivilegeLevel = User::PrivilegeLevel;
    using TimeRestriction = User::TimeRestriction;

    WindowsVersion::WindowsVersion() noexcept
        : m_major(0), m_minor(0), m_build(0), m_fullNumber(0) {}

    WindowsVersion::WindowsVersion(
        const std::uint8_t& major,
        const std::uint16_t& minor,
        const std::uint16_t& build
    ) noexcept : m_major(major), m_minor(minor), m_build(build),
        m_fullNumber(major * 10000000 + minor * 10000 + build) {}

    WindowsVersion::WindowsVersion(
        const std::uint64_t& fullNumber
    ) noexcept : m_fullNumber(fullNumber),
        m_major(static_cast<std::uint8_t>(fullNumber / 1000000)),
        m_minor(static_cast<std::uint16_t>((fullNumber % 10000000) / 10000)),
        m_build(fullNumber % 10000) {}

    const std::uint8_t& WindowsVersion::GetMajor() const noexcept { return this->m_major; }
    const std::uint16_t& WindowsVersion::GetMinor() const noexcept { return this->m_minor; }
    const std::uint16_t& WindowsVersion::GetBuild() const noexcept { return this->m_build; }

    bool WindowsVersion::operator==(const WindowsVersion& version) const noexcept {
        if (this->m_major != version.m_major)
            return false;
        if (this->m_minor != version.m_minor)
            return false;
        if (this->m_build != version.m_build)
            return false;
        return true;
    }
    bool WindowsVersion::operator!=(const WindowsVersion& version) const noexcept {
        return !operator==(version);
    }

    bool WindowsVersion::operator> (const WindowsVersion& version) const noexcept {
        return this->m_fullNumber > version.m_fullNumber;
    }
    bool WindowsVersion::operator< (const WindowsVersion& version) const noexcept {
        return this->m_fullNumber < version.m_fullNumber;
    }

    bool WindowsVersion::operator>=(const WindowsVersion& version) const noexcept {
        return this->m_fullNumber >= version.m_fullNumber;
    }
    bool WindowsVersion::operator<=(const WindowsVersion& version) const noexcept {
        return this->m_fullNumber <= version.m_fullNumber;
    }

    WindowsVersion::operator std::uint64_t() const noexcept {
        return m_fullNumber;
    }

    User::User (
        const std::string& name,
        const std::string& fullName,
        const std::uint32_t& passwordAge,
        const PrivilegeLevel& privileges,
        const std::string& homeDir,
        const std::string& scriptPath,
        const std::string& comment,
        const std::string& userComment,
        const std::uint32_t& flags,
        const std::uint32_t& authFlags,
        const std::string& params,
        const std::array<std::string, 8>& workstations,
        const std::uint32_t& lastLogon,
        const std::uint32_t& lastLogoff,
        const std::uint32_t& expireTime,
        const std::uint32_t& maxStorage,
        const std::uint32_t& unitsPerWeek,
        const std::array<TimeRestriction, 7>& timeRestriction,
        const std::uint32_t& badPasswordCount,
        const std::uint32_t& logonsNumber,
        const std::string& logonServer,
        const std::uint32_t& countryCode,
        const std::uint32_t& codePage,
        const std::uint32_t& userID,
        const std::uint32_t& primaryGroupID,
        const std::string& profile,
        const std::string& homeDirDrive,
        const std::uint32_t& passwordExpireInfo,
        const std::vector<std::string>& userGroups
    ) noexcept : m_name(name),
        m_fullName(fullName),
        m_passwordAge(passwordAge),
        m_privileges(privileges),
        m_homeDir(homeDir),
        m_scriptPath(scriptPath),
        m_comment(comment),
        m_userComment(userComment),
        m_flags(flags),
        m_authFlags(authFlags),
        m_params(params),
        m_workstations(workstations),
        m_lastLogon(lastLogon),
        m_lastLogoff(lastLogoff),
        m_expireTime(expireTime),
        m_maxStorage(maxStorage),
        m_unitsPerWeek(unitsPerWeek),
        m_timeRestriction(timeRestriction),
        m_badPasswordCount(badPasswordCount),
        m_logonsNumber(logonsNumber),
        m_logonServer(logonServer),
        m_countryCode(countryCode),
        m_codePage(codePage),
        m_userID(userID),
        m_primaryGroupID(primaryGroupID),
        m_profile(profile),
        m_homeDirDrive(homeDirDrive),
        m_passwordExpireInfo(passwordExpireInfo),
        m_userGroups(userGroups) {}

    const std::string& User::GetName() const noexcept { return m_name; }
    const std::string& User::GetFullName() const noexcept { return m_fullName; }
    const std::uint32_t& User::GetPasswordAge() const noexcept { return m_passwordAge; }
    const PrivilegeLevel& User::GetPrivileges() const noexcept { return m_privileges; }
    const std::string& User::GetHomeDir() const noexcept { return m_homeDir; }
    const std::string& User::GetScriptPath() const noexcept { return m_scriptPath; }
    const std::string& User::GetComment() const noexcept { return m_comment; }
    const std::string& User::GetUserComment() const noexcept { return m_userComment; }
    const std::uint32_t& User::GetFlags() const noexcept { return m_flags; }
    const std::uint32_t& User::GetAuthFlags() const noexcept { return m_authFlags; }
    const std::string& User::GetParams() const noexcept { return m_params; }
    const std::array<std::string, 8>& User::GetWorkstations() const noexcept { return m_workstations; }
    const std::uint32_t& User::GetLastLogon() const noexcept { return m_lastLogon; }
    const std::uint32_t& User::GetLastLogoff() const noexcept { return m_lastLogoff; }
    const std::uint32_t& User::GetExpireTime() const noexcept { return m_expireTime; }
    const std::uint32_t& User::GetMaxStorage() const noexcept { return m_maxStorage; }
    const std::uint32_t& User::GetUnitsPerWeek() const noexcept { return m_unitsPerWeek; }
    const std::array<TimeRestriction, 7>& User::GetTimeRestriction() const noexcept { return m_timeRestriction; }
    const std::uint32_t& User::GetBadPasswordCount() const noexcept { return m_badPasswordCount; }
    const std::uint32_t& User::GetLogonsNumber() const noexcept { return m_logonsNumber; }
    const std::string& User::GetLogonServer() const noexcept { return m_logonServer; }
    const std::uint32_t& User::GetCountryCode() const noexcept { return m_countryCode; }
    const std::uint32_t& User::GetCodePage() const noexcept { return m_codePage; }
    const std::uint32_t& User::GetUserID() const noexcept { return m_userID; }
    const std::uint32_t& User::GetPrimaryGroupID() const noexcept { return m_primaryGroupID; }
    const std::string& User::GetProfile() const noexcept { return m_profile; }
    const std::string& User::GetHomeDirDrive() const noexcept { return m_homeDirDrive; }
    const std::uint32_t& User::GetPasswordExpireInfo() const noexcept { return m_passwordExpireInfo; }
    const std::vector<std::string>& User::GetUserGroups() const noexcept { return m_userGroups; }

    std::string User::PrivilegeLevelToString(const PrivilegeLevel& level) noexcept {
        switch (level) {
            case PrivilegeLevel::GUEST:
            default:
                return "GUEST";
            case PrivilegeLevel::USER:
                return "USER";
            case PrivilegeLevel::ADMIN:
                return "ADMIN";
        }
    }

    OSInfo::OSInfo(
        const WindowsVersion& windowsVersion,
        const std::vector<User>& users
    ) noexcept : m_windowsVersion(windowsVersion), m_users(users) {}

    const WindowsVersion& OSInfo::GetVersion() const noexcept { return m_windowsVersion; }
    const std::vector<User>& OSInfo::GetUsers() const noexcept { return m_users; }

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

            GetLocaleInfoEx(systemLocale.c_str(), LOCALE_SENGLISHDISPLAYNAME,
                systemLocale.data(), static_cast<int>(systemLocale.size())
            );
            GetLocaleInfoEx(userLocale.c_str(), LOCALE_SENGLISHDISPLAYNAME,
                userLocale.data(), static_cast<int>(userLocale.size())
            );

            WindowsVersion windowsVersion;
            ProductType productType = ProductType::UNKNOWN;
            auto module = GetModuleHandleW(L"ntdll.dll");
            if (module) {
                using RtlGetVersion_t = HRESULT(WINAPI*)(OSVERSIONINFOEXW* lpVersionInformation);
                auto RtlGetVersion = reinterpret_cast<RtlGetVersion_t>(GetProcAddress(module, "RtlGetVersion"));
                if (RtlGetVersion) {
                    OSVERSIONINFOEXW fow{ 0 };
                    fow.dwOSVersionInfoSize = sizeof(fow);
                    if (SUCCEEDED(RtlGetVersion(&fow))) {
                        windowsVersion = WindowsVersion(
                            static_cast<std::uint8_t>(fow.dwMajorVersion),
                            static_cast<std::uint16_t>(fow.dwMinorVersion),
                            static_cast<std::uint16_t>(fow.dwBuildNumber)
                        );
                        auto servicePackMajor = fow.wServicePackMajor;
                        auto servicePackMinor = fow.wServicePackMinor;
                        auto suiteMask = fow.wSuiteMask;
                        
                        switch (fow.wProductType) {
                            case VER_NT_WORKSTATION:
                                productType = ProductType::WORKSTATION;
                                break;
                            case VER_NT_DOMAIN_CONTROLLER:
                                productType = ProductType::DOMAIN_CONTROLLER;
                                break;
                            case VER_NT_SERVER:
                                productType = ProductType::SERVER;
                                break;
                        }
                    }
                }
            }


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
                if (name.empty() && fullName.empty())
                    continue;
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

                std::array<TimeRestriction, 7> timeRestriction;

                for (auto i = 0; i < timeRestriction.size(); i++) {
                    TimeRestriction restriction{};

                    restriction.H00_00 = logonHours[i * 3] & 0x01;
                    restriction.H01_00 = logonHours[i * 3] & 0x02;
                    restriction.H02_00 = logonHours[i * 3] & 0x04;
                    restriction.H03_00 = logonHours[i * 3] & 0x08;
                    restriction.H04_00 = logonHours[i * 3] & 0x10;
                    restriction.H05_00 = logonHours[i * 3] & 0x20;
                    restriction.H06_00 = logonHours[i * 3] & 0x40;
                    restriction.H07_00 = logonHours[i * 3] & 0x80;
                    restriction.H08_00 = logonHours[i * 3 + 1] & 0x01;
                    restriction.H09_00 = logonHours[i * 3 + 1] & 0x02;
                    restriction.H10_00 = logonHours[i * 3 + 1] & 0x04;
                    restriction.H11_00 = logonHours[i * 3 + 1] & 0x08;
                    restriction.H12_00 = logonHours[i * 3 + 1] & 0x10;
                    restriction.H13_00 = logonHours[i * 3 + 1] & 0x20;
                    restriction.H14_00 = logonHours[i * 3 + 1] & 0x40;
                    restriction.H15_00 = logonHours[i * 3 + 1] & 0x80;
                    restriction.H16_00 = logonHours[i * 3 + 2] & 0x01;
                    restriction.H17_00 = logonHours[i * 3 + 2] & 0x02;
                    restriction.H18_00 = logonHours[i * 3 + 2] & 0x04;
                    restriction.H19_00 = logonHours[i * 3 + 2] & 0x08;
                    restriction.H20_00 = logonHours[i * 3 + 2] & 0x10;
                    restriction.H21_00 = logonHours[i * 3 + 2] & 0x20;
                    restriction.H22_00 = logonHours[i * 3 + 2] & 0x40;
                    restriction.H23_00 = logonHours[i * 3 + 2] & 0x80;

                    timeRestriction[i] = restriction;
                }

                std::uint32_t badPasswordCount = userInfo[i].usri3_bad_pw_count;
                std::uint32_t logonsNumber = userInfo[i].usri3_num_logons;
                std::string logonServer = UTF8::ToUTF8(userInfo[i].usri3_logon_server);
                std::uint32_t countryCode = userInfo[i].usri3_country_code;
                std::uint32_t codePage = userInfo[i].usri3_code_page;
                std::uint32_t userID = userInfo[i].usri3_user_id;
                std::uint32_t primaryGroupID = userInfo[i].usri3_primary_group_id;
                std::string profile = UTF8::ToUTF8(userInfo[i].usri3_profile);
                std::string homeDirDrive = UTF8::ToUTF8(userInfo[i].usri3_home_dir_drive);
                std::uint32_t passwordExpireInfo = userInfo[i].usri3_password_expired;

                std::vector<std::string> userGroups;
                LOCALGROUP_USERS_INFO_0* userGroupsBuff;
                DWORD groupEntries = 0;
                DWORD totalGroupEntries = 0;
                if (NetUserGetLocalGroups(nullptr, userInfo[i].usri3_name, 0,
                    LG_INCLUDE_INDIRECT, reinterpret_cast<LPBYTE*>(&userGroupsBuff),
                    MAX_PREFERRED_LENGTH, &groupEntries, &totalGroupEntries
                ) == NERR_Success) {
                    for (DWORD i = 0; i < groupEntries; i++) {
                        auto group = userGroupsBuff + i;
                        if (!group)
                            break;
                        userGroups.push_back(UTF8::ToUTF8(group->lgrui0_name));
                    }
                    NetApiBufferFree(userGroupsBuff);
                }

                auto user = User(
                    name, fullName, passwordAge, privileges, homeDir,
                    scriptPath, comment, userComment, flags, authFlags,
                    params, workstations, lastLogon, lastLogoff, expireTime,
                    maxStorage, unitsPerWeek, timeRestriction, badPasswordCount,
                    logonsNumber, logonServer, countryCode, codePage, userID,
                    primaryGroupID, profile, homeDirDrive, passwordExpireInfo,
                    userGroups
                );
                users.push_back(user);
            }

#ifndef SYSINFO_USE_CACHE
            auto
#endif
            osInfo = OSInfo(windowsVersion, users);
            return osInfo;
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