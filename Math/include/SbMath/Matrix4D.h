#pragma once

#include "Vector3D.h"

namespace math
{
	/*
		Column-oriented matrix
	*/
	struct Matrix4D
	{
		float c1r1, c1r2, c1r3, c1r4,
			c2r1, c2r2, c2r3, c2r4,
			c3r1, c3r2, c3r3, c3r4,
			c4r1, c4r2, c4r3, c4r4;

		/*
			Primary ctor, creates identity matrix
		*/
		Matrix4D() : c1r1{ 1 }, c1r2{ 0 }, c1r3{ 0 }, c1r4{ 0 },
			c2r1{ 0 }, c2r2{ 1 }, c2r3{ 0 }, c2r4{ 0 },
			c3r1{ 0 }, c3r2{ 0 }, c3r3{ 1 }, c3r4{ 0 },
			c4r1{ 0 }, c4r2{ 0 }, c4r3{ 0 }, c4r4{ 1 }	{}

		Matrix4D(
			float c1r1, float c1r2, float c1r3, float c1r4,
			float c2r1, float c2r2, float c2r3, float c2r4,
			float c3r1, float c3r2, float c3r3, float c3r4,
			float c4r1, float c4r2, float c4r3, float c4r4
		);

		Matrix4D(const float src[16]);

		/*
			 Calculates orthographic projection matrix.

			 left   the left screen coordinate (usually 0)
			 right  the right screen coordinate (usually width)
			 top    the top screen coordinate (usually height)
			 bottom the bottom screen coordinate (usually 0)
			 near   the near z value (for example -1)
			 far    the far z coordinate (for example 1)
			 m      the buffer to store resulting matrix in.
		 */
		static Matrix4D orthographic(float left, float right, float top, float bottom, float near, float far);

		/*
			Calculates perspective projection matrix.

			left   the left screen coordinate (usually 0)
			right  the right screen coordinate (usually width)
			top    the top screen coordinate (usually height)
			bottom the bottom screen coordinate (usually 0)
			near   the near z value (for example -1)
			far    the far z coordinate (for example 1)
			m      the buffer to store resulting matrix in.
		 */
		static Matrix4D perspective(float left, float right, float top, float bottom, float near, float far);

		/*
			Calculates perspective projection matrix.

			fow   the horizontal field of view (in radians)
			ratio the aspect ratio between width and height of screen
			near  the near z coordinate (should be > 0)
			far   the far z coordinate
			m     the buffer to store resulting matrix in.
		 */
		static Matrix4D perspective(float fow, float ratio, float near, float far);

		/*
			Creates viewing matrix derived from the "eye" point, a reference point "target" indicating the center of the scene and vector "up"
			Helpful tip: it's better to think of this as a coordinate system rotation.
	 
			target the target point in the scene
			eye    the eye point
			up     the upward vector, must not be parallel to the direction vector (dir = target - eye)
			m      the buffer to store resulting matrix in.
		 */
		static Matrix4D lookAt(const Vector3D& target, const Vector3D& eye, const Vector3D& up);

		static Matrix4D rotation(float ax, float ay, float az);

		/*
			Translation operators
		*/
		Matrix4D operator + (const Vector3D& v) const;
		Matrix4D operator - (const Vector3D& v) const;

		Matrix4D operator + (const Matrix4D& b) const;
		Matrix4D operator - (const Matrix4D& b) const;
		Matrix4D operator * (float scale) const;
		Matrix4D operator * (const Matrix4D& b) const;
		Vector3D operator * (const Vector3D& b) const;

		/*
			Transposition operator
		*/
		Matrix4D operator ~ () const;
		Matrix4D rotate(float ax, float ay, float az) const;
		
		/*
			Calculates inverse matrix. Will set passed variable to false if inversion is not possible (e.g. matrix's determinant is zero).
		*/
		Matrix4D inverse(bool& success) const;

		float determinant() const;

		bool operator == (const Matrix4D& other) const;
		bool operator != (const Matrix4D& other) const;
	};

	inline bool Matrix4D::operator != (const Matrix4D& other) const
	{
		return !(*this == other);
	}
}