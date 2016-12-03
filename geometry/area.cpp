#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long big;
typedef pair<big, big> point;
typedef vector<point> poly;

big prod(point &a, point &b, point &c) {
    return -(a.first - b.first) * (c.second - b.second)
           +(a.second - b.second) * (c.first - b.first);
}

double calc_area(poly& points) {
    points.push_back(points[0]);
    int n = points.size();

    double area = 0;

    point o(0, 0);
    for (int i = 0; i < n - 1; ++i) {
        area += prod(points[i], o, points[i + 1]);
    }
    return fabs(area) / 2;
}

int n;
poly points;

int main() {
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }

    cout << calc_area(points) << "\n";
    //printf("%.8f\n", calc_area(points));
    return 0;
}