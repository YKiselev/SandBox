#pragma once

#ifdef WIN32

#include <string>
#include <Windows.h>

namespace sb::sys::windows
{
	std::wstring fromError(DWORD code);
}

#endif // WIN32