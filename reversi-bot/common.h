#ifndef _COMMON_H_
#define _COMMON_H_

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#include "timer.h"

typedef char Int;

typedef long long AwardType;
const AwardType INF_AWARD = (const AwardType) 1e6;

Timer timer(1.5);

#endif // _COMMON_H_