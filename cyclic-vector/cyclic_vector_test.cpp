#include <iostream>
//#include <tuple>

#include "cyclic_vector.h"

int main() {

    CyclicVector<3, bool> v;

    v.resize(3, 4, 5);

    v.print();

    std::cout << "===" << std::endl;

    v.get(1).print();

    return 0;
}