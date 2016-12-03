//
// Created by manatee on 13.05.16.
//

#include "vec2d.h"

Vec2d vec2d_inf(1e18, 1e18);

std::istream& operator >> (std::istream& in, Vec2d& a) {
    in >> a.x >> a.y;
    return in;
}

std::ostream& operator << (std::ostream& out, const Vec2d& a) {
    out << a.x << " " << a.y;
    return out;
}

Vec2d operator - (const Vec2d& a) {
    return Vec2d(-a.x, -a.y);
}

Vec2d operator + (const Vec2d& a, const Vec2d& b) {
    return Vec2d(a.x + b.x, a.y + b.y);
}

Vec2d operator - (const Vec2d& a, const Vec2d& b) {
    return Vec2d(a.x - b.x, a.y - b.y);
}

Vec2d operator * (const Vec2d& a, double b) {
    return Vec2d(a.x * b, a.y * b);
}

Vec2d operator * (double b, const Vec2d& a) {
    return Vec2d(a.x * b, a.y * b);
}

Vec2d operator / (const Vec2d& a, double b) {
    return Vec2d(a.x / b, a.y / b);
}

double operator * (const Vec2d& a, const Vec2d& b) {
    return a.x * b.x + a.y * b.y;
}

bool operator < (const Vec2d& a, const Vec2d& b) {
    return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}

double det2d(const double x1, const double y1, const double x2, const double y2) {
    return x1 * y2 - x2 * y1;
}

double det2d(const Vec2d& a, const Vec2d& b) {
    return a.x * b.y - a.y * b.x;
}

double det2d(const Vec2d& a, const Vec2d& b, const Vec2d& c) {
    return det2d(a - b, c - b);
}
