
#include "../include/SbCore/AppLoggerFactory.h"

using namespace sb_spi;

namespace
{
	class AppLoggerDelegate : public LoggerDelegate
	{
	public:
		AppLoggerDelegate() : _treshold{ Logger::Message }
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
			_treshold = value;
		}

		void doLog(Logger::Level level, const char* message) override
		{
			if (level >= _treshold)
			{
				// todo
			}
		}

	private:
		Logger::Level _treshold;
	};
}


namespace app
{
	AppLoggerFactory::AppLoggerFactory()
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
				p.reset(new AppLoggerDelegate());
			}
		}
	}
}

