
#include "../include/SbSpi/Logger.h"

namespace sb_spi
{
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