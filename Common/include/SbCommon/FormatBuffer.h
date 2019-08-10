#pragma once

#include <string>
#include <vector>
#include <cstdio>
//#include <iostream>

namespace sb_com
{
	class FormatBuffer final
	{
	public:
		FormatBuffer()
		{
		}
		FormatBuffer(std::size_t size) : buf(size)
		{
		}

		void format(const char* fmt, ...);

		inline const std::vector<char>& buffer() const
		{
			return buf;
		}

	private:
		std::vector<char> buf;
	};

	/*
	inline std::ostream& operator << (std::ostream& out, const FormatBuffer<char>& buf)
	{
		out << buf.buffer();
		return out;
	}
	*/
}