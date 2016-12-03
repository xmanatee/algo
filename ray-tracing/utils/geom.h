#ifndef _GEOM_H_
#define _GEOM_H_

#include "vec3d.h"

real distToPlane(const Vec3d& line_base, const Vec3d& dir, const Vec3d& normal, const Vec3d& plane_base);

#endif // _GEOM_H_