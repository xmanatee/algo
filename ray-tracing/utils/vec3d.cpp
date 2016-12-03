#ifndef _VEC3D_CPP_
#define _VEC3D_CPP_

#include "vec3d.h"

real Vec3d::norm() const {
    return x * x + y * y + z * z;
}

real Vec3d::len() const {
    return sqrtf(norm());
}

void Vec3d::normalize() {
    real l = len();
    x /= l;
    y /= l;
    z /= l;
}

void Vec3d::operator+=(const Vec3d &v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vec3d::operator-=(const Vec3d &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vec3d::operator*=(const Vec3d &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

void Vec3d::operator/=(real d) {
    x /= d;
    y /= d;
    z /= d;
}

void Vec3d::operator*=(real d) {
    x *= d;
    y *= d;
    z *= d;
}

Vec3d Vec3d::dot(const Vec3d &v) const {
    return Vec3d(x * v.x, y * v.y, z * v.z);
}

Vec3d Vec3d::normalized() const {
    real l = len();
    return Vec3d(x / l, y / l, z / l);
}

std::istream& operator >> (std::istream& in, Vec3d& a) {
    in >> a.x >> a.y >> a.z;
    return in;
}

std::ostream& operator << (std::ostream& out, const Vec3d& a) {
    out << "vec3d{" << a.x << "," << a.y << "," << a.z << "}";
    return out;
}

Vec3d operator - (const Vec3d& a) {
    return Vec3d(-a.x, -a.y, -a.z);
}

Vec3d operator + (const Vec3d& a, const Vec3d& b) {
    return Vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3d operator - (const Vec3d& a, const Vec3d& b) {
    return Vec3d(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3d operator * (const Vec3d& a, real b) {
    return Vec3d(a.x * b, a.y * b, a.z * b);
}

Vec3d operator * (real b, const Vec3d& a) {
    return Vec3d(a.x * b, a.y * b, a.z * b);
}

Vec3d operator / (const Vec3d& a, real b) {
    return Vec3d(a.x / b, a.y / b, a.z / b);
}

real operator * (const Vec3d& a, const Vec3d& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

real det2d(real a, real b, real c, real d) {
    return a * d - b * c;
}

Vec3d operator ^ (const Vec3d& a, const Vec3d& b) {
    return Vec3d(det2d(a.y, a.z, b.y, b.z),
                 -det2d(a.x, a.z, b.x, b.z),
                 det2d(a.x, a.y, b.x, b.y));
}

bool operator < (const Vec3d& a, const Vec3d& b) {
    if (a.x != b.x) {
        return a.x < b.y;
    }
    if (a.y != b.y) {
        return a.y < b.y;
    }
    if (a.z != b.z) {
        return a.z < b.z;
    }
    return false;
}

real det3d(const Vec3d& a, const Vec3d& b, const Vec3d& c) {
    return a.x * det2d(b.y, b.z, c.y, c.z)
           - a.y * det2d(b.x, b.z, c.x, c.z)
           + a.z * det2d(b.x, b.y, c.x, c.y);
}

Vec3d min(const Vec3d& a, const Vec3d& b) {
    return Vec3d(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vec3d max(const Vec3d& a, const Vec3d& b) {
    return Vec3d(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

#endif // _VEC3D_H_