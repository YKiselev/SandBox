
#include <string>
#include "gtest/gtest.h"
#include "SbSpi/PersistedConfiguration.h"


TEST(IntValue, AtomicValue)
{
	sb_spi::IntValue v{ 5 };

	ASSERT_TRUE((std::is_same<sb_spi::AtomicValue<int>, decltype(v)::wrapper_type>::value));
}

TEST(IntValue, GetValue)
{
	sb_spi::IntValue v{ 5 };

	ASSERT_EQ(5, v.get());
}

TEST(IntValue, SetValue)
{
	sb_spi::IntValue v{};
	v.set(7);
	ASSERT_EQ(7, v.get());
}

TEST(IntValue, ToString)
{
	sb_spi::IntValue v{ -321 };
	ASSERT_EQ("-321", v.toString());
}

TEST(IntValue, FromString)
{
	sb_spi::IntValue v{};
	v.fromString("123");
	ASSERT_EQ(123, v.get());
}

TEST(FloatValue, AtomicValue)
{
	sb_spi::FloatValue v{ 3.14f };

	ASSERT_TRUE((std::is_same<sb_spi::AtomicValue<float>, decltype(v)::wrapper_type>::value));
}

TEST(FloatValue, GetValue)
{
	sb_spi::FloatValue v{ 3.14f };

	ASSERT_EQ(3.14f, v.get());
}

TEST(FloatValue, SetValue)
{
	sb_spi::FloatValue v{};
	v.set(7.5f);
	ASSERT_EQ(7.5f, v.get());
}

TEST(FloatValue, FromString)
{
	sb_spi::FloatValue v{ };
	v.fromString("3.14");
	ASSERT_EQ(3.14f, v.get());
}

TEST(FloatValue, ToString)
{
	sb_spi::FloatValue v{ 34.55f };
	ASSERT_EQ("34.55", v.toString());
}

TEST(BoolValue, AtomicValue)
{
	sb_spi::BoolValue v{ true };

	ASSERT_TRUE((std::is_same<sb_spi::AtomicValue<bool>, decltype(v)::wrapper_type>::value));
}

TEST(BoolValue, GetValue)
{
	sb_spi::BoolValue v{ true };

	ASSERT_TRUE(v.get());
}

TEST(BoolValue, SetValue)
{
	sb_spi::BoolValue v{};
	v.set(true);
	ASSERT_TRUE(v.get());
	v.set(false);
	ASSERT_FALSE(v.get());
}

TEST(BoolValue, FromString)
{
	sb_spi::BoolValue v{ };

	v.fromString("true");
	ASSERT_TRUE(v.get());

	v.fromString("false");
	ASSERT_FALSE(v.get());
}

TEST(BoolValue, ToString)
{
	sb_spi::BoolValue v{ true };

	ASSERT_EQ("true", v.toString());

	v.set(false);
	ASSERT_EQ("false", v.toString());
}

TEST(StringValue, LockedValue)
{
	sb_spi::StringValue v{ "xyz" };

	ASSERT_TRUE((std::is_same<sb_spi::LockedValue<std::string>, decltype(v)::wrapper_type>::value));
}

TEST(StringValue, GetValue)
{
	sb_spi::StringValue v{ "xyz" };

	ASSERT_EQ("xyz", v.get());
}

TEST(StringValue, SetValue)
{
	sb_spi::StringValue v{ };

	v.set("abc");
	ASSERT_EQ("abc", v.get());
}

TEST(StringValue, ToString)
{
	sb_spi::StringValue v{ "xyz" };

	ASSERT_EQ("xyz", v.toString());
}

TEST(StringValue, FromString)
{
	sb_spi::StringValue v{};
	v.fromString("abc");
	ASSERT_EQ("abc", v.get());
}
