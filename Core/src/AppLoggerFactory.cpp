
#include "../include/SbCore/AppLoggerFactory.h"
#include <atomic>


using namespace sb_spi;

namespace
{
	class DefaultNamedLogger : public NamedLogger
	{
	public:
		DefaultNamedLogger(app::LoggerSink& sink, const char* name) : _treshold{ Logger::Info }, _sink{ sink }, _name{ name }
		{
		}
		virtual ~DefaultNamedLogger()
		{
		}
		void release() override
		{
			// no-op
		}
		Logger::Level treshold() const override
		{
			return _treshold.load(std::memory_order_acquire);
		}
		void treshold(Logger::Level value) override
		{
			_treshold.store(value, std::memory_order_release);
		}
		void log(Logger::Level level, const char* message) override
		{
			if (level >= _treshold)
			{
				_sink.put(_name.c_str(), level, message);
			}
		}
		const char* name() const override
		{
			return _name.c_str();
		}

	private:
		std::atomic<Logger::Level> _treshold;
		app::LoggerSink& _sink;
		const std::string _name;
	};
}


namespace app
{
	const char* LoggerSink::toString(sb_spi::Logger::Level level) const
	{
		switch (level)
		{
		case sb_spi::Logger::Trace:
			return "TRACE";

		case sb_spi::Logger::Debug:
			return "DEBUG";

		case sb_spi::Logger::Info:
			return "INFO";

		case sb_spi::Logger::Warning:
			return "WARNING";

		case sb_spi::Logger::Error:
			return "ERROR";

		case sb_spi::Logger::Off:
			return "OFF";

		default:
			return nullptr;
		}
	}

	//
	// File sink
	//
	FileSink::FileSink(const std::string& name) : _file{ std::fopen(name.c_str(), "w") , std::fclose }
	{
	}
	FileSink::~FileSink()
	{

	}
	void FileSink::put(const char* name, sb_spi::Logger::Level level, const char* message)
	{
		std::fprintf(_file.get(), "%s %s : %s\n", name, toString(level), message);
	}

	//
	// Console sink
	//
	ConsoleSink::ConsoleSink()
	{
	}
	ConsoleSink::~ConsoleSink()
	{
	}
	void ConsoleSink::put(const char* name, sb_spi::Logger::Level level, const char* message)
	{
		std::printf("%s %s : %s\n", name, toString(level), message);
	}

	//
	// App logger factory
	//
	AppLoggerFactory::AppLoggerFactory(std::shared_ptr<LoggerSink> sink) : _sink{ sink }
	{
	}

	AppLoggerFactory::~AppLoggerFactory()
	{
	}

	NamedLogger* AppLoggerFactory::getDelegate(const char* name)
	{
		while (true)
		{
			{
				std::shared_lock lock{ _mutex };
				std::unique_ptr<NamedLogger>& p = _delegates[name];
				if (p)
				{
					return p.get();
				}
			}

			std::unique_lock lock{ _mutex };
			std::unique_ptr<NamedLogger>& p = _delegates[name];
			if (!p)
			{
				p.reset(new DefaultNamedLogger(*_sink, name));
			}
		}
	}
}

