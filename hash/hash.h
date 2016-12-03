#pragma once

#include <vector>

#include "random.h"

class Hash {
public:
    virtual size_t operator()(int64_t number) const = 0;

    static const std::vector<uint64_t> PRIMES;
};

class UpdatableInt64Hash : public Hash {
public:
    UpdatableInt64Hash(Random& random_, uint64_t range_);
    void updateHash();

    size_t operator()(int64_t number) const override;

private:
    Random* random;
    uint64_t range;
    uint64_t coeff, base, mod;
};
