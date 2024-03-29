#pragma once

#include <cmath>

namespace sb_math
{
	struct Vector3D
	{
		float x, y, z;

		constexpr Vector3D() : x{ 0 }, y{ 0 }, z{ 0 } {};
		constexpr Vector3D(float x, float y, float z) : x{ x }, y{ y }, z{ z }{};

		Vector3D normalized() const;
		float length() const;
		constexpr float lengthSquared() const;
		constexpr float dotProduct(const Vector3D& other) const;
		constexpr Vector3D crossProduct(const Vector3D& other) const;
	};

	constexpr float Vector3D::dotProduct(const Vector3D& b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

	constexpr Vector3D Vector3D::crossProduct(const Vector3D& b) const
	{
		return { y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x };
	}

	constexpr float Vector3D::lengthSquared() const
	{
		return dotProduct(*this);
	}

	inline float Vector3D::length() const
	{
		return std::sqrt(lengthSquared());
	}

	inline Vector3D Vector3D::normalized() const
	{
		const float l = length();
		float ool = 1.0;
		if (l != 0) {
			ool = 1.0f / l;
		}
		return { x * ool, y * ool, z * ool };
	}

	inline bool operator == (const Vector3D& a, const Vector3D& b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}

	inline bool operator != (const Vector3D& a, const Vector3D& b)
	{
		return !(a == b);
	}

	template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	inline Vector3D operator * (const Vector3D& v, T scale)
	{
		const float f = static_cast<float>(scale);
		return { v.x * f, v.y * f, v.z * f };
	}

	template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	inline Vector3D& operator *= (Vector3D& v, T scale)
	{
		const float f = static_cast<float>(scale);
		v.x *= f;
		v.y *= f;
		v.z *= f;
		return v;
	}

	template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	inline Vector3D operator * (T scale, const Vector3D& v)
	{
		return v * scale;
	}

	template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	inline Vector3D operator / (const Vector3D& v, T scale)
	{
		return v * (1.0f / scale);
	}

	inline Vector3D operator + (const Vector3D& a, const Vector3D& b)
	{
		return { a.x + b.x, a.y + b.y, a.z + b.z };
	}

	inline Vector3D operator - (const Vector3D& a, const Vector3D& b)
	{
		return { a.x - b.x, a.y - b.y, a.z - b.z };
	}

	inline Vector3D& operator += (Vector3D& a, const Vector3D& b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		return a;
	}

	inline Vector3D& operator -= (Vector3D& a, const Vector3D& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		return a;
	}

	inline Vector3D operator * (const Vector3D& a, const Vector3D& b)
	{
		return { a.x * b.x, a.y * b.y, a.z * b.z };
	}

	inline Vector3D operator / (const Vector3D& a, const Vector3D& b)
	{
		return { a.x / b.x, a.y / b.y, a.z / b.z };
	}

	inline Vector3D& operator *= (Vector3D& a, const Vector3D& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		return a;
	}

	inline Vector3D& operator /= (Vector3D& a, const Vector3D& b)
	{
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		return a;
	}

	inline Vector3D operator - (const Vector3D& a)
	{
		return { -a.x, -a.y, -a.z };
	}
}