#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../utils/vec3d.h"
#include "figure3d.h"

class Sphere : public Figure3d {
public:
    Vec3d loc;
    real r;

    Sphere(const Vec3d& _loc, real _r): Figure3d(SPHERE),
                                             loc(_loc),
                                             r(_r) {
        box = Box(_loc - r * vec3d_ones, _loc + r * vec3d_ones);
    }

    Vec3d getNormalIn(const Vec3d &v) const override {
        return (v - loc).normalized();
    }

    Color getColorIn(const Vec3d& v) const override {
        Vec3d rv = v - loc;
        real phi = atan(rv.y / rv.x);
        real psi = atan(n2(rv.x, rv.y) / rv.z);
        return traits.getColorIn(Vec2d(phi, psi));
    }

    bool intersectsWith(const Line3d& line) const override {
        if (lessOrEqual(line.dist(loc), r)) return 1;
        return 0;
    }

    real intersectWith(const Line3d& line) const override {
        Vec3d k = line.base - loc;
        real b = k * line.dir;
        real c = k.norm() - sqr(r);
        real d = sqr(b) - c;
        if(d >= 0) {
            real sqrtfd = sqrtf(d);

            // t, a == 1
            real t1 = -b + sqrtfd;
            real t2 = -b - sqrtfd;

            real min_t  = std::min(t1,t2);
            real max_t = std::max(t1,t2);

            real t = (min_t >= 0) ? min_t : max_t;

            if (t <= 0) return real_inf;
            return t;
        }
        return real_inf;
    }

};

#endif // _SPHERE_H_