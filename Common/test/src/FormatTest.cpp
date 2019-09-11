#include "SbCommon/Format.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <regex>
#include "FormatTest.h"

using namespace std::string_literals;
using sb_com::format;

TEST(Format, NoArgTooManySpecifiers)
{
	try
	{
		std::ostringstream s;

		format(s, "{}");

		FAIL();
	}
	catch (std::out_of_range&)
	{
		// ok
	}
}

TEST(Format, TooManySpecifiers)
{
	try
	{
		std::ostringstream s;

		format(s, "{} {}", 1);

		FAIL();
	}
	catch (std::out_of_range&)
	{
		// ok
	}
}

TEST(Format, NonCapturingLambda)
{
	std::ostringstream s;

	format(s, "{}", []() { return "test"; });

	ASSERT_EQ("test"s, s.str());
}

TEST(Format, CapturingLambda)
{
	std::ostringstream s;
	std::string src{ "abc" };

	format(s, "{}", [&]() { return src; });

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format, Mixed)
{
	std::ostringstream s;

	format(s, "abc {} def", 123);

	ASSERT_EQ("abc 123 def"s, s.str());
}

TEST(Format, EscapedQuote)
{
	std::ostringstream s;

	format(s, "''abc''def''");

	ASSERT_EQ("'abc'def'"s, s.str());
}

TEST(Format, QuotedPLaceholders)
{
	std::ostringstream s;

	format(s, "'{'abc'{}'def'}'");

	ASSERT_EQ("{abc{}def}"s, s.str());
}

TEST(Format, Indexing)
{
	std::ostringstream s;

	format(s, "{3} {1} {2} {0}", 1, 2, 3, 4);

	ASSERT_EQ("4 2 3 1"s, s.str());
}

TEST(Format, Integers)
{
	std::ostringstream s;

	format(s, "{} {} {} {} {} {}", 1, 1l, 1ll, 1u, 1ul, 1ull);

	ASSERT_EQ("1 1 1 1 1 1"s, s.str());
}

TEST(Format, Unsigned)
{
	std::ostringstream s;

	format(s, "{} {} {} {} {} {}", unsigned(-1), unsigned long(-1l), unsigned long long(-1ll), 1u, 1ul, 1ull);

	ASSERT_EQ("4294967295 4294967295 18446744073709551615 1 1 1"s, s.str());
}

TEST(Format, Octal)
{
	std::ostringstream s;

	format(s, "{:o} {:o} {:o} {:o} {:o} {:o}", 9, 9l, 9ll, 9u, 9ul, 9ull);

	ASSERT_EQ("11 11 11 11 11 11"s, s.str());
}

TEST(Format, Hexadecimal)
{
	std::ostringstream s;

	format(s, "{:#X} {:X} {:#X} {:#x} {:x} {:#x}", -1, -1l, -1ll, 17u, 17ul, 17ull);

	ASSERT_EQ("0xFFFFFFFF FFFFFFFF 0xFFFFFFFFFFFFFFFF 0x11 11 0x11"s, s.str());
}

TEST(Format, Floats)
{
	std::ostringstream s;

	format(s, "{} {} {}", 1.0, 1.0f, 1.0l);

	ASSERT_EQ("1.000000 1.000000 1.000000"s, s.str());
}

TEST(Format, HexadecimalFloats)
{
	std::ostringstream s;

	format(s, "{:A} {:a} {:a}", 1.33, 1.33f, 1.33l);

	ASSERT_EQ("0X1.547AE1P+0 0x1.547ae2p+0 0x1.547ae1p+0"s, s.str());
}

TEST(Format, DISABLED_Fixed)
{
	std::ostringstream s;

	format(s, "{}_{}", 8, 3, -3.1415168888, 5, 2, -3.14654321);

	ASSERT_EQ("-003.142_-3.15"s, s.str());
}

TEST(Format, Scientific)
{
	std::ostringstream s;

	format(s, "{:+06.1E}  {:5.2e}", -3.1415168888, 3.14654321);

	ASSERT_EQ("-3.1E+00  3.15e+00"s, s.str());
}

TEST(Format, Pointer)
{
	std::ostringstream s;

	int* p1 = (int*)0xabcd;
	void* p2 = (void*)0xbeef;

	format(s, "{} {}", p1, p2);

	std::string result = s.str();
	std::regex re{ "[0]+ABCD [0]+BEEF" };
	std::cmatch m;

	ASSERT_TRUE(std::regex_match(result.c_str(), m, re));
}

TEST(Format, NoArgs)
{
	std::ostringstream s;

	format(s, "abc");

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format, NullFormat)
{
	std::ostringstream s;

	format(s, static_cast<char*>(nullptr));

	ASSERT_EQ(""s, s.str());
}

TEST(Format, Char)
{
	std::ostringstream s;

	format(s, "{}{}{}", 'a', 'b', 'c');

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format, String)
{
	std::ostringstream s;

	format(s, "{}{}{}", "a", "b", "c");

	ASSERT_EQ("abc"s, s.str());
}
//DISABLED_
TEST(Format, DISABLED_Perormance)
{
	double avg1 = 0, avg2 = 0;
	for (int t = 0; t < Tries; t++)
	{
		{
			size_t counter = 0;
			std::ostringstream s;

			clock_t begin = clock();
			for (int i = 0; i < Iterations; i++)
			{
				s.str("");
				s.clear();
				format(s, "{} {} {}", i, unsigned(i), double(i));
				counter += s.tellp();
			}
			clock_t end = clock();
			double elapsed_secs = (double(end) - begin) / CLOCKS_PER_SEC;
			avg1 += elapsed_secs;
			std::cout << "Elapsed time (format2): " << elapsed_secs << ", written " << counter << std::endl;
		}

		{
			size_t counter = 0;
			char buf[1000];

			clock_t begin = clock();
			for (int i = 0; i < Iterations; i++)
			{
				int r = sprintf(buf, "%i %u %f", i, i, double(i));
				if (r > 0)
				{
					counter += r;
				}
			}
			clock_t end = clock();
			double elapsed_secs = (double(end) - begin) / CLOCKS_PER_SEC;
			avg2 += elapsed_secs;
			std::cout << "Elapsed time (sprintf): " << elapsed_secs << ", written " << counter << std::endl;
		}
	}
	std::cout << "Avg Elapsed time (format2): " << (avg1 / Tries) << ", (sprintf) " << (avg2 / Tries) << std::endl;
}
