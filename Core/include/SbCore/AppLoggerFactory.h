#pragma once

#include "SbSpi/Logger.h"
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <cstdio>


namespace app
{
	class LoggerSink : public sb_spi::NonCopyable
	{
	public:
		virtual void put(const char* name, sb_spi::Logger::Level level, const char* message) = 0;
	};

	class ChainSink : public LoggerSink
	{
	public:
		ChainSink(const std::vector<std::shared_ptr<LoggerSink>>& args) : _sinks{ args }
		{
		}
		ChainSink(std::initializer_list<std::shared_ptr<LoggerSink>> args) : _sinks{ args }
		{
		}
		virtual ~ChainSink()
		{
		}

		void put(const char* name, sb_spi::Logger::Level level, const char* message) override
		{
			for (std::shared_ptr<LoggerSink>& sink : _sinks)
			{
				sink->put(name, level, message);
			}
		}

	private:
		std::vector<std::shared_ptr<LoggerSink>> _sinks;
	};

	class FileSink : public LoggerSink
	{
	public:
		FileSink(const std::string& name);
		virtual ~FileSink();

		void put(const char* name, sb_spi::Logger::Level level, const char* message) override;

	private:
		std::unique_ptr<FILE, decltype(&std::fclose)> _file;
	};

	class ConsoleSink : public LoggerSink
	{
	public:
		ConsoleSink();
		virtual ~ConsoleSink();

		void put(const char* name, sb_spi::Logger::Level level, const char* message) override;
	};

	class AppLoggerFactory : public sb_spi::LoggerFactory
	{
	public:
		AppLoggerFactory(std::shared_ptr<LoggerSink> sink);
		virtual ~AppLoggerFactory();

		sb_spi::LoggerDelegate* getDelegate(const char* name) override;

	private:
		mutable std::shared_mutex _mutex;
		std::unordered_map<std::string, std::unique_ptr<sb_spi::LoggerDelegate>> _delegates;
		std::shared_ptr<LoggerSink> _sink;
	};
}