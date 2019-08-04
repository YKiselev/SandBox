
#include <string>
#include "gtest/gtest.h"
#include "SbCommon/FormatBuffer.h"

TEST(Format, VaList)
{
	sb_com::FormatBuffer fb;

	fb.format("%d %d %d %s\n", 1, 2, 3, "C string's are alive!");

	std::cout << fb;
}
