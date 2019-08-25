
#include "SbSpi/SharedObject.h"
#include "gtest/gtest.h"

using namespace sb_spi;

class MyObject : public SharedObject
{
public:
	MyObject(bool& flag) : _destructed{ flag }
	{
	}

	virtual void release() override
	{
		delete this;
	}

protected:
	virtual ~MyObject()
	{
		_destructed = true;
	}

private:
	bool& _destructed;
};

TEST(SharedObject, SharedPtr)
{
	bool flag = false;
	MyObject* p = new MyObject{ flag };
	std::shared_ptr<MyObject> sp{ sb_spi::make_shared(p) };

	ASSERT_FALSE(flag);

	sp.reset();

	ASSERT_TRUE(flag);
}