
#include <cstdarg>
#include <cstdio>
#include "SbCommon/FormatBuffer.h"

/*
	See int vswprintf(wchar_t *restrict ws, size_t n, const wchar_t *restrict format, va_list arg);
*/
void sb_com::FormatBuffer::format(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	va_list args2;
	va_copy(args2, args);
	buf.resize(buf.capacity());
	const int required = ::vsnprintf(buf.data(), buf.capacity(), fmt, args2);
	va_end(args2);
	if (required < 0)
	{
		buf.clear();// = "<formatting failed>";
	}
	else
	{
		const int newSize = required + 1;
		buf.resize(newSize);
		const int result = ::vsnprintf(buf.data(), buf.capacity(), fmt, args);
		buf.resize(result);
	}
	va_end(args);
}
