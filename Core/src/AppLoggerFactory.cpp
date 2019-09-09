
#include "../include/SbCore/AppLoggerFactory.h"
#include <atomic>


using namespace sb_spi;

namespace
{
	class AppLoggerDelegate : public LoggerDelegate
	{
	public:
		AppLoggerDelegate(app::LoggerSink& sink, const char* name) : _treshold{ Logger::Message }, _sink{ sink }, _name{ name }
		{
		}
		virtual ~AppLoggerDelegate()
		{
		}
		void release() override
		{
			// no-op
		}
		Logger::Level treshold() const override
		{
			return _treshold;
		}
		void treshold(Logger::Level value) override
		{
			_treshold.store(value);
		}
		void doLog(Logger::Level level, const char* message) override
		{
			if (level >= _treshold)
			{
				_sink.put(_name.c_str(), level, message);
			}
		}

	private:
		std::atomic<Logger::Level> _treshold;
		app::LoggerSink& _sink;
		const std::string _name;
	};
}


namespace app
{
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
		std::fprintf(_file.get(), "%s %i : %s\n", name, level, message);
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
		std::printf("%s %i : %s\n", name, level, message);
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

	LoggerDelegate* AppLoggerFactory::getDelegate(const char* name)
	{
		while (true)
		{
			{
				std::shared_lock lock{ _mutex };
				std::unique_ptr<LoggerDelegate>& p = _delegates[name];
				if (p)
				{
					return p.get();
				}
			}

			std::unique_lock lock{ _mutex };
			std::unique_ptr<LoggerDelegate>& p = _delegates[name];
			if (!p)
			{
				p.reset(new AppLoggerDelegate(*_sink, name));
			}
		}
	}
}

