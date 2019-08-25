#pragma once

namespace sb_con
{
	// Fixed capacity string
	struct FixedString final
	{
		FixedString(size_t capacity) : _capacity{ capacity }, _buffer{ new char[capacity] }
		{
		}
		FixedString(const char* src) : FixedString{ strlen(src) + 1 }
		{
			strcpy(_buffer, src);
		}
		~FixedString()
		{
			delete[] _buffer;
			_buffer = nullptr;
			_capacity = 0;
		}

		bool set(const char* src)
		{
			const size_t length = strlen(src) + 1;
			const bool result = length <= _capacity;
			if (result)
			{
				strncpy(_buffer, src, length);
			}
			else
			{
				strncpy(_buffer, src, _capacity - 1);
				_buffer[_capacity - 1] = 0;
			}
			strcpy(_buffer, src);
			return result;
		}

	private:
		size_t _capacity;
		char* _buffer;
	};
}