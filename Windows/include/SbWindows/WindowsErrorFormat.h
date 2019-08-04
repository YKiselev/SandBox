#pragma once

#ifdef WIN32

#include <string>
#include <Windows.h>

namespace sb_win
{
	std::wstring fromError(DWORD code);
}

#endif // WIN32