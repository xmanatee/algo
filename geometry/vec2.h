#pragma once

#include <istream>
#include <ostream>
#include <cmath>
#include <cassert>
#include <vector>

template<typename T>
class Vec2 {
public:
    T x, y;
    Vec2(T _x, T _y): x(_x), y(_y) {}
/*
    Vec2(T angle): x(cos(angle)), y(sin(angle)) {}

    T arg() const {
        return atan2(y, x);
    }
*/
    Vec2(): x(0), y(0) {}

    T norm() const {
        return x * x + y * y;
    }

    T len() const {
        return sqrt(norm());
    }

    double d(const Vec2& b)const {
        return (*this - b).len();
    }

    Vec2 operator() (const Vec2& b) const {
        return Vec2(x * b.x - y * b.y, x * b.y + y * b.x);
    }

    Vec2& operator += (const Vec2& b) {
        x += b.x;
        y += b.y;
        return *this;
    }

    T getX() const {
        return x;
    }

    T getY() const {
        return y;
    }
};

template<class T>
std::istream& operator >> (std::istream& in, Vec2<T>& a) {
    in >> a.x >> a.y;
    return in;
}

template<class T>
std::ostream& operator << (std::ostream& out, const Vec2<T>& a) {
    out << "(" << a.x << " " << a.y << ")";
    return out;
}

template<class T>
Vec2<T> operator - (const Vec2<T>& a) {
    return Vec2<T>(-a.x, -a.y);
}

template<class T>
Vec2<T> operator + (const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x + b.x, a.y + b.y);
}

template<class T>
Vec2<T> operator - (const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x - b.x, a.y - b.y);
}

template<class T>
Vec2<T> operator * (const Vec2<T>& a, T b) {
    return Vec2<T>(a.x * b, a.y * b);
}

template<class T>
Vec2<T> operator * (T b, const Vec2<T>& a) {
    return Vec2<T>(a.x * b, a.y * b);
}

template<class T>
Vec2<T> operator / (const Vec2<T>& a, T b) {
    return Vec2<T>(a.x / b, a.y / b);
}

template<class T>
T operator * (const Vec2<T>& a, const Vec2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
bool operator < (const Vec2<T>& a, const Vec2<T>& b) {
    return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}

template<class T>
T det2(const T x1, const T y1, const T x2, const T y2) {
    return x1 * y2 - x2 * y1;
}

template<class T>
T det2(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T det2(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c) {
    return det2d(a - b, c - b);
}

template<class T>
Vec2<T> intersect_lines(T a1, T b1, T c1,
                      T a2, T b2, T c2) {
    T det = det2d(a1, b1, a2, b2);
    assert(det != 0);
    T x = det2d(-c1, b1, -c2, b2) / det;
    T y = det2d(a1, -c1, a2, -c2) / det;
    return Vec2<T>(x, y);
}

