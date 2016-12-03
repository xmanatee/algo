#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

class Vec2d {
public:
    const double EPSILON
    double x, y;
    Vec2d(double _x, double _y): x(_x), y(_y) {}

    Vec2d(): x(0), y(0) {}

    double norm() {
        return x * x + y * y;
    }
    double len() {
        return sqrt(norm());
    }
};

istream& operator >> (istream& in, Vec2d& a) {
    in >> a.x >> a.y;
    return in;
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

double operator * (const Vec2d& a, const Vec2d& b) {
    return a.x * b.y - a.y * b.x;
}

Vec2d intersect_lines(double a1, double b1, double c1,
                      double a2, double b2, double c2) {
    double x, y;
    if (a1 == 0) {
        y = -c1 / b1;
        x = -(c2 + b2 * y) / a2;
    }
    else {
        double k = a2 / a1;
        b2 -= b1 * k;
        c2 -= c1 * k;
        y = -c2 / b2;
        x = -(c1 + b1 * y) / a1;
    }
    return Vec2d(x, y);
}

bool on_segment(Vec2d& p, Vec2d& a, Vec2d& b) {
    bool on_line = fabs((a - p) * (b - p)) < Vec2d::EPSILON;
    bool x_equals = fabs((b - a).x) == fabs((b - p).x) + fabs((p - a).x);
    bool y_equals = fabs((b - a).y) == fabs((b - p).y) + fabs((p - a).y);
    return on_line && x_equals && y_equals;
    //return (fabs((b - a).len() - (a - p).len() - (b - p).len()) < 1e-10);
}

int main() {
    //freopen("intersec2.in", "r", stdin);
    //freopen("intersec2.out", "w", stdout);

    Vec2d a, b, c, d;
    cin >> a >> b >> c >> d;

    Vec2d ab = b - a;
    Vec2d cd = d - c;

    if (on_segment(a, c, d) || on_segment(b, c, d)
        || on_segment(c, a, b) || on_segment(d, a, b)) {
            cout << "YES\n";
        return 0;
    }

    double a1 = -ab.y, b1 = ab.x, c1 = -a1 * a.x - b1 * a.y;
    double a2 = -cd.y, b2 = cd.x, c2 = -a2 * c.x - b2 * c.y;

    Vec2d h = intersect_lines(a1, b1, c1, a2, b2, c2);

    if (on_segment(h, a, b) && on_segment(h, c, d)) {
        cout << "YES\n";
        return 0;
    }

    cout << "NO\n";
    return 0;
}