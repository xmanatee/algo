#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
    int l = atoi(argv[1]);
    int seed = atoi(argv[2]);

    srand(seed);

    for (int i = 0; i < l; ++i) {
        cout << static_cast<char>(rand() % ('x' - 'a') + 'a');
    }
    cout << "\n";

    return 0;
}