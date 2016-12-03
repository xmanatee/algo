#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

typedef double big;
typedef pair<big, big> point;
typedef vector<point> poly;

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

    Vec2d operator() (const Vec2d& b) {
        return Vec2d(x * b.x - y * b.y, x * b.y + y * b.x);
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

int main() {
    //freopen("intersec4.in", "r", stdin);
    //freopen("intersec4.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Vec2d o1, o2;
        double r1, r2;
        cin >> o1 >> r1 >> o2 >> r2;

        Vec2d r_vec = o2 - o1;
        double l2 = r_vec.norm();
        double l = sqrt(l2);

        if ((l2 == 0) && (r1 == r2)) {
            cout << "3\n";
            continue; //return 0;
        }

        if ((r1 + r2) * (r1 + r2) == l2) {
            Vec2d ans_vec = o1 + r_vec * (r1 / l);
            printf("1\n%0.9f %0.9f\n", ans_vec.x, ans_vec.y);
            continue; //return 0;
        }

        if ((r1 - r2) * (r1 - r2) == l2) {
            if (r1 < r2) {
                swap(o1, o2);
                swap(r1, r2);
            }
            Vec2d ans_vec = o1 + r_vec * (r1 / l);
            printf("1\n%0.9f %0.9f\n", ans_vec.x, ans_vec.y);
            continue; //return 0;
        }

        if ((r1 + r2 < l) || (r1 + l < r2) || (r2 + l < r1)) {
            cout << "0\n";
            continue; //return 0;
        }

        double p = 0.5 * (r1 + r2 + l);
        double s = sqrt(p * (p - r1) * (p - r2) * (p - l));
        double g = 2 * s / l;
        double a = sqrt(r1 * r1 - g * g);

        Vec2d h = o1 + r_vec * (a / l);
        if ((r2 > r1) && (r2 * r2 > l * l + r1 * r1)) {
            h = o1 - r_vec * (a / l);
        }
        Vec2d p_1 = h + r_vec(Vec2d(0, 1)) * (g / l);
        Vec2d p_2 = h + r_vec(Vec2d(0, -1)) * (g / l);
        if ((p_1 - p_2).norm() < 1e-10) {
            printf("1\n%0.9f %0.9f\n", (p_1 + p_2).x / 2, (p_1 + p_2).y / 2);
        }
        printf("2\n%0.9f %0.9f\n%0.9f %0.9f\n", h.x, h.y, a, g);
        printf("%0.9f %0.9f\n%0.9f %0.9f\n", p_1.x, p_1.y, p_2.x, p_2.y);
    }

    return 0;
}