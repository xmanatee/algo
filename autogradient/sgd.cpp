#include <cstdio>
#include <iostream>

#include "vec2d.h"
#include "line.h"
#include "polygon.h"
#include "autograd.h"
#include "costs.h"

Line lineGrad(const Line& l, const std::vector<Vec2d>& x, const std::vector<bool>& y) {
    double a = l.a;
    double b = l.b;
    double c = l.c;

    TAutoGradient<double> va(a, 1), vb(b, 1), vc(c, 1);
    TAutoGradient<double> ca(a), cb(b), cc(c);
    double da = totalCost(va, cb, cc, x, y).getDerivative();
    double db = totalCost(ca, vb, cc, x, y).getDerivative();
    double dc = totalCost(ca, cb, vc, x, y).getDerivative();

    return Line(da, db, dc);
}

bool splits(const Line& line, const std::vector<Vec2d>& x, const std::vector<bool>& y) {
    static const double margin = 0.2e-6;
    for (size_t i = 0; i < x.size(); ++i) {
        if (((line.signedDist(x[i]) >= -margin) && y[i]) || ((line.signedDist(x[i]) <= margin) && !y[i])) {
            return false;
        }
    }
    return true;
}

int main() {
#ifndef RUNCPP_DEBUG
    freopen("rest.in", "r", stdin);
    freopen("rest.out", "w", stdout);
#endif
    std::ios_base::sync_with_stdio(false);
    std::cout.precision(20);
    std::cout.setf(std::ios::fixed);

    std::vector<Vec2d> x;
    std::vector<bool> y;
    size_t n;
    std::cin >> n;
    Vec2d m1;
    for (size_t i = 0; i < n; ++i) {
        Vec2d v;
        std::cin >> v;
        m1 = m1 + v;
        x.push_back(v);
        y.push_back(true);
    }
    m1 = m1 / n;

    std::cin >> n;
    Vec2d m2;
    for (size_t i = 0; i < n; ++i) {
        Vec2d v;
        std::cin >> v;
        m2 = m2 + v;
        x.push_back(v);
        y.push_back(false);
    }
    m2 = m2 / n;

    Vec2d m3 = (m1 + m2) / 2;
    Vec2d m4 = m3 + Vec2d(0, 1)(m2 - m1);
    Line l(m3, m4);

    double lcost = 1e18;
    double rcost = totalCost(l.a, l.b, l.c, x, y);
    std::cerr << "init line : " << l << std::endl;
    std::cerr << "init loss : " << rcost << std::endl;

    double alpha_start = 1e0;
    double alpha_min = 1e-0;
    double nsteps = 1000;
    int iter = 1;

    std::vector<double> lossHistory;
    lossHistory.push_back(rcost);
    while (!splits(l, x, y)) {
        double alpha = alpha_min  + alpha_start * gate(nsteps - iter) / nsteps;
        l = l - alpha * lineGrad(l, x, y);
#ifdef RUNCPP_DEBUG
        lcost = rcost;
        rcost = totalCost(l.a, l.b, l.c, x, y);
        lossHistory.push_back(rcost);
        std::cerr << iter++ << ". loss : " << rcost << "; " << l << std::endl;
        std::cerr << "\\X : (" << l.intersectX() << ")" << std::endl;
        std::cerr << "\\Y : (" << l.intersectY() << ")" << std::endl;
        std::cerr << lineGrad(l, x, y).norm() << std::endl;
#endif
        if (iter > 100) break;
    }

    l = l / l.len();
    std::cout << l.a << " " << l.b << " " << l.c << std::endl;

#ifdef RUNCPP_DEBUG
    std::cerr << "\\X : " << l.intersectX() << std::endl;
    std::cerr << "\\Y : " << l.intersectY() << std::endl;
#endif

    return 0;
}