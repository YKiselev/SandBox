
#include <string>
#include "gtest/gtest.h"
#include "SbCommon/FormatBuffer.h"

TEST(Format, VaList)
{
	sb_com::FormatBuffer fb;

	fb.format("%i %x %.1f %.3f %s", 1, 31, 2.51f, 3.333, "abc");

	//ASSERT_EQ("1 1f 2.5 3.333 abc", fb.buffer());
}
