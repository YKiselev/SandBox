#include "SbCommon/Format.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <regex>

using namespace std::string_literals;

TEST(Format, TooManySpecifiers)
{
	try
	{
		std::ostringstream s;

		sb_com::format(s, "%i");

		sb_com::format(s, "%i %d", 1);

		FAIL();
	}
	catch (sb_com::format_error& ex)
	{
		// ok
	}
}

TEST(Format, Mixed)
{
	std::ostringstream s;

	sb_com::format(s, "abc %i def", 123);

	ASSERT_EQ("abc 123 def"s, s.str());
}

TEST(Format, Integers)
{
	std::ostringstream s;

	sb_com::format(s, "%i %i %i %u %u %u", 1, 1l, 1ll, 1u, 1ul, 1ull);

	ASSERT_EQ("1 1 1 1 1 1"s, s.str());
}

TEST(Format, Unsigned)
{
	std::ostringstream s;

	sb_com::format(s, "%u %u %u %u %u %u", -1, -1l, -1ll, 1u, 1ul, 1ull);

	ASSERT_EQ("4294967295 4294967295 18446744073709551615 1 1 1"s, s.str());
}

TEST(Format, Octal)
{
	std::ostringstream s;

	sb_com::format(s, "%o %o %o %o %o %o", 9, 9l, 9ll, 9u, 9ul, 9ull);

	ASSERT_EQ("11 11 11 11 11 11"s, s.str());
}

TEST(Format, Hexadecimal)
{
	std::ostringstream s;

	sb_com::format(s, "%#X %#X %#X %#x %#x %#x", -1, -1l, -1ll, 17u, 17ul, 17ull);

	ASSERT_EQ("0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFFFFFFFFFF 0x11 0x11 0x11"s, s.str());
}

TEST(Format, Floats)
{
	std::ostringstream s;

	sb_com::format(s, "%f %f %f", 1.0, 1.0f, 1.0l);

	ASSERT_EQ("1.000000 1.000000 1.000000"s, s.str());
}

TEST(Format, HexadecimalFloats)
{
	std::ostringstream s;

	sb_com::format(s, "%A %a %a", 1.33, 1.33f, 1.33l);

	ASSERT_EQ("0X1.547AE1P+0 0x1.547ae2p+0 0x1.547ae1p+0"s, s.str());
}

TEST(Format, Fixed)
{
	std::ostringstream s;

	sb_com::format(s, "%+0*.*F_%5.2f", 8, 3, -3.1415168888, -3.14654321, 5.55);

	ASSERT_EQ("-003.142_-3.15"s, s.str());
}

TEST(Format, Scientific)
{
	std::ostringstream s;

	sb_com::format(s, "%+06.1E  %5.2e", -3.1415168888, 3.14654321);

	ASSERT_EQ("-3.1E+00  3.15e+00"s, s.str());
}

TEST(Format, Pointer)
{
	std::ostringstream s;

	int* p1 = (int*)0xabcd;
	void* p2 = (void*)0xbeef;

	sb_com::format(s, "%p %p", p1, p2);

	std::string result = s.str();
	std::regex re{ "[0]+ABCD [0]+BEEF" };
	std::cmatch m;

	ASSERT_TRUE(std::regex_match(result.c_str(), m, re));
}

TEST(Format, NoArgs)
{
	std::ostringstream s;

	sb_com::format(s, "abc");

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format, NullFormat)
{
	std::ostringstream s;

	sb_com::format(s, static_cast<char*>(nullptr));

	ASSERT_EQ(""s, s.str());
}

TEST(Format, Char)
{
	std::ostringstream s;

	sb_com::format(s, "%c%c%c", 'a', 'b', 'c');

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format, String)
{
	std::ostringstream s;

	sb_com::format(s, "%s%s%s", "a", "b", "c");

	ASSERT_EQ("abc"s, s.str());
}
//DISABLED_
TEST(Format, Perormance)
{
	{
		size_t counter = 0;
		std::ostringstream s;

		clock_t begin = clock();
		for (int i = 0; i < 10000; i++)
		{
			s.str("");
			s.clear();
			sb_com::format(s, "%i %u %f", i, i, double(i));
			counter += s.tellp();
		}
		clock_t end = clock();
		double elapsed_secs = (double(end) - begin) / CLOCKS_PER_SEC;
		std::cout << "Elapsed time: " << elapsed_secs << ", written " << counter << std::endl;
	}

	{
		size_t counter = 0;
		char buf[1000];

		clock_t begin = clock();
		for (int i = 0; i < 10000; i++)
		{
			int r = sprintf(buf, "%i %u %f", i, i, double(i));
			if (r > 0)
			{
				counter += r;
			}
		}
		clock_t end = clock();
		double elapsed_secs = (double(end) - begin) / CLOCKS_PER_SEC;
		std::cout << "Elapsed time: " << elapsed_secs << ", written " << counter << std::endl;
	}
}