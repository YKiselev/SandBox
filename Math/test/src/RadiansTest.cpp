
#include "gtest/gtest.h"
#include "SbMath/Radians.h"

using sb_math::PI;

TEST(Radians, ToRadians)
{
	EXPECT_FLOAT_EQ(0, sb_math::toRadians(0));
	EXPECT_FLOAT_EQ(PI / 4, sb_math::toRadians(45));
	EXPECT_FLOAT_EQ(PI / 2, sb_math::toRadians(90));
	EXPECT_FLOAT_EQ(3 * PI / 4, sb_math::toRadians(135));
	EXPECT_FLOAT_EQ(PI, sb_math::toRadians(180));
	EXPECT_FLOAT_EQ(5 * PI / 4, sb_math::toRadians(225));
	EXPECT_FLOAT_EQ(3 * PI / 2, sb_math::toRadians(270));
	EXPECT_FLOAT_EQ(7 * PI / 4, sb_math::toRadians(315));
	EXPECT_FLOAT_EQ(2 * PI, sb_math::toRadians(360));

	EXPECT_FLOAT_EQ(-PI / 4, sb_math::toRadians(-45));
	EXPECT_FLOAT_EQ(-PI / 2, sb_math::toRadians(-90));
	EXPECT_FLOAT_EQ(-3 * PI / 4, sb_math::toRadians(-135));
	EXPECT_FLOAT_EQ(-PI, sb_math::toRadians(-180));
	EXPECT_FLOAT_EQ(-5 * PI / 4, sb_math::toRadians(-225));
	EXPECT_FLOAT_EQ(-3 * PI / 2, sb_math::toRadians(-270));
	EXPECT_FLOAT_EQ(-7 * PI / 4, sb_math::toRadians(-315));
	EXPECT_FLOAT_EQ(-2 * PI, sb_math::toRadians(-360));
}

TEST(Radians, ToDegrees)
{
	EXPECT_FLOAT_EQ(0, sb_math::toDegrees(0));
	EXPECT_FLOAT_EQ(45, sb_math::toDegrees(PI / 4));
	EXPECT_FLOAT_EQ(90, sb_math::toDegrees(PI / 2));
	EXPECT_FLOAT_EQ(135, sb_math::toDegrees(3 * PI / 4));
	EXPECT_FLOAT_EQ(180, sb_math::toDegrees(PI));
	EXPECT_FLOAT_EQ(225, sb_math::toDegrees(5 * PI / 4));
	EXPECT_FLOAT_EQ(270, sb_math::toDegrees(3 * PI / 2));
	EXPECT_FLOAT_EQ(315, sb_math::toDegrees(7 * PI / 4));
	EXPECT_FLOAT_EQ(360, sb_math::toDegrees(2 * PI));

	EXPECT_FLOAT_EQ(-45, sb_math::toDegrees(-PI / 4));
	EXPECT_FLOAT_EQ(-90, sb_math::toDegrees(-PI / 2));
	EXPECT_FLOAT_EQ(-135, sb_math::toDegrees(-3 * PI / 4));
	EXPECT_FLOAT_EQ(-180, sb_math::toDegrees(-PI));
	EXPECT_FLOAT_EQ(-225, sb_math::toDegrees(-5 * PI / 4));
	EXPECT_FLOAT_EQ(-270, sb_math::toDegrees(-3 * PI / 2));
	EXPECT_FLOAT_EQ(-315, sb_math::toDegrees(-7 * PI / 4));
	EXPECT_FLOAT_EQ(-360, sb_math::toDegrees(-2 * PI));
}