#ifndef _SIMPLE_SPHERE_H_
#define _SIMPLE_SPHERE_H_

#include "../utils/vec3d.h"
#include "../utils/numeric.h"

class Box {
public:
    Vec3d v1, v2;
    Box(const Vec3d& _v1, const Vec3d& _v2): v1(_v1), v2(_v2) { }
    Box() {}
};

Box operator | (const Box& a, const Box& b);
Box operator | (const Box& a, const Vec3d& b);
Box operator | (const Vec3d& b, const Box& a);

#endif // _SIMPLE_SPHERE_H_
