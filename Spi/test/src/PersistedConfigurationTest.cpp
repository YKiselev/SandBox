
#include <string>
#include "gtest/gtest.h"
#include "SbSpi/PersistedConfiguration.h"


TEST(IntValue, AtomicValue)
{
	spi::IntValue v{ 5 };

	ASSERT_TRUE((std::is_same<spi::AtomicValue<int>, decltype(v)::wrapper_type>::value));
}

TEST(IntValue, GetValue)
{
	spi::IntValue v{ 5 };

	ASSERT_EQ(5, v.get());
}

TEST(IntValue, SetValue)
{
	spi::IntValue v{};
	v.set(7);
	ASSERT_EQ(7, v.get());
}

TEST(IntValue, ToString)
{
	spi::IntValue v{ -321 };
	ASSERT_EQ("-321", v.toString());
}

TEST(IntValue, FromString)
{
	spi::IntValue v{};
	v.fromString("123");
	ASSERT_EQ(123, v.get());
}

TEST(FloatValue, AtomicValue)
{
	spi::FloatValue v{ 3.14f };

	ASSERT_TRUE((std::is_same<spi::AtomicValue<float>, decltype(v)::wrapper_type>::value));
}

TEST(FloatValue, GetValue)
{
	spi::FloatValue v{ 3.14f };

	ASSERT_EQ(3.14f, v.get());
}

TEST(FloatValue, SetValue)
{
	spi::FloatValue v{};
	v.set(7.5f);
	ASSERT_EQ(7.5f, v.get());
}

TEST(FloatValue, FromString)
{
	spi::FloatValue v{ };
	v.fromString("3.14");
	ASSERT_EQ(3.14f, v.get());
}

TEST(FloatValue, ToString)
{
	spi::FloatValue v{ 34.55f };
	ASSERT_EQ("34.55", v.toString());
}

TEST(BoolValue, AtomicValue)
{
	spi::BoolValue v{ true };

	ASSERT_TRUE((std::is_same<spi::AtomicValue<bool>, decltype(v)::wrapper_type>::value));
}

TEST(BoolValue, GetValue)
{
	spi::BoolValue v{ true };

	ASSERT_TRUE(v.get());
}

TEST(BoolValue, SetValue)
{
	spi::BoolValue v{};
	v.set(true);
	ASSERT_TRUE(v.get());
	v.set(false);
	ASSERT_FALSE(v.get());
}

TEST(BoolValue, FromString)
{
	spi::BoolValue v{ };

	v.fromString("true");
	ASSERT_TRUE(v.get());

	v.fromString("false");
	ASSERT_FALSE(v.get());
}

TEST(BoolValue, ToString)
{
	spi::BoolValue v{ true };

	ASSERT_EQ("true", v.toString());

	v.set(false);
	ASSERT_EQ("false", v.toString());
}

TEST(StringValue, LockedValue)
{
	spi::StringValue v{ "xyz" };

	ASSERT_TRUE((std::is_same<spi::LockedValue<std::string>, decltype(v)::wrapper_type>::value));
}

TEST(StringValue, GetValue)
{
	spi::StringValue v{ "xyz" };

	ASSERT_EQ("xyz", v.get());
}

TEST(StringValue, SetValue)
{
	spi::StringValue v{ };

	v.set("abc");
	ASSERT_EQ("abc", v.get());
}

TEST(StringValue, ToString)
{
	spi::StringValue v{ "xyz" };

	ASSERT_EQ("xyz", v.toString());
}

TEST(StringValue, FromString)
{
	spi::StringValue v{};
	v.fromString("abc");
	ASSERT_EQ("abc", v.get());
}
