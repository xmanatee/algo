#ifndef _VEC2D_H_
#define _VEC2D_H_

#include <istream>
#include <ostream>
#include <cmath>
#include <vector>

static const double EPSILON = 1e-9;

class Vec2d {
public:
    double x, y;
    Vec2d(double _x, double _y): x(_x), y(_y) {}
    Vec2d(double angle): x(cos(angle)), y(sin(angle)) {}

    Vec2d(): x(0), y(0) {}

    double norm() const {
        return x * x + y * y;
    }
    double len() const {
        return sqrt(norm());
    }

    double arg() const {
        return atan2(y, x);
    }

    Vec2d operator() (const Vec2d& b) const {
        return Vec2d(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

extern Vec2d vec2d_inf;

std::istream& operator >> (std::istream& in, Vec2d& a);
std::ostream& operator << (std::ostream& out, const Vec2d& a);
Vec2d operator - (const Vec2d& a);
Vec2d operator + (const Vec2d& a, const Vec2d& b);
Vec2d operator - (const Vec2d& a, const Vec2d& b);
Vec2d operator * (const Vec2d& a, double b);
Vec2d operator * (double b, const Vec2d& a);
Vec2d operator / (const Vec2d& a, double b);
double operator * (const Vec2d& a, const Vec2d& b);
bool operator < (const Vec2d& a, const Vec2d& b);
double det2d(const double x1, const double y1, const double x2, const double y2);
double det2d(const Vec2d& a, const Vec2d& b);
double det2d(const Vec2d& a, const Vec2d& b, const Vec2d& c);

#endif // _VEC2D_H_