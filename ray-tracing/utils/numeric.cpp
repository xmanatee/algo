#ifndef _NUMERIC_CPP_
#define _NUMERIC_CPP_

#include "numeric.h"

bool lessOrEqual(real a, real b) {
    return a - real_epsilon < b;
}

bool isZero(real x) {
    return (fabsf(x) < real_epsilon);
}

bool isInf(real d) {
    return (d > real_inf / 10);
}
bool isNInf(real d) {
    return (d < real_ninf / 10);
}

real sqr(real d) {
    return d * d;
}

real cube(real d) {
    return d * d * d;
}

real cut(real x, real a, real b) {
    if (x < a) return a;
    if (x > b) return b;
    return x;
}

real sign(real x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

real n2(real a, real b) {
    return sqrtf(sqr(a) + sqr(b));
}

#endif // _NUMERIC_CPP_