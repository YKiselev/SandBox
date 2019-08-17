#include "SbCommon/Format2.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <regex>

using namespace std::string_literals;

TEST(Format2, TooManySpecifiers)
{
	try
	{
		std::ostringstream s;

		sb_com::format(s, "{}");//???????

		sb_com::format(s, "{} {}", 1);

		FAIL();
	}
	catch (std::out_of_range&)
	{
		// ok
	}
}

TEST(Format2, Mixed)
{
	std::ostringstream s;

	sb_com::format(s, "abc {} def", 123);

	ASSERT_EQ("abc 123 def"s, s.str());
}

TEST(Format2, EscapedQuote)
{
	std::ostringstream s;

	sb_com::format(s, "''abc''def''");

	ASSERT_EQ("'abc'def'"s, s.str());
}

TEST(Format2, QuotedPLaceholders)
{
	std::ostringstream s;

	sb_com::format(s, "'{'abc'{}'def'}'");

	ASSERT_EQ("{abc{}def}"s, s.str());
}

TEST(Format2, Indexing)
{
	std::ostringstream s;

	sb_com::format(s, "{3} {1} {2} {0}", 1, 2, 3, 4);

	ASSERT_EQ("4 2 3 1"s, s.str());
}

TEST(Format2, Integers)
{
	std::ostringstream s;

	sb_com::format(s, "{} {} {} {} {} {}", 1, 1l, 1ll, 1u, 1ul, 1ull);

	ASSERT_EQ("1 1 1 1 1 1"s, s.str());
}

TEST(Format2, Unsigned)
{
	std::ostringstream s;

	sb_com::format(s, "{} {} {} {} {} {}", unsigned(-1), unsigned long(-1l), unsigned long long(-1ll), 1u, 1ul, 1ull);

	ASSERT_EQ("4294967295 4294967295 18446744073709551615 1 1 1"s, s.str());
}

TEST(Format2, Octal)
{
	std::ostringstream s;

	sb_com::format(s, "{:o} {:o} {:o} {:o} {:o} {:o}", 9, 9l, 9ll, 9u, 9ul, 9ull);

	ASSERT_EQ("11 11 11 11 11 11"s, s.str());
}

TEST(Format2, Hexadecimal)
{
	std::ostringstream s;

	sb_com::format(s, "{:#X} {:X} {:#X} {:#x} {:x} {:#x}", -1, -1l, -1ll, 17u, 17ul, 17ull);

	ASSERT_EQ("0xFFFFFFFF FFFFFFFF 0xFFFFFFFFFFFFFFFF 0x11 11 0x11"s, s.str());
}

TEST(Format2, Floats)
{
	std::ostringstream s;

	sb_com::format(s, "{} {} {}", 1.0, 1.0f, 1.0l);

	ASSERT_EQ("1.000000 1.000000 1.000000"s, s.str());
}

TEST(Format2, HexadecimalFloats)
{
	std::ostringstream s;

	sb_com::format(s, "{:A} {:a} {:a}", 1.33, 1.33f, 1.33l);

	ASSERT_EQ("0X1.547AE1P+0 0x1.547ae2p+0 0x1.547ae1p+0"s, s.str());
}

TEST(Format2, DISABLED_Fixed)
{
	std::ostringstream s;

	sb_com::format(s, "{}_{}", 8, 3, -3.1415168888, 5, 2, -3.14654321);

	ASSERT_EQ("-003.142_-3.15"s, s.str());
}

TEST(Format2, Scientific)
{
	std::ostringstream s;

	sb_com::format(s, "{:+06.1E}  {:5.2e}", -3.1415168888, 3.14654321);

	ASSERT_EQ("-3.1E+00  3.15e+00"s, s.str());
}

TEST(Format2, Pointer)
{
	std::ostringstream s;

	int* p1 = (int*)0xabcd;
	void* p2 = (void*)0xbeef;

	sb_com::format(s, "{} {}", p1, p2);

	std::string result = s.str();
	std::regex re{ "[0]+ABCD [0]+BEEF" };
	std::cmatch m;

	ASSERT_TRUE(std::regex_match(result.c_str(), m, re));
}

TEST(Format2, NoArgs)
{
	std::ostringstream s;

	sb_com::format(s, "abc");

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format2, NullFormat)
{
	std::ostringstream s;

	sb_com::format(s, static_cast<char*>(nullptr));

	ASSERT_EQ(""s, s.str());
}

TEST(Format2, Char)
{
	std::ostringstream s;

	sb_com::format(s, "{}{}{}", 'a', 'b', 'c');

	ASSERT_EQ("abc"s, s.str());
}

TEST(Format2, String)
{
	std::ostringstream s;

	sb_com::format(s, "{}{}{}", "a", "b", "c");

	ASSERT_EQ("abc"s, s.str());
}
//DISABLED_
TEST(Format2, Perormance)
{
	const int iterations = 150000, tries = 3;
	double avg1 = 0, avg2 = 0;
	for (int t = 0; t < tries; t++)
	{
		{
			size_t counter = 0;
			std::ostringstream s;

			clock_t begin = clock();
			for (int i = 0; i < iterations; i++)
			{
				s.str("");
				s.clear();
				sb_com::format(s, "{} {} {}", i, unsigned(i), double(i));
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
			for (int i = 0; i < iterations; i++)
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
	std::cout << "Avg Elapsed time (format2): " << (avg1 / tries) << ", (sprintf) " << (avg2 / tries) << std::endl;
}
