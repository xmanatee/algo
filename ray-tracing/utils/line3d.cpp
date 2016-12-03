#include "line3d.h"

real Line3d::dist(const Vec3d& a) const {
    return ((a - base) ^ dir).len() / dir.len();  // optimize
}

Vec3d Line3d::operator()(real t) const {
    return base + t * dir;
}


std::ostream& operator << (std::ostream& out, const Line3d& line) {
    out << "line3d{" << line.base << "," << line.dir << "}";
    return out;
}