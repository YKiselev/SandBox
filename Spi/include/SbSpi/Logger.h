#pragma once

#include <memory>
#include <sstream>
#include "SharedObject.h"
#include "NonCopyable.h"
#include "SbCommon/Format.h"

namespace sb_spi
{
	class NamedLogger;

	//
	// Client logger API
	//
	class Logger
	{
	public:
		enum Level
		{
			Trace, Debug, Info, Warning, Error, Off
		};

		Logger() = default;
		Logger(NamedLogger* p);
		Logger(std::shared_ptr<NamedLogger> p);
		Logger(const Logger& src) = default;
		~Logger() = default;

		void delegateTo(std::shared_ptr<NamedLogger> p);
		void delegateTo(NamedLogger* p);

		template <typename... Args>
		void trace(const char* fmt, Args...args);
		void trace(const char* msg);

		template <typename... Args>
		void debug(const char* fmt, Args...args);
		void debug(const char* msg);

		template <typename... Args>
		void info(const char* fmt, Args...args);
		void info(const char* msg);

		template <typename... Args>
		void warning(const char* fmt, Args...args);
		void warning(const char* msg);

		template <typename... Args>
		void error(const char* fmt, Args...args);
		void error(const char* msg);

		template <typename... Args>
		void log(Level level, const char* fmt, Args... args);
		void log(Level level, const char* msg);

		void treshold(Level level);
		Level treshold();

	private:
		std::shared_ptr<NamedLogger> _delegate;
	};

	//
	// Named logger delegate used by Logger class
	//
	class NamedLogger : public virtual SharedObject
	{
	public:
		virtual Logger::Level treshold() const = 0;
		virtual void treshold(Logger::Level value) = 0;
		virtual const char* name() const = 0;
		virtual void log(Logger::Level level, const char* message) = 0;
	};

	//
	// Logger factory
	//
	class LoggerFactory : public NonCopyable
	{
	public:
		LoggerFactory() = default;
		LoggerFactory(const LoggerFactory&) = delete;
		virtual ~LoggerFactory() = default;

		LoggerFactory& operator = (const LoggerFactory&) = delete;

		virtual NamedLogger* getDelegate(const char* name) = 0;
	};

	//
	// Inline methods
	//
	template <typename... Args>
	inline void Logger::trace(const char* fmt, Args...args)
	{
		log(Trace, fmt, args...);
	}

	template <typename... Args>
	inline void Logger::debug(const char* fmt, Args...args)
	{
		log(Debug, fmt, args...);
	}

	template <typename... Args>
	inline void Logger::info(const char* fmt, Args...args)
	{
		log(Info, fmt, args...);
	}

	template <typename... Args>
	inline void Logger::warning(const char* fmt, Args...args)
	{
		log(Warning, fmt, args...);
	}

	template <typename... Args>
	inline void Logger::error(const char* fmt, Args...args)
	{
		log(Error, fmt, args...);
	}

	template <typename... Args>
	inline void Logger::log(Level level, const char* fmt, Args... args)
	{
		if (level >= treshold())
		{
			std::stringstream ss;
			sb_com::format(ss, fmt, args...);
			std::string s{ ss.str() };
			log(level, s.c_str());
		}
	}

	inline void Logger::trace(const char* msg)
	{
		log(Trace, msg);
	}

	inline void Logger::debug(const char* msg)
	{
		log(Debug, msg);
	}

	inline void Logger::info(const char* msg)
	{
		log(Info, msg);
	}

	inline void Logger::warning(const char* msg)
	{
		log(Warning, msg);
	}

	inline void Logger::error(const char* msg)
	{
		log(Error, msg);
	}

	inline void Logger::log(Level level, const char* msg)
	{
		NamedLogger* const p = _delegate.get();
		if (p && level >= p->treshold())
		{
			p->log(level, msg);
		}
	}
}