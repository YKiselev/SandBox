#pragma once

#include <string>
#include <iostream>

namespace sb::common
{
	class FormatBuffer final
	{
	public:
		FormatBuffer()
		{
		}
		FormatBuffer(const std::string& src) : buf{ src }
		{
		}

		void format(const char* fmt, ...);

		inline const std::string& buffer() const
		{
			return buf;
		}

	private:
		std::string buf;
	};

	inline std::ostream& operator << (std::ostream& out, const FormatBuffer& buf)
	{
		out << buf.buffer();
		return out;
	}
}