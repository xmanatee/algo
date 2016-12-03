#ifndef _VEC3D_H_
#define _VEC3D_H_

#include <istream>
#include <ostream>
#include <cmath>

#include "numeric.h"


class Vec3d {
public:
    real x, y, z;

    Vec3d(real _x, real _y, real _z) : x(_x), y(_y), z(_z) { }

    Vec3d() : x(0), y(0), z(0) { }

    real norm() const;

    real len() const;

    Vec3d normalized() const;

    void normalize();

    void operator += (const Vec3d& v);
    void operator -= (const Vec3d& v);
    void operator *= (const Vec3d& v);
    void operator /= (real d);
    void operator *= (real d);
    Vec3d dot(const Vec3d& v) const;
};

const Vec3d vec3d_inf(real_inf, real_inf, real_inf);
const Vec3d vec3d_zero(0, 0, 0);
const Vec3d vec3d_ones(1, 1, 1);

std::istream& operator >> (std::istream& in, Vec3d& a);
std::ostream& operator << (std::ostream& out, const Vec3d& a);
Vec3d operator - (const Vec3d& a);
Vec3d operator + (const Vec3d& a, const Vec3d& b);
Vec3d operator - (const Vec3d& a, const Vec3d& b);
Vec3d operator * (const Vec3d& a, real b);
Vec3d operator * (real b, const Vec3d& a);
Vec3d operator / (const Vec3d& a, real b);
real operator * (const Vec3d& a, const Vec3d& b);
real det2d(real a, real b, real c, real d);
Vec3d operator ^ (const Vec3d& a, const Vec3d& b);
bool operator < (const Vec3d& a, const Vec3d& b);
Vec3d min(const Vec3d& a, const Vec3d& b);
Vec3d max(const Vec3d& a, const Vec3d& b);

real det3d(const Vec3d& a, const Vec3d& b, const Vec3d& c);
#endif // _VEC3D_H_