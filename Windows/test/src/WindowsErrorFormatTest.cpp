
#include <string>
#include <Windows.h>
#include "gtest/gtest.h"
#include "SbWindows/WindowsErrorFormat.h"

TEST(ErrorFormat, Simple)
{
	std::string msg{ sb_win::fromError(123) };

	ASSERT_TRUE(msg.length() > 3);
}

