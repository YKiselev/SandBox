
#include "../include/SbSpi/Logger.h"

namespace sb_spi
{
	Logger::Logger(NamedLogger* p) : Logger(make_shared(p))
	{
	}

	Logger::Logger(std::shared_ptr<NamedLogger> p) : _delegate{ p }
	{
	}

	void Logger::delegateTo(std::shared_ptr<NamedLogger> p)
	{
		_delegate = p;
	}

	void Logger::delegateTo(NamedLogger* p)
	{
		delegateTo(make_shared(p));
	}
	void Logger::treshold(Level value)
	{
		NamedLogger* const p = _delegate.get();
		if (p)
		{
			p->treshold(value);
		}
	}

	Logger::Level Logger::treshold()
	{
		NamedLogger* const p = _delegate.get();
		if (p)
		{
			return p->treshold();
		}
		return Off;
	}
}