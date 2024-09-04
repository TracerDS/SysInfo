#pragma once

#include <cstdint>
#include <cstdlib>
#include <bitset>
#include <array>
#include <unordered_map>
#include <string>
#include <iostream>

#ifdef _WIN32
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	include <windows.h>
#endif