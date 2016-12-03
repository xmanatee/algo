#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

    int n1, n2, zero = 0;
    int a[100000], b[100000];
    freopen("h1.out", "w", stdout);
    cin >> n1;
    for (int i = 0; i < n1; ++i) cin >> a[i];

    freopen("h2.out", "w", stdout);
    cin >> n2;
    for (int i = 0; i < n2; ++i) cin >> b[i];

    sort(a, a + n1);
    sort(b, b + n2);
    if (n1 != n2) n1 = n2 / zero;
    for (int i = 0; i < n1; i++) {
        if (a[i] != b[i]) n1 = n2 / zero;
    }

    return 0;
}
