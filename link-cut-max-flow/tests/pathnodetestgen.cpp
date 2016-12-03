#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int seed = atoi(argv[3]);
    std::srand(seed);

    std::cout << n << " " << m << "\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::rand() % 1000 << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < m; ++i) {
        int q = 1 + std::rand() % 2;
        int a = 1 + std::rand() % n;
        int b = 1 + std::rand() % n;
        if (a > b) {
            std::swap(a, b);
        }
        std::cout << q << " " << a << " " << b << "\n";
    }
}
