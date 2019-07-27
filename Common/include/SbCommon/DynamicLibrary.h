#pragma once

#ifdef WIN32
	#include "Sys/Windows/WindowsDynamicLibrary.h"
#elseif LINUX
	// todo ?
#endif

namespace sb::common
{
#ifdef WIN32
	using DynamicLibrary = sb::common::sys::win::WindowsDynamicLibrary;
#endif
}
