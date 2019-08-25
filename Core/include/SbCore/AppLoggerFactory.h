#pragma once

#include "SbSpi/Logger.h"
#include <shared_mutex>
#include <unordered_map>


namespace app
{
	class AppLoggerFactory : public sb_spi::LoggerFactory
	{
	public:
		AppLoggerFactory();
		virtual ~AppLoggerFactory();

		sb_spi::LoggerDelegate* getDelegate(const char* name) override;

	private:
		mutable std::shared_mutex _mutex;
		std::unordered_map<std::string, std::unique_ptr<sb_spi::LoggerDelegate>> _delegates;
	};
}