#include "pch.hpp"
#include <SysInfo/dll.hpp>

namespace SysInfo::Core {
	bool StructInit::IsInitialized() const noexcept {
		return m_initialized;
	}
}
