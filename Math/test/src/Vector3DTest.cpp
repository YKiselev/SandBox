
#include "gtest/gtest.h"
#include "SbMath/Vector3D.h"

using sb_math::Vector3D;

TEST(Vector3D, Normalization) {
	EXPECT_EQ(Vector3D(1, 0, 0), Vector3D(10, 0, 0).normalized());
	EXPECT_EQ(Vector3D(0, 1, 0), Vector3D(0, 10, 0).normalized());
	EXPECT_EQ(Vector3D(0, 0, 1), Vector3D(0, 0, 10).normalized());

	const Vector3D n = Vector3D(11, 12, 13).normalized();

	EXPECT_FLOAT_EQ(0.52801687f, n.x);
	EXPECT_FLOAT_EQ(0.57601845f, n.y);
	EXPECT_FLOAT_EQ(0.62401998f, n.z);
}

TEST(Vector3D, Length)
{
	EXPECT_FLOAT_EQ(std::sqrt(25.0f + 49 + 9), Vector3D(5, 7, 3).length());
}

TEST(Vector3D, LengthSquared)
{
	EXPECT_FLOAT_EQ(25 + 49 + 9, Vector3D(5, 7, 3).lengthSquared());
}

TEST(Vector3D, DotProduct)
{
	EXPECT_FLOAT_EQ(2 * 3 + 4 * 5 + 6 * 7, Vector3D(2, 4, 6).dotProduct(Vector3D(3, 5, 7)));
}

TEST(Vector3D, Equality)
{
	EXPECT_TRUE(Vector3D(1, 2, 3) == Vector3D(1, 2, 3));
	EXPECT_FALSE(Vector3D(1, 2, 3) != Vector3D(1, 2, 3));

	EXPECT_FALSE(Vector3D(1, 2, 3) == Vector3D(3, 2, 1));
	EXPECT_TRUE(Vector3D(1, 2, 3) != Vector3D(3, 2, 1));
}

TEST(Vector3D, CrossProduct)
{
	const Vector3D result = Vector3D(5, 7, 9).crossProduct(Vector3D(-10, 3, -5));
	EXPECT_FLOAT_EQ(7 * -5 - 9 * 3, result.x);
	EXPECT_FLOAT_EQ(9 * -10 - 5 * -5, result.y);
	EXPECT_FLOAT_EQ(5 * 3 - 7 * -10, result.z);
}

TEST(Vector3D, MultiplyByScalar)
{
	const Vector3D result = Vector3D(1, 2, 3) * 100;
	EXPECT_FLOAT_EQ(100, result.x);
	EXPECT_FLOAT_EQ(200, result.y);
	EXPECT_FLOAT_EQ(300, result.z);
}

TEST(Vector3D, MultiplyByScalarAndAssign)
{
	Vector3D a = Vector3D(1, 2, 3);
	const Vector3D& result = a *= 100;
	EXPECT_FLOAT_EQ(100, result.x);
	EXPECT_FLOAT_EQ(200, result.y);
	EXPECT_FLOAT_EQ(300, result.z);
}

TEST(Vector3D, ScalarIsMultipliedBy)
{
	const Vector3D result = 100 * Vector3D(1, 2, 3);
	EXPECT_FLOAT_EQ(100, result.x);
	EXPECT_FLOAT_EQ(200, result.y);
	EXPECT_FLOAT_EQ(300, result.z);
}

TEST(Vector3D, DivideByScalar)
{
	const Vector3D result = Vector3D(10, 20, 30) / 10.0f;
	EXPECT_FLOAT_EQ(1, result.x);
	EXPECT_FLOAT_EQ(2, result.y);
	EXPECT_FLOAT_EQ(3, result.z);
}

TEST(Vector3D, AddVector)
{
	const Vector3D result = Vector3D(1, 2, 3) + Vector3D(4, 5, 6);
	EXPECT_FLOAT_EQ(5, result.x);
	EXPECT_FLOAT_EQ(7, result.y);
	EXPECT_FLOAT_EQ(9, result.z);
}

TEST(Vector3D, SubtractVector)
{
	const Vector3D result = Vector3D(1, 2, 3) - Vector3D(4, 5, 6);
	EXPECT_FLOAT_EQ(-3, result.x);
	EXPECT_FLOAT_EQ(-3, result.y);
	EXPECT_FLOAT_EQ(-3, result.z);
}

TEST(Vector3D, IncrementByVector)
{
	Vector3D a = Vector3D(1, 2, 3);
	const Vector3D& result = a += Vector3D(4, 5, 6);
	EXPECT_FLOAT_EQ(5, result.x);
	EXPECT_FLOAT_EQ(7, result.y);
	EXPECT_FLOAT_EQ(9, result.z);
}

TEST(Vector3D, DecrementByVector)
{
	Vector3D a = Vector3D(1, 2, 3);
	const Vector3D& result = a -= Vector3D(4, 5, 6);
	EXPECT_FLOAT_EQ(-3, result.x);
	EXPECT_FLOAT_EQ(-3, result.y);
	EXPECT_FLOAT_EQ(-3, result.z);
}

TEST(Vector3D, MultiplyByVector)
{
	const Vector3D result = Vector3D(1, 2, 3) * Vector3D(4, 5, 6);
	EXPECT_FLOAT_EQ(4, result.x);
	EXPECT_FLOAT_EQ(10, result.y);
	EXPECT_FLOAT_EQ(18, result.z);
}

TEST(Vector3D, DivideByVector)
{
	const Vector3D result = Vector3D(10, 20, 30) / Vector3D(5, 4, 5);
	EXPECT_FLOAT_EQ(2, result.x);
	EXPECT_FLOAT_EQ(5, result.y);
	EXPECT_FLOAT_EQ(6, result.z);
}

TEST(Vector3D, MultiplyByVectorAndAssign)
{
	Vector3D a = Vector3D(1, 2, 3);
	const Vector3D& result = a *= Vector3D(4, 5, 6);
	EXPECT_FLOAT_EQ(4, result.x);
	EXPECT_FLOAT_EQ(10, result.y);
	EXPECT_FLOAT_EQ(18, result.z);
}

TEST(Vector3D, DivideByVectorAndAssign)
{
	Vector3D a = Vector3D(10, 20, 30);
	const Vector3D& result = a /= Vector3D(5, 4, 5);
	EXPECT_FLOAT_EQ(2, result.x);
	EXPECT_FLOAT_EQ(5, result.y);
	EXPECT_FLOAT_EQ(6, result.z);
}

TEST(Vector3D, Negate)
{
	const Vector3D result = -Vector3D(1, 2, 3);
	EXPECT_FLOAT_EQ(-1, result.x);
	EXPECT_FLOAT_EQ(-2, result.y);
	EXPECT_FLOAT_EQ(-3, result.z);
}