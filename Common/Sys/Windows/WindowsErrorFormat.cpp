
#ifdef WIN32

#include "WindowsErrorFormat.h"

namespace sb::common::errors
{
	std::wstring fromError(DWORD code)
	{
		LPVOID lpMsgBuf;
		DWORD result = ::FormatMessage(
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

#endif //  WIN32