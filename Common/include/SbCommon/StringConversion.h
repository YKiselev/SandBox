#pragma once

#include <codecvt>
#include <string>

namespace sb_com
{
	std::wstring widen(const std::string& utf8);

	std::wstring widen(const char* utf8);

	std::string narrow(const std::wstring& src);

	std::string narrow(const wchar_t* src);
}