#pragma once

#ifdef SYSINFO_BUILD
#	define EXPORT __declspec(dllexport)
#else
#	define EXPORT __declspec(dllimport)
#endif
#include <future>

#ifdef SYSINFO_USE_FUTURE
#	define FUTURE(x) std::future<x>
#	define FUTURE_FUNC(x) std::async(std::launch::async, []{ return x; })
#else
#	define FUTURE(x) x
#	define FUTURE_FUNC(x) x
#endif

namespace SysInfo {
	class EXPORT StructInit {
	public:
		bool IsInitialized() const noexcept;
	protected:
		bool m_initialized;
	};
}