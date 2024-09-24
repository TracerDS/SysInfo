#pragma once

#include <SysInfo/dll.hpp>

namespace SysInfo::OS {
#pragma warning(push)
#pragma warning(disable: 4251)
    class EXPORT OSInfo : public Core::StructInit {
    public:
        class User {
        public:
            enum class PrivilegeLevel {
                GUEST,
                USER,
                ADMIN
            };
        protected:
        public:
            std::string m_name;
            std::string m_comment;
            std::string m_userComment;
            std::string m_homeDirectory;
        };
    protected:

    };
#pragma warning(pop)

    EXPORT std::future<OSInfo> GetOSInfoFuture() noexcept;
    EXPORT FUTURE(OSInfo) GetOSInfo() noexcept;
}
