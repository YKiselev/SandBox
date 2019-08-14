#include "SbCommon/Format.h"
#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <cstdio>

TEST(Format, NoArgs)
{
	std::ostringstream s;

	sb_com::format2(s, "abc %+0*.*F  %5.2f\n", 8, 3, 3.1415168888, 3.14654321);

	//sb_com::format2(s, "%");

	std::cout << s.str() << '\n';

	s.str("");
	s.clear();

	sb_com::format2(s, "%+06.1E  %5.2e\n", 3.1415168888, 3.14654321);

	std::cout << s.str() << '\n';;
/*
	//sb_com::format(s, "Hello!");

	sb_com::format(s, "%", 1);

	s << 123.555 << '\n';

	//s.setf(std::ios_base::hex, std::ios_base::basefield);

	s << "42 in hex is "<< std::hex << 42 << '\n';

	s << "123 in hex is " << std::setw(20) << 123 << '\n';

	//s << std::resetiosflags(std::ios_base::basefield);

	s.setf(std::ios_base::fmtflags(0), std::ios_base::basefield);

	s << "42 in dec is " << 42 << '\n';

	s.precision(4);
	s.setf(std::ios_base::fixed, std::ios_base::floatfield);
	
	s << "3.1415161718 with precision of 4 is " << 3.1415161718 << '\n';

	//s << "3.1415161718 with precision of 3 is " << std::setprecision(3) << 3.1415161718 << '\n';

	std::cout << s.str();

	printf("printf(%+0*.*f)\n", 8, 2, 3.15611783);
	*/
}