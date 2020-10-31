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
#define CCGuchar unsigned char
#define CCGlong long
#define CCGll long long
#define CCGuint unsigned int
#define CCGbool bool

#ifndef PI
#define PI 3.1415926535897932385
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

}

namespace CCG
{
	using std::shared_ptr;
	using std::make_shared;

	class CCGVec3;
	//! \brief 三维点，用以表示一个点的位置
	using CCGPoint3D = CCGVec3;

	//! \brief 颜色表，用以表示一个点RGB值
	using CCGColor3D = CCGVec3;

	inline CCGdouble degrees_to_radians(CCGdouble degrees) {
		return degrees * PI / 180.0;
	}

	inline CCGdouble Clamp(CCGdouble x, CCGdouble min, CCGdouble max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	inline CCGdouble Rand() {
		// Returns a random real in [0,1).
		return rand() / (RAND_MAX + 1.0);
	}

	inline CCGdouble RandBW(CCGdouble min, CCGdouble max) {
		// Returns a random real in [min,max).
		return min + (max - min)*Rand();
	}

	inline CCGint RandInt(CCGint min, CCGint max) {
		return static_cast<CCGint>(RandBW(min, max + 1));
	}
}

#endif