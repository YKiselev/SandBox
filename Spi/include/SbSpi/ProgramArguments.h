#pragma once

#include <filesystem>

namespace sb_spi
{
	struct ProgramArguments
	{
		//ProgramArguments(const std::filesystem::path curDir) : currentDir{ curDir }
		//{
		//}

		const std::filesystem::path currentDir;
	};
}