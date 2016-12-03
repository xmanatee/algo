#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

#include "kheap.cpp"

int main() {
    freopen("test.in", "r", stdin);
    int n;
    cin >> n;
    Heapka < int > KHeap(2);
    char s[20];
    int a;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s[0] == 'A') {
            cin >> a;
            heapka.add(a);
        }
        if (s[0] == 'G') {
            cout << heapka.get_min() << endl;
        }
        if (s[0] == 'D') {
            heapka.drop_min();
        }
    }
}
