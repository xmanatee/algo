#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "mytimsort.h"

void getInput(vector <int> & ans, int entropy) {
    int n = rand() % 10 + 1;
    if (entropy == 100) {
        for (int i = 0; i < n; ++i)
            ans.push_back(rand() % 10000);
    }
    else {
        for (int i = 0; i < n; ++i)
            ans.push_back(i);

        int swap_quantity = n * entropy / 100;
        for (int i = 0; i < swap_quantity; ++i) {
            int id1 = rand() % n;
            int id2 = rand() % n;
            swap(ans[id1], ans[id2]);
        }
    }
}

void outVector(vector <int> & arr) {
    cout << "[" << arr.size() << "] - ";
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << endl;
}


int main() {
    cout << fixed << setprecision(8) << endl;
    srand(time(NULL));
    const int TEST_QUATITY = 3;
    double efficiency = 0;
    int fails = 0;
    for (int i = 0; i < TEST_QUATITY; ++i) {
        cout << i << ")" << endl;
        vector <int> arr1;
        getInput(arr1, 30);
        vector <int> arr2(arr1);

        outVector(arr2);

        double start_time = clock();
        sort(arr2.begin(), arr2.end());
        double stdsort_time = clock() - start_time;
        cout << "Stdsort result : " << stdsort_time / CLOCKS_PER_SEC << "\n";

        outVector(arr2);

        start_time = clock();
        timsort(arr1);
        double timsort_time = clock() - start_time;
        cout << "Timsort result : " << timsort_time / CLOCKS_PER_SEC << "\n";

        outVector(arr1);
        for (int i = 0; i < arr1.size(); i++) {
            if (arr1[i] != arr2[i]) {
                ++fails;
                break;
            }
        }
        efficiency = efficiency + timsort_time / stdsort_time;
    }

    efficiency /= TEST_QUATITY;
    cout << "Efficiency : " << efficiency << "\n";
    cout << "Failed " << fails << " of " << TEST_QUATITY << "\n";

    return 0;
}
