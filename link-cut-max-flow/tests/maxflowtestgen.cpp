#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int seed = atoi(argv[3]);

    std::cout << n << " " << m << "\n";

    std::srand(seed);
    for (int i = 0; i < m; ++i) {
        std::cout << 1 + std::rand() % n << " " << 1 + std::rand() % n << " " << 1 + std::rand() % (int)(1e9) << "\n";
    }
}
