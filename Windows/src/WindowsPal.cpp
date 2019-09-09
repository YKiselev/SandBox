
#include "../include/SbWindows/WindowsPal.h"
#include <ShlObj.h>

namespace sb_pal
{
	std::filesystem::path getUserHome()
	{
		std::filesystem::path result;
		PWSTR buf = NULL;
		const HRESULT hr = ::SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &buf);
		if (hr == S_OK)
		{
			result = buf;
		}
		::CoTaskMemFree(buf);

		return result;
	}
}
