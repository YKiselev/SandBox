#pragma once

#include <codecvt>
#include <string>

namespace sb_com
{
	std::wstring widen(const std::string& utf8)
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.from_bytes(utf8);
	}

	std::string narrow(const std::wstring& src)
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.to_bytes(src);
	}
}