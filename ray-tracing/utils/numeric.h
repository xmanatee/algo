#ifndef _REAL_H_
#define _REAL_H_

#include <cfloat>
#include <cmath>

typedef float real;
const real real_inf = FLT_MAX;
const real real_ninf = -FLT_MAX;
const real real_epsilon = 1e-3;

bool lessOrEqual(real a, real b);
bool isZero(real x);
bool isInf(real d);
bool isNInf(real d);
real sqr(real d);
real cube(real d);
real cut(real x, real a, real b);
real sign(real x);
real n2(real a, real b);



typedef unsigned char small;
const small small_max = 255;
const small small_min = 0;

typedef signed char signed_small;
const signed_small signed_small_max = 127;
const signed_small signed_small_min = -127;


#endif // _REAL_H_