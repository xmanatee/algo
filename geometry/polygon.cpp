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

bool check_convex(poly& points) {
    points.push_back(points[0]);
    points.push_back(points[1]);
    points.push_back(points[2]);
    points.push_back(points[3]);
    int n = points.size();

    for (int i = 0; i < n - 4; ++i) {
        point new_point = points[i];
        bool a = prod(points[i], points[i + 1], points[i + 2]) > 0;
        bool b = prod(points[i + 1], points[i + 2], points[i + 3]) > 0;
        if (a ^ b) {
            return false;
        }
    }
    return true;
}

int n;
poly points;

int main() {
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }
    if (check_convex(points)) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
    return 0;
}