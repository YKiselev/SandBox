
#include "../../include/SbPal/Pal.h"
#include <ShlObj.h>
#include "SbCommon/StringConversion.h"

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

	std::FILE* open(const char* name, const char* mode)
	{
		std::wstring n{ sb_com::widen(name) }, m{ sb_com::widen(mode) };
		return _wfopen(n.c_str(), m.c_str());
	}
}
