#include <iostream>
#include <cassert>

#include "futex.h"
#include "incrementer.h"

using namespace std;

typedef long long number;

int main() {
    number a = 1e7, b = 10;
    futex xutex;
    mutex xutex2;

    for (number b : {1, 2, 3, 4, 5, 8, 16, 32}) {
        std::cout << "nThreads : " << b << std::endl;
        number n = 0;
        auto start = std::chrono::system_clock::now();
        Incrementer<number, futex>::setup(a, b);
        if (a != Incrementer<number, futex>::parallel(n, xutex)) {
            std::cerr << "LOL" << std::endl;
        }
        auto end = std::chrono::system_clock::now();
        std::cout << "Futex result: " << std::chrono::duration<double>(end - start).count() << std::endl;

        n = 0;
        start = std::chrono::system_clock::now();
        Incrementer<number, mutex>::setup(a, b);
        if (a != Incrementer<number, mutex>::parallel(n, xutex2)) {
            std::cerr << "LOL" << std::endl;
        }
        end = std::chrono::system_clock::now();
        std::cout << "Mutex result: " << std::chrono::duration<double>(end - start).count() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}