#pragma once

#ifdef SYSINFO_BUILD
#	define EXPORT __declspec(dllexport)
#else
#	define EXPORT __declspec(dllimport)
#endif

#ifdef SYSINFO_USE_FUTURE
#	include <future>
#	define FUTURE(x) std::future<x>
#	define FUTURE_FUNC(x) std::async(std::launch::async, []{ return x; })
#else
#	define FUTURE(x) x
#	define FUTURE_FUNC(x) x
#endif

namespace SysInfo {
	class EXPORT StructInit {
	public:
		virtual bool IsInitialized() const noexcept;
	protected:
		bool m_initialized;
	};
}