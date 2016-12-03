#include "random.h"

Random::Random(size_t seed): generator(seed) {}

int64_t Random::nextInt(int64_t left_bound, int64_t right_bound) {
    std::uniform_int_distribution<int64_t> distribution(left_bound, right_bound);
    int64_t randomNumber = distribution(generator);
    return randomNumber;
}
