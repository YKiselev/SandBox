#pragma once

#include <memory>
#include <sstream>
#include "SharedObject.h"
#include "SbCommon/Format.h"

namespace sb_spi
{
	class LoggerDelegate;

	// Client logger API
	class Logger
	{
	public:
		enum Level
		{
			Trace, Debug, Message, Warning, Error, Off
		};

		Logger() = default;
		Logger(LoggerDelegate* p);
		Logger(std::shared_ptr<LoggerDelegate> p);

		void delegateTo(std::shared_ptr<LoggerDelegate> p);
		void delegateTo(LoggerDelegate* p);

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

		void treshold(Level level);
		Level treshold();

	private:
		std::shared_ptr<LoggerDelegate> _delegate;
	};

	// Logger delegate used by Logger class
	class LoggerDelegate : public virtual SharedObject
	{
	public:
		virtual Logger::Level treshold() const = 0;
		virtual void treshold(Logger::Level value) = 0;
		virtual void doLog(Logger::Level level, const char* message) = 0;
	};

	// Logger factory
	class LoggerFactory
	{
	public:
		LoggerFactory() = default;
		LoggerFactory(const LoggerFactory&) = delete;
		virtual ~LoggerFactory() = default;

		LoggerFactory& operator = (const LoggerFactory&) = delete;

		virtual LoggerDelegate* getDelegate(const char* name) = 0;
	};

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
	inline void Logger::message(const char* fmt, Args...args)
	{
		log(Message, fmt, args...);
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

	Logger::Logger(LoggerDelegate* p) : Logger(make_shared(p))
	{
	}

	Logger::Logger(std::shared_ptr<LoggerDelegate> p) : _delegate{ p }
	{
	}

	void Logger::delegateTo(std::shared_ptr<LoggerDelegate> p)
	{
		_delegate = p;
	}

	void Logger::delegateTo(LoggerDelegate* p)
	{
		delegateTo(make_shared(p));
	}

	inline void Logger::trace(const char* msg)
	{
		log(Trace, msg);
	}

	inline void Logger::debug(const char* msg)
	{
		log(Debug, msg);
	}

	inline void Logger::message(const char* msg)
	{
		log(Debug, msg);
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
		LoggerDelegate* const p = _delegate.get();
		if (p && level >= p->treshold())
		{
			p->doLog(level, msg);
		}
	}

	void Logger::treshold(Level value)
	{
		LoggerDelegate* const p = _delegate.get();
		if (p)
		{
			p->treshold(value);
		}
	}

	Logger::Level Logger::treshold()
	{
		LoggerDelegate* const p = _delegate.get();
		if (p)
		{
			return p->treshold();
		}
		return Off;
	}
}