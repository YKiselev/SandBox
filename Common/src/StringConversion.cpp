
#include "../include/SbCommon/StringConversion.h"

namespace
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert()
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{};
	}
}

namespace sb_com
{
	std::wstring widen(const std::string& utf8)
	{
		return convert().from_bytes(utf8);
	}

	std::wstring widen(const char* utf8)
	{
		return convert().from_bytes(utf8);
	}

	std::string narrow(const std::wstring& src)
	{
		return convert().to_bytes(src);
	}

	std::string narrow(const wchar_t* src)
	{
		return convert().to_bytes(src);
	}
}