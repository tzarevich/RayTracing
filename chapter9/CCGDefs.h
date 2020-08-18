#ifndef CCGDEFS_H_INCLUDED
#define CCGDEFS_H_INCLUDED
#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

namespace CCG
{
#define CCGint int
#define CCGdouble double
#define CCGfloat float
#define CCGchar char
#define CCGlong long
#define CCGll long long
#define CCGuint unsigned int
#define CCGbool bool

#define RAND 1000

#ifndef PI
#define PI 3.1415926535897932384626433833
#endif

#if !defined(CCGDB_MAX)
#define CCGDB_MAX DBL_MAX
#endif

#if !defined(FALSE)
#define FALSE false
#endif

#if !defined(TRUE)
#define TRUE true
#endif

#define CCGMAX(a, b) ( ((a) > (b)) ? (a) : (b) )
#define CCGMIN(a, b) ( ((a) > (b)) ? (b) : (a) )

	class CCGVec3;

	using std::shared_ptr;
	using std::make_shared;

	//! \brief 三维点，用以表示一个点的位置
	using CCGPoint3D = CCGVec3;

	//! \brief 颜色表，用以表示一个点RGB值
	using CCGColor3D = CCGVec3;


	/*
	const CCGdouble infinity = std::numeric_limits<CCGdouble>::infinity();
	const CCGdouble pi = 3.1415926535897932385;

	inline CCGdouble degrees_to_radians(CCGdouble degrees) {
		return degrees * pi / 180.0;
	}

	inline CCGdouble clamp(CCGdouble x, CCGdouble min, CCGdouble max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	inline CCGdouble random_double() {
		// Returns a random real in [0,1).
		return rand() / (RAND_MAX + 1.0);
	}

	inline CCGdouble random_double(CCGdouble min, CCGdouble max) {
		// Returns a random real in [min,max).
		return min + (max - min)*random_double();
	}

	inline CCGint random_int(int min, int max) {
		// Returns a random integer in [min,max].
		return static_cast<CCGint>(random_double(min, max + 1));
		*/
}

#endif