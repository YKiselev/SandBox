#pragma once

#include <filesystem>
#include <cstdio>

namespace sb_pal
{
	//
	// Gets user home folder. On Windows returns %LOCALAPPDATA% folder location.
	//
	std::filesystem::path getUserHome();

	//
	// Opens file with specified mode
	// @param name the file name
	// @param mode the file mode (see std::fopen)
	//
	std::FILE* open(const char* name, const char* mode);
}