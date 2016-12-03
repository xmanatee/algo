#pragma once

#include <random>

class Random {
public:
    explicit Random(size_t seed);

    int64_t nextInt(int64_t left_bound = 0, int64_t right_bound = 1000);
private:
    std::mt19937 generator;
};
