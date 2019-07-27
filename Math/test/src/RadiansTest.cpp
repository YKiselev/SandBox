
#include "gtest/gtest.h"
#include "SbMath/Radians.h"

TEST(Radians, ToRadians)
{
	EXPECT_FLOAT_EQ(0, math::toRadians(0));
	EXPECT_FLOAT_EQ(math::PI / 4, math::toRadians(45));
	EXPECT_FLOAT_EQ(math::PI / 2, math::toRadians(90));
	EXPECT_FLOAT_EQ(3 * math::PI / 4, math::toRadians(135));
	EXPECT_FLOAT_EQ(math::PI, math::toRadians(180));
	EXPECT_FLOAT_EQ(5 * math::PI / 4, math::toRadians(225));
	EXPECT_FLOAT_EQ(3 * math::PI / 2, math::toRadians(270));
	EXPECT_FLOAT_EQ(7 * math::PI / 4, math::toRadians(315));
	EXPECT_FLOAT_EQ(2 * math::PI, math::toRadians(360));

	EXPECT_FLOAT_EQ(-math::PI / 4, math::toRadians(-45));
	EXPECT_FLOAT_EQ(-math::PI / 2, math::toRadians(-90));
	EXPECT_FLOAT_EQ(-3 * math::PI / 4, math::toRadians(-135));
	EXPECT_FLOAT_EQ(-math::PI, math::toRadians(-180));
	EXPECT_FLOAT_EQ(-5 * math::PI / 4, math::toRadians(-225));
	EXPECT_FLOAT_EQ(-3 * math::PI / 2, math::toRadians(-270));
	EXPECT_FLOAT_EQ(-7 * math::PI / 4, math::toRadians(-315));
	EXPECT_FLOAT_EQ(-2 * math::PI, math::toRadians(-360));
}

TEST(Radians, ToDegrees)
{
	EXPECT_FLOAT_EQ(0, math::toDegrees(0));
	EXPECT_FLOAT_EQ(45, math::toDegrees(math::PI / 4));
	EXPECT_FLOAT_EQ(90, math::toDegrees(math::PI / 2));
	EXPECT_FLOAT_EQ(135, math::toDegrees(3 * math::PI / 4));
	EXPECT_FLOAT_EQ(180, math::toDegrees(math::PI));
	EXPECT_FLOAT_EQ(225, math::toDegrees(5 * math::PI / 4));
	EXPECT_FLOAT_EQ(270, math::toDegrees(3 * math::PI / 2));
	EXPECT_FLOAT_EQ(315, math::toDegrees(7 * math::PI / 4));
	EXPECT_FLOAT_EQ(360, math::toDegrees(2 * math::PI));

	EXPECT_FLOAT_EQ(-45, math::toDegrees(-math::PI / 4));
	EXPECT_FLOAT_EQ(-90, math::toDegrees(-math::PI / 2));
	EXPECT_FLOAT_EQ(-135, math::toDegrees(-3 * math::PI / 4));
	EXPECT_FLOAT_EQ(-180, math::toDegrees(-math::PI));
	EXPECT_FLOAT_EQ(-225, math::toDegrees(-5 * math::PI / 4));
	EXPECT_FLOAT_EQ(-270, math::toDegrees(-3 * math::PI / 2));
	EXPECT_FLOAT_EQ(-315, math::toDegrees(-7 * math::PI / 4));
	EXPECT_FLOAT_EQ(-360, math::toDegrees(-2 * math::PI));
}