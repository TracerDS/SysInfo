#pragma once

#include <SysInfo/dll.hpp>

namespace SysInfo::OS {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT OSInfo : public Core::StructInit {
    public:
        class WindowsVersion {
        public:
            enum class ProductType {
                UNKNOWN,
                WORKSTATION,
                DOMAIN_CONTROLLER,
                SERVER,
            };

            WindowsVersion() noexcept;

            WindowsVersion(
                const std::uint8_t& major,
                const std::uint16_t& minor,
                const std::uint16_t& build
            ) noexcept;

            WindowsVersion(
                const std::uint64_t& fullNumber
            ) noexcept;

            const std::uint8_t& GetMajor() const noexcept;
            const std::uint16_t& GetMinor() const noexcept;
            const std::uint16_t& GetBuild() const noexcept;

            bool operator==(const WindowsVersion& version) const noexcept;
            bool operator!=(const WindowsVersion& version) const noexcept;

            bool operator>(const WindowsVersion& version) const noexcept;
            bool operator>=(const WindowsVersion& version) const noexcept;

            bool operator<(const WindowsVersion& version) const noexcept;
            bool operator<=(const WindowsVersion& version) const noexcept;

            operator std::uint64_t() const noexcept;
        protected:
            std::uint8_t m_major;
            std::uint16_t m_minor;
            std::uint16_t m_build;
            std::uint64_t m_fullNumber;
        };

        class User {
        public:
            enum class PrivilegeLevel {
                GUEST,
                USER,
                ADMIN
            };
            struct TimeRestriction {
                bool H00_00;
                bool H01_00;
                bool H02_00;
                bool H03_00;
                bool H04_00;
                bool H05_00;
                bool H06_00;
                bool H07_00;
                bool H08_00;
                bool H09_00;
                bool H10_00;
                bool H11_00;
                bool H12_00;
                bool H13_00;
                bool H14_00;
                bool H15_00;
                bool H16_00;
                bool H17_00;
                bool H18_00;
                bool H19_00;
                bool H20_00;
                bool H21_00;
                bool H22_00;
                bool H23_00;
            };

            User(
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
            ) noexcept;

            const std::string& GetName() const noexcept;
            const std::string& GetFullName() const noexcept;
            const std::uint32_t& GetPasswordAge() const noexcept;
            const PrivilegeLevel& GetPrivileges() const noexcept;
            const std::string& GetHomeDir() const noexcept;
            const std::string& GetScriptPath() const noexcept;
            const std::string& GetComment() const noexcept;
            const std::string& GetUserComment() const noexcept;
            const std::uint32_t& GetFlags() const noexcept;
            const std::uint32_t& GetAuthFlags() const noexcept;
            const std::string& GetParams() const noexcept;
            const std::array<std::string, 8>& GetWorkstations() const noexcept;
            const std::uint32_t& GetLastLogon() const noexcept;
            const std::uint32_t& GetLastLogoff() const noexcept;
            const std::uint32_t& GetExpireTime() const noexcept;
            const std::uint32_t& GetMaxStorage() const noexcept;
            const std::uint32_t& GetUnitsPerWeek() const noexcept;
            const std::array<TimeRestriction, 7>& GetTimeRestriction() const noexcept;
            const std::uint32_t& GetBadPasswordCount() const noexcept;
            const std::uint32_t& GetLogonsNumber() const noexcept;
            const std::string& GetLogonServer() const noexcept;
            const std::uint32_t& GetCountryCode() const noexcept;
            const std::uint32_t& GetCodePage() const noexcept;
            const std::uint32_t& GetUserID() const noexcept;
            const std::uint32_t& GetPrimaryGroupID() const noexcept;
            const std::string& GetProfile() const noexcept;
            const std::string& GetHomeDirDrive() const noexcept;
            const std::uint32_t& GetPasswordExpireInfo() const noexcept;
            const std::vector<std::string>& GetUserGroups() const noexcept;

            static std::string PrivilegeLevelToString(const PrivilegeLevel& level) noexcept;
        protected:
            std::string m_name;
            std::string m_fullName;
            std::uint32_t m_passwordAge;
            PrivilegeLevel m_privileges;
            std::string m_homeDir;
            std::string m_scriptPath;
            std::string m_comment;
            std::string m_userComment;
            std::uint32_t m_flags;
            std::uint32_t m_authFlags;
            std::string m_params;
            std::array<std::string, 8> m_workstations;
            std::uint32_t m_lastLogon;
            std::uint32_t m_lastLogoff;
            std::uint32_t m_expireTime;
            std::uint32_t m_maxStorage;
            std::uint32_t m_unitsPerWeek;
            std::array<TimeRestriction, 7> m_timeRestriction;
            std::uint32_t m_badPasswordCount;
            std::uint32_t m_logonsNumber;
            std::string m_logonServer;
            std::uint32_t m_countryCode;
            std::uint32_t m_codePage;
            std::uint32_t m_userID;
            std::uint32_t m_primaryGroupID;
            std::string m_profile;
            std::string m_homeDirDrive;
            std::uint32_t m_passwordExpireInfo;
            std::vector<std::string> m_userGroups;
        };
    
        OSInfo(
            const WindowsVersion& windowsVersion,
            const std::vector<User>& users
        ) noexcept;

        const WindowsVersion& GetVersion() const noexcept;
        const std::vector<User>& GetUsers() const noexcept;
    protected:
        WindowsVersion m_windowsVersion;
        std::vector<User> m_users;
    };
#pragma warning(pop)

    EXPORT std::future<OSInfo> GetOSInfoFuture() noexcept;
    EXPORT FUTURE(OSInfo) GetOSInfo() noexcept;
}
