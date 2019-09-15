
#include "../include/SbCommon/StringConversion.h"
#include <codecvt>

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

	bool widen(const char* utf8, std::wstring& result)
	{
		result.clear();
		constexpr size_t bufferSize = 64;
		const const char* end = utf8 + std::char_traits<char>::length(utf8);
		std::codecvt_utf8_utf16<wchar_t> cvt;
		std::codecvt_utf8_utf16<wchar_t>::state_type state{};
		wchar_t buffer[bufferSize];
		auto input = utf8;
		do
		{
			auto output = buffer;
			auto r = cvt.in(state, input, end, input, buffer, buffer + bufferSize, output);
			if (r == std::codecvt_base::error)
			{
				return false;
			}
			result.append(buffer, output);
		} while (input < end);

		return true;
	}

	std::string narrow(const std::wstring& src)
	{
		return convert().to_bytes(src);
	}

	std::string narrow(const wchar_t* src)
	{
		return convert().to_bytes(src);
	}

	bool narrow(const wchar_t* src, std::string& result)
	{
		result.clear();
		constexpr size_t bufferSize = 64;
		const const wchar_t* end = src + std::char_traits<wchar_t>::length(src);
		std::codecvt_utf8_utf16<wchar_t> cvt;
		std::codecvt_utf8_utf16<wchar_t>::state_type state{};
		char buffer[bufferSize];
		auto input = src;
		do
		{
			auto output = buffer;
			auto r = cvt.out(state, input, end, input, buffer, buffer + bufferSize, output);
			if (r == std::codecvt_base::error)
			{
				return false;
			}
			result.append(buffer, output);
		} while (input < end);

		return true;
	}
}