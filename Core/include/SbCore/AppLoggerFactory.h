#pragma once

#include "SbSpi/Logger.h"
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <cstdio>


namespace app
{
	//
	// Logger sink
	//
	class LoggerSink : public sb_spi::NonCopyable
	{
	public:
		virtual void put(const char* name, sb_spi::Logger::Level level, const char* message) = 0;

	protected:
		const char* toString(sb_spi::Logger::Level level) const;
	};

	//
	// Chain of sinks
	//
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

	//
	// File-backed logger sink
	//
	class FileSink : public LoggerSink
	{
	public:
		FileSink(const std::string& name);
		virtual ~FileSink();

		void put(const char* name, sb_spi::Logger::Level level, const char* message) override;

	private:
		std::unique_ptr<FILE, decltype(&std::fclose)> _file;
	};

	//
	// Console-backed logger sink
	//
	class ConsoleSink : public LoggerSink
	{
	public:
		ConsoleSink();
		virtual ~ConsoleSink();

		void put(const char* name, sb_spi::Logger::Level level, const char* message) override;
	};

	//
	// App logger factory
	//
	class AppLoggerFactory : public sb_spi::LoggerFactory
	{
	public:
		AppLoggerFactory(std::shared_ptr<LoggerSink> sink);
		virtual ~AppLoggerFactory();

		sb_spi::NamedLogger* getDelegate(const char* name) override;

	private:
		mutable std::shared_mutex _mutex;
		std::unordered_map<std::string, std::unique_ptr<sb_spi::NamedLogger>> _delegates;
		std::shared_ptr<LoggerSink> _sink;
	};
}