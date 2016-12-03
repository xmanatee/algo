#ifndef _GEOM_CPP_
#define _GEOM_CPP_

#include "geom.h"
#include "numeric.h"

real distToPlane(const Vec3d& line_base, const Vec3d& dir, const Vec3d& normal, const Vec3d& plane_base) {
    real cross1 = dir * normal;
    if (isZero(cross1)) return real_inf;
    real cross2 = (plane_base - line_base) * normal;
    real ans = cross2 / cross1;
    return ans;
}

#endif // _GEOM_CPP_