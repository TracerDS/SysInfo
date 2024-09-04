#include "pch.hpp"
#include <SysInfo/dll.hpp>

namespace SysInfo {
	bool StructInit::IsInitialized() const noexcept {
		return m_initialized;
	}
}
