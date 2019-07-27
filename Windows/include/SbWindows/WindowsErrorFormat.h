#pragma once

#ifdef WIN32

#include <string>
#include <Windows.h>

namespace sb::common::sys::windows
{
	std::wstring fromError(DWORD code);
}

#endif // WIN32