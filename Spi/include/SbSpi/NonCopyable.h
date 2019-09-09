#pragma once

namespace sb_spi
{
	//
	// Deletes copy (and move) constructor and assignment (and move) operator.
	//
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator = (const NonCopyable& src) = delete;
	};
}