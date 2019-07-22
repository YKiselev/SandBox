
#include <string>
#include "gtest/gtest.h"
#include "FormatBuffer.h"

TEST(Format, VaList)
{
	pg::commons::FormatBuffer fb;

	fb.format("%d %d %d %s\n", 1, 2, 3, "C string's are alive!");

	std::cout << fb;
}

template <typename S, typename C = S::char_type>
void format(S & out, const C * p)
{
	if (!p)
	{
		return;
	}
	while (*p)
	{
		if (*p == '%' && *++p != '%')
		{
			throw std::runtime_error("extra arguments provided to printf");
		}
		out << *p++;
	}
}

template <typename S, typename C = S::char_type, typename Arg, typename... Args>
void format(S& out, const C* fmt, Arg arg, Args...args)
{
	while (fmt && *fmt)
	{
		if (*fmt == '%' && *++fmt != '%')
		{
			out << arg;
			format(out, fmt, args...);
			return;
		}
		out << *fmt++;
	}
	throw std::runtime_error("extra arguments provided to printf");
}

class X
{
public:
	X(int src) : _value{ src }
	{
	}

	int value() const
	{
		return _value;
	}
private:
	int _value;
};

std::ostream& operator<< (std::ostream& s, const X& x)
{
	s << x.value();
	return s;
}

std::wostream& operator<< (std::wostream& s, const X& x)
{
	s << x.value();
	return s;
}

TEST(Format, Char)
{
	using namespace std::string_literals;

	format(std::cout, "abc%%\n");
	format(std::cout, "name is %\n", "John");
	format(std::cout, "it's % past %\n", 2, 3);

	X x{ 33 };

	format(std::cout, "%=%\n", "amount"s, x);

	//format(std::cout, "bad %\n");
	//format(std::cout, "bad%, %\n", 2);
	//format(std::cout, "bad%, %=%\n", 3, 1);
}

TEST(Format, Wchar)
{
	using namespace std::string_literals;

	format(std::wcout, L"abc%%\n");
	format(std::wcout, L"name is %\n", L"John");
	format(std::wcout, L"it's % past %\n", 2, 3);

	X x{ 33 };

	format(std::wcout, L"%=%\n", L"amount"s, x);

	//format(std::cout, "bad %\n");
	//format(std::cout, "bad%, %\n", 2);
	//format(std::cout, "bad%, %=%\n", 3, 1);
}

