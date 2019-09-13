
#include "SbSpi/FileSystem.h"
#include "gtest/gtest.h"

using namespace sb_spi;

class MyReadable : public Readable
{
public:
	void release() override
	{
	}
	size_t read(char* buf, size_t capacity) override
	{
		return 0;
	}
};

class MyWritable : public Writable
{
public:
	size_t write(const char* buf, size_t length) override
	{
		return 0;
	}

	void release() override
	{
	}
};

class MyFileSystem : public FileSystem
{
protected:

	Readable* _openReadable(const char* name) override
	{
		return nullptr;
	}
	Writable* _openWritable(const char* name) override
	{
		return nullptr;
	}
};


TEST(FileSystem, OpenReadable)
{

}