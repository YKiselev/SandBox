#pragma once

#include <string>

namespace sb_com
{
	std::wstring widen(const std::string& utf8);

	std::wstring widen(const char* utf8);

	bool widen(const char* utf8, std::wstring& result);

	std::string narrow(const std::wstring& src);

	std::string narrow(const wchar_t* src);

	bool narrow(const wchar_t* src, std::string& result);
}