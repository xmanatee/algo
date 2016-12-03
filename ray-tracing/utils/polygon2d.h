#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include <algorithm>
#include <cstdlib>

#include "vec2d.h"

typedef std::vector<Vec2d> polygon;

double oriented_area(polygon& points) {
    points.push_back(points[0]);
    int n = (int) points.size();
    double area = 0;

    for (int i = 0; i < n - 1; ++i) {
        area += det2d(points[i], points[i + 1]);
    }
    return area / 2;
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
    for (int i = 0; i < a.size(); ++i) {
        ans.push_back(-a[i]);
    }
    return ans;
}

// Takes as input 2 convex polegons oriented clockwise
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

    polygon sum = {a[ita] + b[itb]};
    int k = n + m;

    while (sum.size() < k) {//(ita + 1) % n != mina || (itb + 1) % m != minb) {
        int ita_next = (ita + 1) % n;
        int itb_next = (itb + 1) % m;
        if (det2d(a[ita_next] - a[ita], b[itb_next] - b[itb]) < 0) {
            ita = ita_next;
        }
        else {
            itb = itb_next;
        }
        sum.push_back(a[ita] + b[itb]);
    }

    return sum;
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
    out << p.size() << std::endl;
    for (int i = 0; i < p.size(); ++i) {
        out << p[i] << std::endl;
    }
    return out;
}

#endif // _POLYGON_H_