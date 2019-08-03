
#include <string>
#include <Windows.h>
#include "gtest/gtest.h"
#include "SbWindows/WindowsErrorFormat.h"

TEST(ErrorFormat, Simplet)
{
	std::wstring msg{ sb::sys::windows::fromError(123) };

	ASSERT_TRUE(msg.length() > 3);
}

