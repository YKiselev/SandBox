
#include "SbCommon/FixedString.h"
#include "gtest/gtest.h"

using namespace sb_com;

TEST(FixedString, ConstructFromLiteral)
{
	FixedString<16> fs{ "abc" };

	ASSERT_EQ(std::string{ "abc" }, fs.c_str());
	ASSERT_EQ(3, fs.length());
}

TEST(FixedString, Truncate)
{
	FixedString<3> fs{ "abcd" };

	ASSERT_EQ(std::string{ "ab" }, fs.c_str());
	ASSERT_EQ(2, fs.length());
}

TEST(FixedString, Compare)
{
	FixedString<8> fs{ "abc" };

	ASSERT_EQ(0, fs.compare("abc"));
	ASSERT_EQ(1, fs.compare("aaa"));
	ASSERT_EQ(-1, fs.compare("bbb"));
}

TEST(FixedString, AppendTrim)
{
	FixedString<4> fs{ "ab" };

	ASSERT_FALSE(fs.append("cd"));
	ASSERT_EQ(std::string{ "abc" }, fs.c_str());
	ASSERT_EQ(3, fs.length());
}

TEST(FixedString, Append)
{
	FixedString<5> fs{ "ab" };

	ASSERT_TRUE(fs.append("cd"));
	ASSERT_EQ(std::string{ "abcd" }, fs.c_str());
	ASSERT_EQ(4, fs.length());
}