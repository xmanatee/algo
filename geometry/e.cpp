#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "geom2d.h"

using namespace std;

int main() {
    freopen("tangent.in", "r", stdin);
    freopen("tangent.out", "w", stdout);
    Vec2d o, p;
    double r;
    cin >> o >> r >> p;

    double r2 = r * r;
    double l2 = (o - p).norm();

    //cerr << r2 << " " << l2 << "\n";
    if (l2 < r2) {
        cout << "0\n";
        return 0;
    }
    if (l2 == r2) {
        cout << "1\n" << p.x << " " << p.y << "\n";
        return 0;
    }

    double l = sqrt(l2);
    double h2 = l2 - r2;
    double h = sqrt(h2);
    double a = h2 / l;
    double g = h * r / l;

    Vec2d r_vec = (p - o);
    Vec2d p3 = p - r_vec * (a / l);
    Vec2d p2_1 = p3 + r_vec(Vec2d(0, -1)) * (g / l);
    Vec2d p2_2 = p3 + r_vec(Vec2d(0, 1)) * (g / l);
    printf("2\n%0.6f %0.6f\n%0.6f %0.6f\n", p3.x, p3.y, a, g);
    printf("%0.6f %0.6f\n%0.6f %0.6f\n", p2_1.x, p2_1.y, p2_2.x, p2_2.y);

    //printf("%.8f\n", calc_area(points));
    return 0;
}