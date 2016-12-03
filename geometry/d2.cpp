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

    Vec2d operator() (const Vec2d& b) {
        return Vec2d(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

istream& operator >> (istream& in, Vec2d& a) {
    in >> a.x >> a.y;
    return in;
}

ostream& operator << (ostream& out, Vec2d& a) {
    out << a.x << " " << a.y;
    return out;
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
    return a.x * b.y - a.y * b.x;
}

int main() {
    freopen("intersec4.in", "r", stdin);
    freopen("intersec4.out", "w", stdout);

    cout.precision(15);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Vec2d o1, o2;
        double r1, r2;
        cin >> o1 >> r1 >> o2 >> r2;

        Vec2d r_vec = o2 - o1;
        double l2 = r_vec.norm();
        double l = sqrt(l2);

        if (l2 == 0) {
            if (r1 == r2) {
                if (r1 == 0) {
                    cout << "1\n" << o1 << "\n";
                }
                else {
                    cout << "3\n";
                }
            }
            else {
                cout << "0\n";
            }
            continue; //return 0;
        }

        if ((r1 + r2) * (r1 + r2) == l2) {
            Vec2d ans_vec = o1 + r_vec * r1 / l;
            cout << "1\n" << ans_vec << "\n";
            continue; //return 0;
        }

        if ((r1 - r2) * (r1 - r2) == l2) {
            Vec2d ans_vec;
            if (r1 > r2) {
                ans_vec = o1 + r_vec * r1 / l;
            }
            else {
                ans_vec = o1 - r_vec * r1 / l;
            }
            cout << "1\n" << ans_vec << "\n";
            continue; //return 0;
        }

        if (((r1 + r2) * (r1 + r2) < l2) || (l2 < (r2 - r1) * (r2 - r1))) {
            cout << "0\n";
            continue; //return 0;
        }

        double a = (r1 * r1 + l2 - r2 * r2) / 2 / l;
        double g = sqrt(r1 * r1 - a * a);

        Vec2d h = o1 + r_vec * a / l;

        Vec2d p_1 = h + r_vec(Vec2d(0, 1)) * g / l;
        Vec2d p_2 = h + r_vec(Vec2d(0, -1)) * g / l;

        cout << "2\n" << h << "\n" << fabs(a) << " " << g << "\n";
        cout << p_1 << "\n" << p_2 << "\n";
    }

    return 0;
}