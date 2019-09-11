
#include "gtest/gtest.h"
#include "SbSpi/Logger.h"

using namespace sb_spi;

class MyNamedLogger : public sb_spi::NamedLogger
{
public:
	MyNamedLogger(Logger::Level treshold) : _treshold{ treshold }, _released{ false }
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

	void log(Logger::Level level, const char* message) override
	{
		_buf << message;
	}
	const char* name()const override
	{
		return "MyLogger";
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
	MyNamedLogger md{ Logger::Trace };
	Logger logger{ &md };

	logger.trace("{} {} {}", 1, 2, 3);

	ASSERT_EQ("1 2 3", md.buffer());
}

TEST(Logger, TraceOff)
{
	MyNamedLogger md{ Logger::Debug };
	Logger logger{ &md };

	logger.trace("{} {} {}", 1, 2, 3);

	ASSERT_EQ("", md.buffer());
}

TEST(Logger, Debug)
{
	MyNamedLogger md{ Logger::Debug };
	Logger logger{ &md };

	logger.debug("{} {} {}", 1, 2, 3);

	ASSERT_EQ("1 2 3", md.buffer());
}

TEST(Logger, Info)
{
	MyNamedLogger md{ Logger::Info };
	Logger logger{ &md };

	logger.info("{} {} {}", 1, 2, 3);

	ASSERT_EQ("1 2 3", md.buffer());
}

TEST(Logger, Warning)
{
	MyNamedLogger md{ Logger::Warning };
	Logger logger{ &md };

	logger.warning("{} {} {}", 1, 2, 3);

	ASSERT_EQ("1 2 3", md.buffer());
}

TEST(Logger, Error)
{
	MyNamedLogger md{ Logger::Error };
	Logger logger{ &md };

	logger.error("{} {} {}", 1, 2, 3);

	ASSERT_EQ("1 2 3", md.buffer());
}
