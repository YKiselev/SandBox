#include "../include/SbSpi/Logger.h"

namespace
{
	class DefaultLogger : public sb_spi::Logger
	{
	public:
		DefaultLogger();
		virtual ~DefaultLogger() override;

		virtual void level(Level level) override;
		virtual Level level() override;

	protected:
		virtual void doLog(Level level, const char* fmt, ...) override;

	private:
		Level _level;
	};

	DefaultLogger::DefaultLogger() : _level{ Message }
	{
	}

	DefaultLogger::~DefaultLogger()
	{
	}

	void DefaultLogger::level(Level level)
	{
		_level = level;
	}

	sb_spi::Logger::Level DefaultLogger::level()
	{
		return _level;
	}

	void DefaultLogger::doLog(Level level, const char* fmt, ...)
	{
		// todo?
	}
}

namespace sb_spi
{
}