#include <iostream>

#include "fraction.h"
#include "segmenttree.h"

using namespace std;

int main() {

    Fraction<int> a, b;

    cin >> a >> b;
    cout << a + b << endl;
    cout << a * b << endl;
    cout << a / b << endl;


    return 0;
}