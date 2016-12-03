#include<iostream>

using namespace std;

template<int N>
struct Fib {
    static const int val = Fib<N-1>::val + Fib<N-2>::val;
};

template<>
struct Fib<0> {
    static const int val = 1;
};

template<>
struct Fib<1> {
    static const int val = 1;
};

int main() {
    cout << Fib<4>::val << endl;
    return 0;
}
