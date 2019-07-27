#include <cmath>
#include "../include/SbMath/Matrix4D.h"


namespace math
{

	Matrix4D::Matrix4D(const float src[16]) : c1r1{ src[0] }, c1r2{ src[1] }, c1r3{ src[2] }, c1r4{ src[3] },
		c2r1{ src[4] }, c2r2{ src[5] }, c2r3{ src[6] }, c2r4{ src[7] },
		c3r1{ src[8] }, c3r2{ src[9] }, c3r3{ src[10] }, c3r4{ src[11] },
		c4r1{ src[12] }, c4r2{ src[13] }, c4r3{ src[14] }, c4r4{ src[15] }
	{
	}

	Matrix4D::Matrix4D(
		float c1r1, float c1r2, float c1r3, float c1r4,
		float c2r1, float c2r2, float c2r3, float c2r4,
		float c3r1, float c3r2, float c3r3, float c3r4,
		float c4r1, float c4r2, float c4r3, float c4r4
	) : c1r1(c1r1), c1r2(c1r2), c1r3(c1r3), c1r4(c1r4),
		c2r1(c2r1), c2r2(c2r2), c2r3(c2r3), c2r4(c2r4),
		c3r1(c3r1), c3r2(c3r2), c3r3(c3r3), c3r4(c3r4),
		c4r1(c4r1), c4r2(c4r2), c4r3(c4r3), c4r4(c4r4)
	{
	}

	Matrix4D Matrix4D::orthographic(float left, float right, float top, float bottom, float near, float far)
	{
		return Matrix4D(
			2 / (right - left), 0, 0, 0,
			0, 2 / (top - bottom), 0, 0,
			0, 0, -2 / (far - near), 0,
			-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1
		);
	}

	Matrix4D Matrix4D::perspective(float left, float right, float top, float bottom, float near, float far)
	{
		return Matrix4D(
			2 * near / (right - left), 0, 0, 0,
			0, 2 * near / (top - bottom), 0, 0,
			(right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1,
			0, 0, -2 * far * near / (far - near), 0
		);
	}

	Matrix4D Matrix4D::perspective(float fow, float ratio, float near, float far)
	{
		const float w = near * std::tan(0.5f * fow);
		const float h = w / ratio;
		return perspective(-w, w, h, -h, near, far);
	}

	Matrix4D Matrix4D::lookAt(const Vector3D & target, const Vector3D & eye, const Vector3D & up)
	{
		const Vector3D zaxis = (eye - target).normalized();
		const Vector3D xaxis = up.crossProduct(zaxis).normalized();
		const Vector3D yaxis = zaxis.crossProduct(xaxis);
		const Matrix4D m = Matrix4D(
			xaxis.x, xaxis.y, xaxis.z, 0,
			yaxis.x, yaxis.y, yaxis.z, 0,
			zaxis.x, zaxis.y, zaxis.z, 0,
			0, 0, 0, 1
		);
		return (~m) - eye;
	}

	Matrix4D Matrix4D::rotation(float ax, float ay, float az)
	{
		const float a = std::cos(ax);
		const float b = std::sin(ax);
		const float c = std::cos(ay);
		const float d = std::sin(ay);
		const float e = std::cos(az);
		const float f = std::sin(az);
		return {
			c * e, b * d * e + a * f, -a * d * e + b * f, 0,
			-c * f, -b * d * f + a * e, a * d * f + b * e, 0,
			d, -b * c, a * c, 0,
			0, 0, 0, 0
		};
	}

	Matrix4D Matrix4D::rotate(float ax, float ay, float az) const
	{
		return (*this)* rotation(ax, ay, az);
	}

	/*
	   Calculates inverse matrix.
	   See Matrix::determinant for details.

		   0 4  8 12     A B C D
		   1 5  9 13     E F G H
	   M   2 6 10 14     I J K L
		   3 7 11 15     M N O P

	   Asub 5  9 13   Bsub 1  9 13   Csub 1 5 13   Dsub 1 5  9
			6 10 14        2 10 14        2 6 14        2 6 10
			7 11 15        3 11 15        3 7 15        3 7 11

	   Esub 4  8 12   Fsub 0  8 12   Gsub 0 4 12   Hsub 0 4  8
			6 10 14        2 10 14        2 6 14        2 6 10
			7 11 15        3 11 15        3 7 15        3 7 11

	   Isub 4  8 12   Jsub 0  8 12   Ksub 0 4 12   Lsub 0 4  8
			5  9 13        1  9 13        1 5 13        1 5  9
			7 11 15        3 11 15        3 7 15        3 7 11

	   Msub 4  8 12   Nsub 0  8 12   Osub 0 4 12   Psub 0 4  8
			5  9 13        1  9 13        1 5 13        1 5  9
			6 10 14        2 10 14        2 6 14        2 6 10
	 */

	Matrix4D Matrix4D::inverse(bool& success) const
	{
		const float d6_11 = c2r3 * c3r4 - c2r4 * c3r3;
		const float d6_15 = c2r3 * c4r4 - c2r4 * c4r3;
		const float d10_15 = c3r3 * c4r4 - c3r4 * c4r3;
		const float d2_11 = c1r3 * c3r4 - c1r4 * c3r3;
		const float d2_15 = c1r3 * c4r4 - c1r4 * c4r3;
		const float d2_7 = c1r3 * c2r4 - c1r4 * c2r3;
		const float d9_14 = c3r2 * c4r3 - c3r3 * c4r2;
		const float d9_15 = c3r2 * c4r4 - c3r4 * c4r2;
		const float d5_14 = c2r2 * c4r3 - c2r3 * c4r2;
		const float d5_15 = c2r2 * c4r4 - c2r4 * c4r2;
		const float d1_14 = c1r2 * c4r3 - c1r3 * c4r2;
		const float d1_15 = c1r2 * c4r4 - c1r4 * c4r2;
		const float d5_10 = c2r2 * c3r3 - c2r3 * c3r2;
		const float d5_11 = c2r2 * c3r4 - c2r4 * c3r2;
		const float d1_11 = c1r2 * c3r4 - c1r4 * c3r2;
		const float d1_6 = c1r2 * c2r3 - c1r3 * c2r2;
		const float d1_7 = c1r2 * c2r4 - c1r4 * c2r2;
		const float d1_10 = c1r2 * c3r3 - c1r3 * c3r2;

		// row 0
		const float A = c2r2 * d10_15 - c3r2 * d6_15 + c4r2 * d6_11;
		const float B = c1r2 * d10_15 - c3r2 * d2_15 + c4r2 * d2_11;
		const float C = c1r2 * d6_15 - c2r2 * d2_15 + c4r2 * d2_7;
		const float D = c1r2 * d6_11 - c2r2 * d2_11 + c3r2 * d2_7;

		// row 1
		const float E = c2r1 * d10_15 - c3r1 * d6_15 + c4r1 * d6_11;
		const float F = c1r1 * d10_15 - c3r1 * d2_15 + c4r1 * d2_11;
		const float G = c1r1 * d6_15 - c2r1 * d2_15 + c4r1 * d2_7;
		const float H = c1r1 * d6_11 - c2r1 * d2_11 + c3r1 * d2_7;

		// row 2
		const float I = c2r1 * d9_15 - c3r1 * d5_15 + c4r1 * d5_11;
		const float J = c1r1 * d9_15 - c3r1 * d1_15 + c4r1 * d1_11;
		const float K = c1r1 * d5_15 - c2r1 * d1_15 + c4r1 * d1_7;
		const float L = c1r1 * d5_11 - c2r1 * d1_11 + c3r1 * d1_7;

		// row 3
		const float M = c2r1 * d9_14 - c3r1 * d5_14 + c4r1 * d5_10;
		const float N = c1r1 * d9_14 - c3r1 * d1_14 + c4r1 * d1_10;
		const float O = c1r1 * d5_14 - c2r1 * d1_14 + c4r1 * d1_6;
		const float P = c1r1 * d5_10 - c2r1 * d1_10 + c3r1 * d1_6;

		const float det = c1r1 * A - c2r1 * B + c3r1 * C - c4r1 * D;
		if (det == 0) {
			success = false;
			return {};
		}
		const float ood = 1.0f / det;
		success = true;

		// transpose result and multiply each element by ood
		return {
			ood * A, -ood * B, ood * C, -ood * D,
			-ood * E, ood * F, -ood * G, ood * H,
			ood * I, -ood * J, ood * K, -ood * L,
			-ood * M, ood * N, -ood * O, ood * P
		};
	}

	/*
	   For 2x2 matrix M determinant is A*D - B*C

			 | A B |
		 M = |     |
			 | C D |

	   So for our 4x4 matrix determinant {@code Det = A * Asubd - B * Bsubd + C * Csubd - D*Dsubd} where

		   0 4  8 12
		   1 5  9 13
	   M   2 6 10 14
		   3 7 11 15

			 5  9 13
	   Asub  6 10 14
			 7 11 15

			 1  9 13
	   Bsub  2 10 14
			 3 11 15

			 1 5 13
	   Csub  2 6 14
			 3 7 15

			 1 5 9
	   Dsub  2 6 10
			 3 7 11

	   Here each number is a matrix element index (0 - c1r1, 1 - c1r2, etc):
	   Asubd = 5 * (10*15 - 11*14) - 9 * (6*15 - 7*14) + 13 * (6*11 - 7*10)
	   Bsubd = 1 * (10*15 - 11*14) - 9 * (2*15 - 3*14) + 13 * (2*11 - 3*10)
	   Csubd = 1 * (6*15 - 7*14) - 5 * (2*15 - 3*14) + 13 * (2*7 - 3*6)
	   Dsubd = 1 * (6*11 - 7*10) - 5 * (2*11 - 3*10) + 9 * (2*7 - 3*6)
	 */

	float Matrix4D::determinant() const
	{
		const float d6_11 = c2r3 * c3r4 - c2r4 * c3r3;
		const float d6_15 = c2r3 * c4r4 - c2r4 * c4r3;
		const float d10_15 = c3r3 * c4r4 - c3r4 * c4r3;
		const float d2_11 = c1r3 * c3r4 - c1r4 * c3r3;
		const float d2_15 = c1r3 * c4r4 - c1r4 * c4r3;
		const float d2_7 = c1r3 * c2r4 - c1r4 * c2r3;

		const float Asubd = c2r2 * d10_15 - c3r2 * d6_15 + c4r2 * d6_11;
		const float Bsubd = c1r2 * d10_15 - c3r2 * d2_15 + c4r2 * d2_11;
		const float Csubd = c1r2 * d6_15 - c2r2 * d2_15 + c4r2 * d2_7;
		const float Dsubd = c1r2 * d6_11 - c2r2 * d2_11 + c3r2 * d2_7;

		return c1r1 * Asubd - c2r1 * Bsubd + c3r1 * Csubd - c4r1 * Dsubd;
	}

	Matrix4D Matrix4D::operator + (const Matrix4D & b) const
	{
		return {
			c1r1 + b.c1r1, c1r2 + b.c1r2, c1r3 + b.c1r3, c1r4 + b.c1r4,
			c2r1 + b.c2r1, c2r2 + b.c2r2, c2r3 + b.c2r3, c2r4 + b.c2r4,
			c3r1 + b.c3r1, c3r2 + b.c3r2, c3r3 + b.c3r3, c3r4 + b.c3r4,
			c4r1 + b.c4r1, c4r2 + b.c4r2, c4r3 + b.c4r3, c4r4 + b.c4r4
		};
	}

	Matrix4D Matrix4D::operator + (const Vector3D & v) const
	{
		Matrix4D r{ *this };

		r.c4r1 = c1r1 * v.x + c2r1 * v.y + c3r1 * v.z + c4r1;
		r.c4r2 = c1r2 * v.x + c2r2 * v.y + c3r2 * v.z + c4r2;
		r.c4r3 = c1r3 * v.x + c2r3 * v.y + c3r3 * v.z + c4r3;
		r.c4r4 = c1r4 * v.x + c2r4 * v.y + c3r4 * v.z + c4r4;

		return r;
	}

	Matrix4D Matrix4D::operator - (const Vector3D & v) const
	{
		return (*this) + (-v);
	}

	Matrix4D Matrix4D::operator - (const Matrix4D & b) const
	{
		return {
			c1r1 - b.c1r1, c1r2 - b.c1r2, c1r3 - b.c1r3, c1r4 - b.c1r4,
			c2r1 - b.c2r1, c2r2 - b.c2r2, c2r3 - b.c2r3, c2r4 - b.c2r4,
			c3r1 - b.c3r1, c3r2 - b.c3r2, c3r3 - b.c3r3, c3r4 - b.c3r4,
			c4r1 - b.c4r1, c4r2 - b.c4r2, c4r3 - b.c4r3, c4r4 - b.c4r4
		};
	}

	Matrix4D Matrix4D::operator * (float scale) const
	{
		return {
			c1r1 * scale, c1r2 * scale, c1r3 * scale, c1r4 * scale,
			c2r1 * scale, c2r2 * scale, c2r3 * scale, c2r4 * scale,
			c3r1 * scale, c3r2 * scale, c3r3 * scale, c3r4 * scale,
			c4r1 * scale, c4r2 * scale, c4r3 * scale, c4r4 * scale
		};
	}

	//
	// Each row of first matrix is multiplied by the column of second (component-wise) and sum of the results is stored in result's cell.
	//
	Matrix4D Matrix4D::operator * (const Matrix4D & b) const
	{
		// r0
		const float m0 = c1r1 * b.c1r1 + c2r1 * b.c1r2 + c3r1 * b.c1r3 + c4r1 * b.c1r4;
		const float m4 = c1r1 * b.c2r1 + c2r1 * b.c2r2 + c3r1 * b.c2r3 + c4r1 * b.c2r4;
		const float m8 = c1r1 * b.c3r1 + c2r1 * b.c3r2 + c3r1 * b.c3r3 + c4r1 * b.c3r4;
		const float m12 = c1r1 * b.c4r1 + c2r1 * b.c4r2 + c3r1 * b.c4r3 + c4r1 * b.c4r4;
		// r1
		const float m1 = c1r2 * b.c1r1 + c2r2 * b.c1r2 + c3r2 * b.c1r3 + c4r2 * b.c1r4;
		const float m5 = c1r2 * b.c2r1 + c2r2 * b.c2r2 + c3r2 * b.c2r3 + c4r2 * b.c2r4;
		const float m9 = c1r2 * b.c3r1 + c2r2 * b.c3r2 + c3r2 * b.c3r3 + c4r2 * b.c3r4;
		const float m13 = c1r2 * b.c4r1 + c2r2 * b.c4r2 + c3r2 * b.c4r3 + c4r2 * b.c4r4;
		// r2
		const float m2 = c1r3 * b.c1r1 + c2r3 * b.c1r2 + c3r3 * b.c1r3 + c4r3 * b.c1r4;
		const float m6 = c1r3 * b.c2r1 + c2r3 * b.c2r2 + c3r3 * b.c2r3 + c4r3 * b.c2r4;
		const float m10 = c1r3 * b.c3r1 + c2r3 * b.c3r2 + c3r3 * b.c3r3 + c4r3 * b.c3r4;
		const float m14 = c1r3 * b.c4r1 + c2r3 * b.c4r2 + c3r3 * b.c4r3 + c4r3 * b.c4r4;
		// r3
		const float m3 = c1r4 * b.c1r1 + c2r4 * b.c1r2 + c3r4 * b.c1r3 + c4r4 * b.c1r4;
		const float m7 = c1r4 * b.c2r1 + c2r4 * b.c2r2 + c3r4 * b.c2r3 + c4r4 * b.c2r4;
		const float m11 = c1r4 * b.c3r1 + c2r4 * b.c3r2 + c3r4 * b.c3r3 + c4r4 * b.c3r4;
		const float m15 = c1r4 * b.c4r1 + c2r4 * b.c4r2 + c3r4 * b.c4r3 + c4r4 * b.c4r4;

		return {
			m0, m1, m2, m3,
			m4, m5, m6, m7,
			m8, m9, m10, m11,
			m12, m13, m14, m15
		};
	}

	Vector3D Matrix4D::operator * (const Vector3D & b) const
	{
		return {
			c1r1 * b.x + c2r1 * b.y + c3r1 * b.z + c4r1,
			c1r2 * b.x + c2r2 * b.y + c3r2 * b.z + c4r2,
			c1r3 * b.x + c2r3 * b.y + c3r3 * b.z + c4r3,
		};
	}

	Matrix4D Matrix4D::operator ~ () const
	{
		return {
			c1r1, c2r1, c3r1, c4r1,
			c1r2, c2r2, c3r2, c4r2,
			c1r3, c2r3, c3r3, c4r3,
			c1r4, c2r4, c3r4, c4r4
		};
	}

	bool Matrix4D::operator == (const Matrix4D & other) const
	{
		return c1r1 == other.c1r1 && c1r2 == other.c1r2 && c1r3 == other.c1r3 && c1r4 == other.c1r4 &&
			c2r1 == other.c2r1 && c2r2 == other.c2r2 && c2r3 == other.c2r3 && c2r4 == other.c2r4 &&
			c3r1 == other.c3r1 && c3r2 == other.c3r2 && c3r3 == other.c3r3 && c3r4 == other.c3r4 &&
			c4r1 == other.c4r1 && c4r2 == other.c4r2 && c4r3 == other.c4r3 && c4r4 == other.c4r4;
	}
}