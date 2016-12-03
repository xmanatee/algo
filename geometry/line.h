#ifndef _LINE_H_
#define _LINE_H_

#include "vec2d.h"

class Line {
public:
    double a, b, c;
    Line(double _a, double _b, double _c): a(_a), b(_b), c(_c) {}
    Line(const Vec2d& v, const Vec2d& u): a(u.y - v.y), b(-u.x + v.x), c(det2d(u, v)) {}
    double norm() const {
        return a * a + b * b;
    }

    double len() const {
        return sqrt(a * a + b * b);
    }

    double operator () (const Vec2d& v) const {
        return a * v.x + b * v.y + c;
    }

    Vec2d intersectX() const {
        return intersect_lines(a, b, c, 0, 1, 0);
    }
    Vec2d intersectY() const {
        return intersect_lines(a, b, c, 1, 0, 0);
    }

    double signedDist(const Vec2d& v) const {
        return (a * v.x + b * v.y + c) / len();
    }
};

Line operator + (const Line& l1, const Line& l2) {
    return Line(l1.a + l2.a, l1.b + l2.b, l1.c + l2.c);
}

Line operator - (const Line& l1, const Line& l2) {
    return Line(l1.a - l2.a, l1.b - l2.b, l1.c - l2.c);
}

Line operator * (const Line& l, double f) {
    return Line(l.a * f, l.b * f, l.c * f);
}

Line operator / (const Line& l, double f) {
    return Line(l.a / f, l.b / f, l.c / f);
}

Line operator * (double f, const Line& l) {
    return Line(l.a * f, l.b * f, l.c * f);
}

std::ostream& operator << (std::ostream& out, const Line& line) {
    out << "{" << line.a << "," << line.b << "," << line.c << "}";
    return out;
}

#endif // _LINE_H_