
#include <string>
#include <cstring>
#include "gtest/gtest.h"
#include "SbSpi/PersistedConfiguration.h"

using namespace sb_spi;

TEST(IntValue, Get)
{
	IntValue iv{ "x", 123 };

	ASSERT_EQ(123, iv.getInt());
	ASSERT_EQ(123ull, iv.getUllong());
	ASSERT_NEAR(123.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(123.0, iv.getDouble(), 0.1);
	ASSERT_TRUE(iv.getBool());
}

TEST(IntValue, SetInteger)
{
	IntValue iv{ "x",3 };

	iv.setInt(1);

	ASSERT_EQ(1, iv.getInt());
	ASSERT_EQ(1, iv.getUllong());
	ASSERT_NEAR(1.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(1.0, iv.getDouble(), 0.1);
	ASSERT_TRUE(iv.getBool());
}

TEST(IntValue, SetUllong)
{
	IntValue iv{ "x",3 };

	iv.setUllong(2);

	ASSERT_EQ(2, iv.getInt());
	ASSERT_EQ(2, iv.getUllong());
	ASSERT_NEAR(2.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(2.0, iv.getDouble(), 0.1);
	ASSERT_TRUE(iv.getBool());
}

TEST(IntValue, SetFloat)
{
	IntValue iv{ "x", 2 };

	iv.setFloat(3.f);

	ASSERT_EQ(3, iv.getInt());
	ASSERT_EQ(3, iv.getUllong());
	ASSERT_NEAR(3.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(3.0, iv.getDouble(), 0.1);
	ASSERT_TRUE(iv.getBool());
}

TEST(IntValue, SetDouble)
{
	IntValue iv{ "x", 2 };

	iv.setDouble(3.0);

	ASSERT_EQ(3, iv.getInt());
	ASSERT_EQ(3, iv.getUllong());
	ASSERT_NEAR(3.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(3.0, iv.getDouble(), 0.1);
	ASSERT_TRUE(iv.getBool());
}

TEST(IntValue, SetBool)
{
	IntValue iv{ "x",2 };

	iv.setBool(false);

	ASSERT_EQ(0, iv.getInt());
	ASSERT_EQ(0, iv.getUllong());
	ASSERT_NEAR(0.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(0.0, iv.getDouble(), 0.1);
	ASSERT_FALSE(iv.getBool());
}

TEST(IntValue, FromString)
{
	IntValue iv{ "x",123 };

	iv.setString("1234567890");

	ASSERT_EQ(1234567890, iv.getInt());
	ASSERT_EQ(1234567890ull, iv.getUllong());
	ASSERT_NEAR(1234567890.f, iv.getFloat(), 0.1);
	ASSERT_NEAR(1234567890.0, iv.getDouble(), 0.1);
	ASSERT_TRUE(iv.getBool());
}

TEST(IntValue, ToString)
{
	IntValue iv{ "x",123 };

	char buf[100];
	const int r = iv.getString(buf, 100);
	ASSERT_EQ("123", std::string{ buf });
	ASSERT_EQ(3, r);
}

TEST(UllongValue, Get)
{
	UllongValue v{ "x",123 };

	ASSERT_EQ(123, v.getInt());
	ASSERT_EQ(123ull, v.getUllong());
	ASSERT_NEAR(123.f, v.getFloat(), 0.1);
	ASSERT_NEAR(123.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(UllongValue, SetInteger)
{
	UllongValue v{ "x",3 };

	v.setInt(1);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(UllongValue, SetUllong)
{
	UllongValue v{ "x",3 };

	v.setUllong(2);

	ASSERT_EQ(2, v.getInt());
	ASSERT_EQ(2, v.getUllong());
	ASSERT_NEAR(2.f, v.getFloat(), 0.1);
	ASSERT_NEAR(2.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(UllongValue, SetFloat)
{
	UllongValue v{ "x",2 };

	v.setFloat(3.f);

	ASSERT_EQ(3, v.getInt());
	ASSERT_EQ(3, v.getUllong());
	ASSERT_NEAR(3.f, v.getFloat(), 0.1);
	ASSERT_NEAR(3.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(UllongValue, SetDouble)
{
	UllongValue v{ "x",2 };

	v.setDouble(3.0);

	ASSERT_EQ(3, v.getInt());
	ASSERT_EQ(3, v.getUllong());
	ASSERT_NEAR(3.f, v.getFloat(), 0.1);
	ASSERT_NEAR(3.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(UllongValue, SetBool)
{
	UllongValue v{ "x",2 };

	v.setBool(false);

	ASSERT_EQ(0, v.getInt());
	ASSERT_EQ(0, v.getUllong());
	ASSERT_NEAR(0.f, v.getFloat(), 0.1);
	ASSERT_NEAR(0.0, v.getDouble(), 0.1);
	ASSERT_FALSE(v.getBool());
}

TEST(UllongValue, FromString)
{
	UllongValue v{ "x",123 };

	v.setString("1234567890");

	ASSERT_EQ(1234567890, v.getInt());
	ASSERT_EQ(1234567890ull, v.getUllong());
	ASSERT_NEAR(1234567890.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1234567890.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(UllongValue, ToString)
{
	UllongValue v{ "x",123 };

	char buf[100];
	const int r = v.getString(buf, 100);
	ASSERT_EQ("0x7b", std::string{ buf });
	ASSERT_EQ(4, r);
}

TEST(DoubleValue, Get)
{
	DoubleValue v{ "x",123 };

	ASSERT_EQ(123, v.getInt());
	ASSERT_EQ(123ull, v.getUllong());
	ASSERT_NEAR(123.f, v.getFloat(), 0.1);
	ASSERT_NEAR(123.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(DoubleValue, SetInteger)
{
	DoubleValue v{ "x",3 };

	v.setInt(1);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(DoubleValue, SetUllong)
{
	DoubleValue v{ "x",3.0 };

	v.setUllong(2);

	ASSERT_EQ(2, v.getInt());
	ASSERT_EQ(2, v.getUllong());
	ASSERT_NEAR(2.f, v.getFloat(), 0.1);
	ASSERT_NEAR(2.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(DoubleValue, SetFloat)
{
	DoubleValue v{ "x",2.0 };

	v.setFloat(3.f);

	ASSERT_EQ(3, v.getInt());
	ASSERT_EQ(3, v.getUllong());
	ASSERT_NEAR(3.f, v.getFloat(), 0.1);
	ASSERT_NEAR(3.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(DoubleValue, SetDouble)
{
	DoubleValue v{ "x",2.0 };

	v.setDouble(3.0);

	ASSERT_EQ(3, v.getInt());
	ASSERT_EQ(3, v.getUllong());
	ASSERT_NEAR(3.f, v.getFloat(), 0.1);
	ASSERT_NEAR(3.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(DoubleValue, SetBool)
{
	DoubleValue v{ "x",2.0 };

	v.setBool(false);

	ASSERT_EQ(0, v.getInt());
	ASSERT_EQ(0, v.getUllong());
	ASSERT_NEAR(0.f, v.getFloat(), 0.1);
	ASSERT_NEAR(0.0, v.getDouble(), 0.1);
	ASSERT_FALSE(v.getBool());
}

TEST(DoubleValue, FromString)
{
	DoubleValue v{ "x" };

	v.setString("123.4567");

	ASSERT_EQ(123, v.getInt());
	ASSERT_EQ(123ull, v.getUllong());
	ASSERT_NEAR(123.4567f, v.getFloat(), 0.1);
	ASSERT_NEAR(123.4567, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(DoubleValue, ToString)
{
	DoubleValue v{ "x",3.14 };

	char buf[100];
	const int r = v.getString(buf, 100);
	ASSERT_EQ("3.140000", std::string{ buf });
	ASSERT_EQ(8, r);
}

TEST(FloatValue, Get)
{
	FloatValue v{ "x",123.f };

	ASSERT_EQ(123, v.getInt());
	ASSERT_EQ(123ull, v.getUllong());
	ASSERT_NEAR(123.f, v.getFloat(), 0.1);
	ASSERT_NEAR(123.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(FloatValue, SetInteger)
{
	FloatValue v{ "x",3.f };

	v.setInt(1);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(FloatValue, SetUllong)
{
	FloatValue v{ "x",3.f };

	v.setUllong(2);

	ASSERT_EQ(2, v.getInt());
	ASSERT_EQ(2, v.getUllong());
	ASSERT_NEAR(2.f, v.getFloat(), 0.1);
	ASSERT_NEAR(2.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(FloatValue, SetFloat)
{
	FloatValue v{ "x",2.f };

	v.setFloat(3.f);

	ASSERT_EQ(3, v.getInt());
	ASSERT_EQ(3, v.getUllong());
	ASSERT_NEAR(3.f, v.getFloat(), 0.1);
	ASSERT_NEAR(3.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(FloatValue, SetDouble)
{
	FloatValue v{ "x",2.f };

	v.setDouble(3.0);

	ASSERT_EQ(3, v.getInt());
	ASSERT_EQ(3, v.getUllong());
	ASSERT_NEAR(3.f, v.getFloat(), 0.1);
	ASSERT_NEAR(3.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(FloatValue, SetBool)
{
	FloatValue v{ "x",2.f };

	v.setBool(false);

	ASSERT_EQ(0, v.getInt());
	ASSERT_EQ(0, v.getUllong());
	ASSERT_NEAR(0.f, v.getFloat(), 0.1);
	ASSERT_NEAR(0.0, v.getDouble(), 0.1);
	ASSERT_FALSE(v.getBool());
}

TEST(FloatValue, FromString)
{
	FloatValue v{ "x" };

	v.setString("123.4567");

	ASSERT_EQ(123, v.getInt());
	ASSERT_EQ(123ull, v.getUllong());
	ASSERT_NEAR(123.4567f, v.getFloat(), 0.0001);
	ASSERT_NEAR(123.4567, v.getDouble(), 0.0001);
	ASSERT_TRUE(v.getBool());
}

TEST(FloatValue, ToString)
{
	FloatValue v{ "x",3.14f };

	char buf[100];
	const int r = v.getString(buf, 100);
	ASSERT_EQ("3.140000", std::string{ buf });
	ASSERT_EQ(8, r);
}

TEST(BoolValue, Get)
{
	BoolValue v{ "x",true };

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1ull, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(BoolValue, SetInteger)
{
	BoolValue v{ "x" };

	v.setInt(1);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(BoolValue, SetUllong)
{
	BoolValue v{ "x" };

	v.setUllong(2);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(BoolValue, SetFloat)
{
	BoolValue v{ "x" };

	v.setFloat(3.f);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(BoolValue, SetDouble)
{
	BoolValue v{ "x" };

	v.setDouble(3.0);

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(BoolValue, SetBool)
{
	BoolValue v{ "x" };

	v.setBool(false);

	ASSERT_EQ(0, v.getInt());
	ASSERT_EQ(0, v.getUllong());
	ASSERT_NEAR(0.f, v.getFloat(), 0.1);
	ASSERT_NEAR(0.0, v.getDouble(), 0.1);
	ASSERT_FALSE(v.getBool());
}

TEST(BoolValue, FromString)
{
	BoolValue v{ "x" };

	v.setString("yes");

	ASSERT_EQ(1, v.getInt());
	ASSERT_EQ(1ull, v.getUllong());
	ASSERT_NEAR(1.f, v.getFloat(), 0.1);
	ASSERT_NEAR(1.0, v.getDouble(), 0.1);
	ASSERT_TRUE(v.getBool());
}

TEST(BoolValue, ToString)
{
	BoolValue v{ "x",true };

	char buf[10];
	const int r = v.getString(buf, 10);
	ASSERT_EQ("yes", std::string{ buf });
	ASSERT_EQ(3, r);
}

TEST(StringValue, FromString)
{
	StringValue v{ "x",20 };
	char buf[10];

	int r = v.getString(buf, 10);
	ASSERT_EQ("", std::string{ buf });
	ASSERT_EQ(0, r);

	v.setString("Test");

	r = v.getString(buf, 10);
	ASSERT_EQ("Test", std::string{ buf });
	ASSERT_EQ(4, r);
}
/*
#include <unordered_map>

void update(std::unordered_map<std::string, int>& map, const char* key)
{
	const int v = map[key];
	map[key] = v + 1;
}

TEST(StringMap, Keys)
{
	const char* const keys[] = { "a","b","c","d","e" };
	const size_t count = sizeof(keys) / sizeof(const char*);
	std::unordered_map<std::string, int> ints;
	for (int i = 0; i < 100000; i++)
	{
		update(ints, keys[i % count]);
	}

	for (const auto& p : ints) {
		std::cout << p.first << " = " << p.second << "\n";
	}
	int g = 0;
}*/