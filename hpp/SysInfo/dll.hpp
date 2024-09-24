#pragma once

// Supported macros:
// SYSINFO_USE_CACHE
// SYSINFO_USE_FUTURE
// SYSINFO_PRE_INIT

#ifdef SYSINFO_BUILD
#	define EXPORT __declspec(dllexport)
#else
#	define EXPORT __declspec(dllimport)
#endif
#include <future>

#ifdef SYSINFO_USE_FUTURE
#	define FUTURE(x) std::future<x>
#else
#	define FUTURE(x) x
#endif

namespace SysInfo::Core {
	class EXPORT StructInit {
	public:
		bool IsInitialized() const noexcept;
	protected:
		bool m_initialized;
	};
}