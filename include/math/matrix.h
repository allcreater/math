#ifndef MATH_MATRIX_H_
#define MATH_MATRIX_H_

#include <iostream>
#include "math/vector_float.h"


namespace math {

struct float4x4 {
	static const float4x4 identity;
	static const float4x4 zero;


	float4x4() noexcept
		: m00(0), m01(0), m02(0), m03(0),
		m10(0), m11(0), m12(0), m13(0),
		m20(0), m21(0), m22(0), m23(0),
		m30(0), m31(0), m32(0), m33(0)
	{}

	float4x4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) noexcept
		: m00(m00), m01(m01), m02(m02), m03(m03),
		m10(m10), m11(m11), m12(m12), m13(m13),
		m20(m20), m21(m21), m22(m22), m23(m23),
		m30(m30), m31(m31), m32(m32), m33(m33)
	{}


	float4x4& operator+=(const float4x4& m) noexcept
	{
		m00 += m.m00; m01 += m.m01; m02 += m.m02; m03 += m.m03;
		m10 += m.m10; m11 += m.m11; m12 += m.m12; m13 += m.m13;
		m20 += m.m20; m21 += m.m21; m22 += m.m22; m23 += m.m23;
		m30 += m.m30; m31 += m.m31; m32 += m.m32; m33 += m.m33;
		return *this;
	}

	float4x4& operator-=(const float4x4& m) noexcept
	{
		m00 -= m.m00; m01 -= m.m01; m02 -= m.m02; m03 -= m.m03;
		m10 -= m.m10; m11 -= m.m11; m12 -= m.m12; m13 -= m.m13;
		m20 -= m.m20; m21 -= m.m21; m22 -= m.m22; m23 -= m.m23;
		m30 -= m.m30; m31 -= m.m31; m32 -= m.m32; m33 -= m.m33;
		return *this;
	}

	float4x4& operator*=(float val) noexcept
	{
		m00 *= val; m01 *= val; m02 *= val; m03 *= val;
		m10 *= val; m11 *= val; m12 *= val; m13 *= val;
		m20 *= val; m21 *= val; m22 *= val; m23 *= val;
		m30 *= val; m31 *= val; m32 *= val; m33 *= val;
		return *this;
	}

	// Post-multiplies this matrix with the specified matrix.
	float4x4& operator*=(const float4x4& m) noexcept;

	float4x4& operator/=(float val) noexcept
	{
		assert(!approx_equal(val, 0.0f));

		m00 /= val; m01 /= val; m02 /= val; m03 /= val;
		m10 /= val; m11 /= val; m12 /= val; m13 /= val;
		m20 /= val; m21 /= val; m22 /= val; m23 /= val;
		m30 /= val; m31 /= val; m32 /= val; m33 /= val;
		return *this;
	}



	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};

bool operator==(const float4x4& l, const float4x4& r) noexcept;

inline bool operator!=(const float4x4& l, const float4x4& r) noexcept
{
	return !(l == r);
}

inline float4x4 operator+(const float4x4& l, const float4x4 r) noexcept
{
	return float4x4(
		l.m00 + r.m00, l.m01 + r.m01, l.m02 + r.m02, l.m03 + r.m03,
		l.m10 + r.m10, l.m11 + r.m11, l.m12 + r.m12, l.m13 + r.m13,
		l.m20 + r.m20, l.m21 + r.m21, l.m22 + r.m22, l.m23 + r.m23,
		l.m30 + r.m30, l.m31 + r.m31, l.m32 + r.m32, l.m33 + r.m33
	);
}

inline float4x4 operator-(const float4x4& l, const float4x4 r) noexcept
{
	return float4x4(
		l.m00 - r.m00, l.m01 - r.m01, l.m02 - r.m02, l.m03 - r.m03,
		l.m10 - r.m10, l.m11 - r.m11, l.m12 - r.m12, l.m13 - r.m13,
		l.m20 - r.m20, l.m21 - r.m21, l.m22 - r.m22, l.m23 - r.m23,
		l.m30 - r.m30, l.m31 - r.m31, l.m32 - r.m32, l.m33 - r.m33
	);
}

inline float4x4 operator*(const float4x4& m, float val) noexcept
{
	return float4x4(
		m.m00 * val, m.m01 * val, m.m02 * val, m.m03 * val,
		m.m10 * val, m.m11 * val, m.m12 * val, m.m13 * val,
		m.m20 * val, m.m21 * val, m.m22 * val, m.m23 * val,
		m.m30 * val, m.m31 * val, m.m32 * val, m.m33 * val
	);
}

inline float4x4 operator*(float  val, const float4x4& m) noexcept
{
	return float4x4(
		m.m00 * val, m.m01 * val, m.m02 * val, m.m03 * val,
		m.m10 * val, m.m11 * val, m.m12 * val, m.m13 * val,
		m.m20 * val, m.m21 * val, m.m22 * val, m.m23 * val,
		m.m30 * val, m.m31 * val, m.m32 * val, m.m33 * val
	);
}

// Post-multiplies l matrix with r.
float4x4 operator*(const float4x4& l, const float4x4& r) noexcept;

inline float4x4 operator/(const float4x4& m, float val) noexcept
{
	assert(!approx_equal(val, 0.0f));

	return float4x4(
		m.m00 / val, m.m01 / val, m.m02 / val, m.m03 / val,
		m.m10 / val, m.m11 / val, m.m12 / val, m.m13 / val,
		m.m20 / val, m.m21 / val, m.m22 / val, m.m23 / val,
		m.m30 / val, m.m31 / val, m.m32 / val, m.m33 / val
	);
}

std::ostream& operator<<(std::ostream& out, const float4x4& m);

std::wostream& operator<<(std::wostream& out, const float4x4& m);

//  Calculates the determinant of the matrix m.
float det(const float4x4& m) noexcept;

// Computes the inverse of the matrix.
float4x4 inverse(const float4x4& m) noexcept;

// Determines whether the specified matrix is orthogonal.
inline bool is_orthogonal(const float4x4& m) noexcept
{
	const float abs_d = std::abs(det(m));
	return approx_equal(abs_d, 1.0f);
}

// Multiplies the given matrix by the column vector. 
inline float4 mul(const float4x4& m, const float4& v) noexcept
{
	return float4(
		(m.m00 * v.x) + (m.m01 * v.y) + (m.m02 * v.z) + (m.m03 * v.w),
		(m.m10 * v.x) + (m.m11 * v.y) + (m.m12 * v.z) + (m.m13 * v.w),
		(m.m20 * v.x) + (m.m21 * v.y) + (m.m22 * v.z) + (m.m23 * v.w),
		(m.m30 * v.x) + (m.m31 * v.y) + (m.m32 * v.z) + (m.m33 * v.w)
	);
}

// Multiplies matrix by the column vector float4(v.x, v.y, z, w). 
inline float4 mul(const float4x4& m, const float2& v, float z = 0.f, float w = 1.f) noexcept
{
	return mul(m, float4(v.x, v.y, z, w));
}

// Multiplies matrix by the column vector float4(v.x, v.y, v.z, w). 
inline float4 mul(const float4x4& m, const float3& v, float w = 1.f) noexcept
{
	return mul(m, float4(v.x, v.y, v.z, w));
}

// Puts the matrix m into a float array in a column major order.
inline float* to_array_column_major_order(const float4x4& m, float* arr) noexcept
{
	arr[0] = m.m00; arr[1] = m.m10; arr[2] = m.m20; arr[3] = m.m30;
	arr[4] = m.m01; arr[5] = m.m11; arr[6] = m.m21; arr[7] = m.m31;
	arr[8] = m.m02; arr[9] = m.m12; arr[10] = m.m22; arr[11] = m.m32;
	arr[12] = m.m03; arr[13] = m.m13; arr[14] = m.m23; arr[15] = m.m33;

	return arr;
}

// Puts the matrix m into a float array in a row major order.
inline float* to_array_row_major_order(const float4x4& m, float* arr) noexcept
{
	arr[0] = m.m00; arr[1] = m.m01; arr[2] = m.m02; arr[3] = m.m03;
	arr[4] = m.m10; arr[5] = m.m11; arr[6] = m.m12; arr[7] = m.m13;
	arr[8] = m.m20; arr[9] = m.m21; arr[10] = m.m22; arr[11] = m.m23;
	arr[12] = m.m30; arr[13] = m.m31; arr[14] = m.m32; arr[15] = m.m33;

	return arr;
}

// Calculates the sum of the elements on the main diagonal. tr(M).
inline float trace(const float4x4& m) noexcept
{
	return m.m00 + m.m11 + m.m22 + m.m33;
}

// Reflects the matrix over its main diagonal to obtain transposed matrix.
inline float4x4 transpose(const float4x4& m) noexcept
{
	return float4x4(
		m.m00, m.m10, m.m20, m.m30,
		m.m01, m.m11, m.m21, m.m31,
		m.m02, m.m12, m.m22, m.m32,
		m.m03, m.m13, m.m23, m.m33
	);
}

} // namespace math

#endif // MATH_MATRIX_H_