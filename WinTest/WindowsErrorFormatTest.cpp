
#include <string>
#include <Windows.h>
#include "gtest/gtest.h"
#include "Sys/Windows/WindowsErrorFormat.h"

TEST(ErrorFormat, Simplet)
{
	std::wstring msg{ sb::common::errors::fromError(123) };

	ASSERT_TRUE(msg.length() > 3);
}

