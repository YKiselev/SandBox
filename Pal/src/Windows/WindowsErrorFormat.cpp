
#include "WindowsErrorFormat.h"
#include <Windows.h>
#include <vector>
#include <memory>
#include <functional>
#include "SbCommon/ScopeGuard.h"

namespace sb_win
{
	std::string fromError(DWORD code)
	{
		LPWSTR lpMsgBuf;
		DWORD result = ::FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_MAX_WIDTH_MASK,
			NULL,
			code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)& lpMsgBuf,
			0,
			NULL
		);
		std::unique_ptr<WCHAR, std::function<HLOCAL(HLOCAL)>> guard{ lpMsgBuf, ::LocalFree };
		if (result)
		{
			const int required = ::WideCharToMultiByte(CP_UTF8, 0, lpMsgBuf, -1, NULL, 0, NULL, NULL);
			if (required > 0)
			{
				std::vector<char> buf(static_cast<size_t>(required));
				const int length = ::WideCharToMultiByte(CP_UTF8, 0, lpMsgBuf, -1, buf.data(), buf.size(), NULL, NULL);
				if (length > 0)
				{
					return std::string(buf.data(), length);
				}
			}
		}
		return "<Unable to retrieve system message>";
	}
}
