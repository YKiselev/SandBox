#pragma once

#include <cstring>

namespace sb_com
{
	//
	// Fixed capacity string
	//
	template <size_t N>
	struct FixedString final
	{
		FixedString() noexcept
		{
			set("");
		}
		explicit FixedString(const char* src) noexcept
		{
			set(src);
		}
		bool set(const char* src) noexcept
		{
			return append(0, src);
		}
		size_t length() const noexcept
		{
			return _length;
		}
		bool append(const char* src) noexcept
		{
			return append(_length, src);
		}
		const char* c_str() const noexcept
		{
			return _buffer;
		}
		constexpr size_t capacity() const noexcept
		{
			return N;
		}
		operator const char* () const noexcept
		{
			return _buffer;
		}
		int compare(const char* src) const noexcept
		{
			return std::strcmp(_buffer, src);
		}
		bool operator == (const char* src) const noexcept
		{
			return compare(src) == 0;
		}
		bool operator != (const char* src) const noexcept
		{
			return compare(src) != 0;
		}
	private:
		char _buffer[N];
		size_t _length{ 0 };

		bool append(size_t fromIndex, const char* src) noexcept
		{
			const size_t required = std::strlen(src) + 1;
			const size_t available = N - _length;
			const bool result = required <= available;
			if (result)
			{
				std::strncpy(_buffer + _length, src, required);
				_length += required - 1;
			}
			else
			{
				std::strncpy(_buffer + _length, src, available - 1);
				_buffer[N - 1] = 0;
				_length = N - 1;
			}
			return result;
		}
	};
}