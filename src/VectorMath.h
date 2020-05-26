#pragma once

#ifndef _USE_MATH_DEFINES
#define M_E        2.71828182845904523536f // e
#define M_LOG2E    1.44269504088896340736f // log2(e)
#define M_LOG10E   0.434294481903251827651f // log10(e)
#define M_LN2      0.693147180559945309417f // ln(2)
#define M_LN10     2.30258509299404568402f // ln(10)
#define M_PI       3.14159265358979323846f // pi
#define M_TWOPI    6.28318530718058647692f
#define M_PI_2     1.57079632679489661923f // pi/2
#define M_PI_4     0.785398163397448309616f // pi/4
#define M_1_PI     0.318309886183790671538f // 1/pi
#define M_2_PI     0.636619772367581343076f // 2/pi
#define M_2_SQRTPI 1.12837916709551257390f // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880f // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401f // 1/sqrt(2)
#endif

#include <cmath>

// Scales a vector a by float scale
// a = a * scale
// result stored in a
inline void scale(float* a, const float& scale)
{
	for (int i = 0; i < 3; i++, a++) {
		*a = *a * scale;
	}
}

// Adds vector b * scale to vector a
// a = a + (b * scale)
// Result is stored in vector a
inline void add(float* a, const float* b, const float& scale = 1.0f)
{
	for (int i = 0; i < 3; i++) {
		*a++ += scale * (*b++);
	}
}

// Subtracts vector b * scale from vector a
// a = a - (b * scale)
// Result is stored in vector a
inline void sub(float* a, const float* b, const float& scale = 1.0f)
{
	for (int i = 0; i < 3; i++) {
		*a++ -= scale * (*b++);
	}
}

// Normalises a vector n
// n = n / sqrt(x^2 + y^2 + z^2)
// Result stored in vector n
inline void norm(float* n)
{
	float l = 0.0f;

	for (int i = 0; i < 3; i++) {
		l += n[i] * n[i];
	}

	l = sqrt(l);

	for (int i = 0; i < 3; i++) {
		n[i] /= l;
	}
}

// Cross product of vector a and vector b sets  vector c to be the result
// c = a X b
// Result stored in vector c
inline void cross(const float* a, const float* b, float* c)
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

// Dot product between vector a and vector b, set the result to float dot
// dot = a.b;
// Result stored in float dot
inline void dot(const float* a, const float* b, float& dot)
{
	dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
