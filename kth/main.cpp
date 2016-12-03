#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

#include "TTopElements.h"

int main() {
    n = 100000;
    randomize(time(NULL));

    TTopElements t1(k, HEAP_TYPE);
    TTopElements t2(k, KTHM_TYPE);

    for (int i = 0; i < n; i++) {
        a = rand();
        t1.Add(a);
        t2.Add(a);
    }

    freopen("h1.out", "w", stdout);
    cout << n << endl;
    t1.GetCurrentTop(cout);

    freopen("h2.out", "w", stdout);
    cout << n << endl;
    t2.GetCurrentTop(cout);

    return 0;
}
