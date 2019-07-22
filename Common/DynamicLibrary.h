#pragma once

#ifdef _WIN32
#include "sys/windows/WindowsDynamicLibrary.h"
#endif

namespace pg::commons
{
#ifdef _WIN32
	using DynamicLibrary = pg::commons::WindowsDynamicLibrary;
#endif
}
