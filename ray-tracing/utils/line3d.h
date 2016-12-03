#ifndef _LINE3D_H_
#define _LINE3D_H_

#include "vec3d.h"

class Line3d {
public:
    Vec3d base, dir;
    real attribute = 1;
    Line3d(const Vec3d& _base, const Vec3d& _dir): base(_base), dir(_dir.normalized()) {}
    Line3d() {}

    real dist(const Vec3d& a) const;

    Vec3d operator() (real t) const;
};

std::ostream& operator << (std::ostream& out, const Line3d& line);


#endif // _LINE3D_H_