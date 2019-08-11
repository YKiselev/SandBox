#pragma once

#ifdef WIN32
	#include "SbWindows/WindowsDynamicLibrary.h"
#elif LINUX
	// todo ?
#endif

namespace sb_pal
{
#ifdef WIN32
	using DynamicLibrary = sb_win::WindowsDynamicLibrary;
#endif
}
