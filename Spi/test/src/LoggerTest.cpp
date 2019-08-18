
#include "gtest/gtest.h"
#include "SbSpi/Logger.h"

using namespace sb_spi;

class MyDelegate : public sb_spi::LoggerDelegate
{
public:
	MyDelegate(Logger::Level treshold) : _treshold{ treshold }, _released{ false }
	{
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
		_buf << message;
	}

	void release() override
	{
		_released = true;
	}

	std::string buffer()
	{
		return _buf.str();
	}

	void clear()
	{
		_buf.str("");
		_buf.clear();
	}

private:
	Logger::Level _treshold;
	std::stringstream _buf;
	bool _released;
};

TEST(Logger, TraceOn)
{
	MyDelegate md{ Logger::Trace };
	Logger logger{ &md };

	logger.trace("{} {} {}", 1, 2, 3);

	ASSERT_EQ("1 2 3", md.buffer());
}

TEST(Logger, TraceOff)
{
	MyDelegate md{ Logger::Debug };
	Logger logger{ &md };

	logger.trace("{} {} {}", 1, 2, 3);

	ASSERT_EQ("", md.buffer());
}
