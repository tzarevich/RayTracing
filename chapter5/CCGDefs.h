#ifndef CCGDEFS_H_INCLUDED
#define CCGDEFS_H_INCLUDED
#pragma once
#include <cmath>

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

#endif