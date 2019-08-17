#pragma once

#include <cstdarg>
#include <memory>

namespace sb_spi
{
	class Logger
	{
	public:
		enum Level
		{
			Trace, Debug, Message, Warning, Error
		};
		
		Logger() = default;
		Logger(const Logger&) = delete;
		virtual ~Logger() = default;

		Logger& operator =(const Logger&) = delete;

		template <typename... Args>
		void trace(const char* fmt, Args...args);
		void trace(const char* msg);

		template <typename... Args>
		void debug(const char* fmt, Args...args);
		void debug(const char* msg);

		template <typename... Args>
		void message(const char* fmt, Args...args);
		void message(const char* msg);

		template <typename... Args>
		void warning(const char* fmt, Args...args);
		void warning(const char* msg);

		template <typename... Args>
		void error(const char* fmt, Args...args);
		void error(const char* msg);

		template <typename... Args>
		void log(Level level, const char* fmt, Args... args);
		void log(Level level, const char* msg);
		
		virtual void level(Level level) = 0;
		virtual Level level() = 0;

	protected:
		virtual void doLog(Level level, const char* fmt, ...) = 0;
	};

	inline void Logger::trace(const char* msg)
	{
		log(Trace, msg);
	}

	template <typename... Args>
	inline void Logger::trace(const char* fmt, Args...args)
	{
		log(Trace, fmt, args);
	}

	template <typename... Args>
	inline void Logger::debug(const char* fmt, Args...args)
	{
		log(Debug, fmt, va);
	}

	inline void Logger::debug(const char* msg)
	{
		log(Debug, msg);
	}

	template <typename... Args>
	inline void Logger::message(const char* fmt, Args...args)
	{
		log(Debug, fmt, args);
	}

	inline void Logger::message(const char* msg)
	{
		log(Debug, msg);
	}

	template <typename... Args>
	inline void Logger::warning(const char* fmt, Args...args)
	{
		log(Warning, fmt, args);
	}

	inline void Logger::warning(const char* msg)
	{
		log(Warning, msg);
	}

	template <typename... Args>
	inline void Logger::error(const char* fmt, Args...args)
	{
		log(Error, fmt, args);
	}

	inline void Logger::error(const char* msg)
	{
		log(Error, msg);
	}

	template <typename... Args>
	inline void Logger::log(Level level, const char* fmt, Args... args)
	{
		if (level() >= level)
		{
			doLog(level, fmt, args...);
		}
	}
	inline void Logger::log(Level level, const char* msg)
	{
		doLog(level, msg);
	}

	class LoggerFactory
	{
	public:
		LoggerFactory() = default;
		LoggerFactory(const LoggerFactory&) = delete;
		virtual ~LoggerFactory() = default;

		LoggerFactory& operator = (const LoggerFactory&) = delete;

		virtual std::shared_ptr<Logger> getLogger(const char* name) = 0;
	};

}