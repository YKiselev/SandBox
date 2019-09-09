#pragma once

#include "Logger.h"
#include "PersistedConfiguration.h"
#include "FileSystem.h"
#include "ProgramArguments.h"

namespace sb_spi
{
	struct CoreServices
	{
		const ProgramArguments* arguments;
		LoggerFactory* loggerFactory;
		PersistedConfiguration* configuration;
		FileSystem* fileSystem;
	};
}