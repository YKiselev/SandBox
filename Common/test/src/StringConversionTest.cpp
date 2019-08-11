
#include "SbCommon/StringConversion.h"
#include "gtest/gtest.h"

using namespace std::string_literals;

TEST(StringConversion, Narrow)
{
	ASSERT_EQ("z\xC3\x9F\xE6\xB0\xB4", sb_com::narrow(L"z\u00df\u6c34"));
}

TEST(StringConversion, Widen)
{
	ASSERT_EQ(L"z\u00df\u6c34", sb_com::widen(u8"z\u00df\u6c34"));
}
