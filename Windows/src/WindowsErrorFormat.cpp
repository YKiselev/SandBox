
#include <Windows.h>
#include "../include/SbWindows/WindowsErrorFormat.h"

namespace sb_win
{
	std::wstring fromError(DWORD code)
	{
		LPVOID lpMsgBuf;
		DWORD result = ::FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)& lpMsgBuf,
			0, NULL
		);

		std::wstring r{ static_cast<LPTSTR>(lpMsgBuf) };

		::LocalFree(lpMsgBuf);

		return r;
	}
}
