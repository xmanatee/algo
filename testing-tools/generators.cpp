#include <vector>

#include "generators.h"

template<class T>
std::vector<T> generateRandomVector(size_t size, T range, size_t seed) {
    std::vector<T> items;
    if (seed == 0) {
        seed = static_cast<size_t>(std::time(nullptr));
    }
    Random random(seed);
    items.resize(size);
    for (size_t i = 0; i < size; ++i) {
        items[i] = static_cast<T>(random.nextInt(0, 2 * range) - range);
    }
    return items;
}

template<class T>
std::vector<T> generateConseqVector(size_t size, T start) {
    std::vector<T> items;
    items.resize(size);
    for (size_t i = 0; i < size; ++i) {
        items[i] = start + i;
    }
    return items;
}
