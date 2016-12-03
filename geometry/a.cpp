#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

class Vec2d {
public:
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

Vec2d operator * (const Vec2d& a, const Vec2d& b) {
    return Vec2d(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
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

bool on_segment(Vect2d& p, Vec2d& a, Vec2d& c) {
    return (fabs((b - a).len() - (a - h).len() - (b - h).len()) < 1e-7);
}

int main() {
    freopen("distance4.in", "r", stdin);
    freopen("distance4.out", "w", stdout);

    Vec2d p, a, b;
    cin >> p >> a >> b;

    Vec2d ab = b - a;

    if (ab.norm() == 0) {
        printf("%0.7f", (a - p).len());
        return 0;
    }

    double a1 = ab.x, b1 = ab.y, c1 = -a1 * p.x - b1 * p.y;
    double a2 = -ab.y, b2 = ab.x, c2 = -a2 * a.x - b2 * a.y;

    Vec2d h = intersect_lines(a1, b1, c1, a2, b2, c2);

    double ans = min((p - a).len(), (p - b).len());

    if (fabs(ab.len() - (a - h).len() - (b - h).len()) < 1e-7) {
        ans = min(ans, (p - h).len());
    }

    printf("%0.7f\n", ans);

    return 0;
}