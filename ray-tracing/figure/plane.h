#ifndef _PLANE_H_
#define _PLANE_H_

#include "figure3d.h"

#include "../utils/geom.h"

class Plane: public Figure3d {
public:
    Vec3d loc;
    Vec3d normal;
    Vec3d e1, e2;
    Plane(Vec3d _normal, Vec3d _loc): Figure3d(PLANE),
                                      loc(_loc),
                                      normal(_normal.normalized()) {
        box = Box(-vec3d_inf, vec3d_inf),
        e1 = normal ^ loc.normalized();
        e2 = normal ^ e1;
    }
    
    Vec3d getNormalIn(const Vec3d &v) const override {
        return normal;
    }

    Color getColorIn(const Vec3d& v) const override {
        return traits.getColorIn(Vec2d((v - loc) * e1, (v - loc) * e2));
    }

    bool intersectsWith(const Line3d& line) const override {
        return true;
        return !isZero(line.dir * normal);
    }

    real intersectWith(const Line3d& line) const override {
        real t = distToPlane(line.base, line.dir, normal, loc);

        if (lessOrEqual(t, 0)) return real_inf;

//        std::cerr << "L: " << t << std::endl;

        return t;
    }
};

#endif // _PLANE_H_