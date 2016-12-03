#include <cstdio>
#include <cstdlib>
#include <istream>
#include <ostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

static const double EPSILON = 1e-9;

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

std::istream& operator >> (std::istream& in, Vec2d& a) {
    in >> a.x >> a.y;
    return in;
}

std::ostream& operator << (std::ostream& out, Vec2d& a) {
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

std::vector<Vec2d> intersectCircles(const Vec2d& o1, double r1, const Vec2d& o2, double r2) {
    Vec2d r_vec = o2 - o1;
    double l2 = r_vec.norm();

    std::vector<Vec2d> ans;

    if ((l2 == 0) && (r1 == r2) && (r1 == 0)) {
        ans.push_back(o1);
        return ans;
    }

    double l = sqrt(l2);

    if ((r1 + r2) * (r1 + r2) == l2) {
        ans.push_back(o1 + r_vec * r1 / l);
        return ans;
    }

    if ((r1 - r2) * (r1 - r2) == l2) {
        if (r1 > r2) {
            ans.push_back(o1 + r_vec * r1 / l);
        }
        else {
            ans.push_back(o1 - r_vec * r1 / l);
        }
        return ans;
    }

    if (((r1 + r2) * (r1 + r2) < l2) || (l2 < (r2 - r1) * (r2 - r1))) {
        return ans;
    }

    double a = (r1 * r1 + l2 - r2 * r2) / 2 / l;
    double g = sqrt(r1 * r1 - a * a);

    Vec2d h = o1 + r_vec * a / l;

    ans.push_back(h + r_vec(Vec2d(0, 1)) * g / l);
    ans.push_back(h + r_vec(Vec2d(0, -1)) * g / l);
}

Vec2d intersect_lines(double a1, double b1, double c1,
                      double a2, double b2, double c2) {
    if (a1 * b2 - a2 * b1 == 0) {
        return Vec2d(1e18, 1e18);
    }
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

bool on_segment(const Vec2d& p, const Vec2d& a, const Vec2d& b) {
    bool on_line = fabs((a - p) * (b - p)) < EPSILON;
    bool x_equals = fabs((b - a).x) == fabs((b - p).x) + fabs((p - a).x);
    bool y_equals = fabs((b - a).y) == fabs((b - p).y) + fabs((p - a).y);
    return on_line && x_equals && y_equals;
    //return (fabs((b - a).len() - (a - p).len() - (b - p).len()) < 1e-10);
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

typedef std::vector<Vec2d> polygon;

double calc_area(polygon& points) {
    points.push_back(points[0]);
    int n = (int) points.size();

    double area = 0;

    for (int i = 0; i < n - 1; ++i) {
        area += det2d(points[i], points[i + 1]);
    }
    return fabs(area) / 2;
}

bool check_convex(polygon& points) {
    points.push_back(points[0]);
    points.push_back(points[1]);
    points.push_back(points[2]);
    int n = (int) points.size();

    double a = det2d(points[0], points[1], points[2]);
    for (int i = 0; i < n - 4; ++i) {
        double b = det2d(points[i + 1], points[i + 2], points[i + 3]);
        bool ok = ((a > 0) && (b > 0)) || ((a < 0) && (b < 0));
        if (!ok) {
            return false;
        }
        a = b;
    }
    return true;
}

polygon build_convex_hull(polygon& points) {
    int n = (int) points.size();
    std::sort(points.begin(), points.end());

    polygon hull;
    int l = 0;
    for (int i = 0; i < n; ++i) {
        Vec2d new_point = points[i];
        while ((l > 1) && (det2d(hull[l - 2], hull[l - 1], new_point) <= 0)) {
            hull.pop_back();
            --l;
        }
        hull.push_back(new_point);
        ++l;
    }

    int rl = 1;
    for (int i = n - 2; i >= 0; --i) {
        Vec2d new_point = points[i];
        while ((rl > 1) && (det2d(hull[l - 2], hull[l - 1], new_point) <= 0)) {
            hull.pop_back();
            --rl;
            --l;
        }
        hull.push_back(new_point);
        ++rl;
        ++l;
    }

    while ((l > 2) &&
           ((det2d(hull[l - 1], hull[0], hull[1]) <= 0) ||
            (det2d(hull[l - 2], hull[l - 1], hull[0]) <= 0))) {
        hull.pop_back();
        --l;
    }

    return hull;
}

polygon operator - (const polygon& a) {
    polygon ans;
    for (int i = 0; i < polygon.size(); ++i) {
        ans.push_back(-a[i]);
    }
    return ans;
}


polygon operator + (const polygon& a, const polygon& b) {
    int n = (int) a.size();
    int m = (int) b.size();

    //find leftest in a
    int mina = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i].x < a[mina].x) {
            mina = i;
        }
    }

    //find leftest in b
    int minb = 0;
    for (int i = 1; i < m; ++i) {
        if (b[i].x < b[minb].x) {
            minb = i;
        }
    }

    int ita = mina;
    int itb = minb;

    polygon ans = {a[ita] + b[itb]};

    while (ita + 1 != mina || itb + 1 != minb) {
        int ita_next = (ita + 1) % n;
        int itb_next = (itb + 1) % m;
        if (det2d(a[ita_next] - a[ita], b[itb_next] - b[itb]) > 0) {
            ita = ita_next;
        }
        else {
            itb = itb_next;
        }
        ans.push_back(a[ita] + b[itb]);
    }

    return ans;
}

std::istream& operator >> (std::istream& in, polygon& p) {
    int n;
    Vec2d v;
    in >> n;
    for (int i = 0; i < n; ++i) {
        in >> v;
        p.push_back(v);
    }
    return in;
}

std::ostream& operator << (std::ostream& out, polygon& p) {
    out << p.size();
    for (int i = 0; i < p.size(); ++i) {
        out << p[i];
    }
    return out;
}

int main() {
    //freopen("gift.in", "r", stdin);
    //freopen("gift.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cout.precision(3);
    int n;
    polygon A, B;
    std::cin >> A >> B;

    A = build_convex_hull(A);
    B = build_convex_hull(B);

    polygon C = A + B;
    std::cout << C;
    return 0;
}