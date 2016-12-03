#include "hash.h"

UpdatableInt64Hash::UpdatableInt64Hash(Random& random_, uint64_t range_): random(&random_),
                                                                          range(range_) {
    mod = *std::lower_bound(PRIMES.begin(), PRIMES.end(), 2 * range);
    updateHash();
}

void UpdatableInt64Hash::updateHash() {
    coeff = random->nextInt(1, mod - 1);
    base = random->nextInt(0, mod - 1);
}

size_t UpdatableInt64Hash::operator()(int64_t number) const {
    number += range;
    uint64_t hash = (coeff * number + base) % mod;
    return static_cast<size_t>(hash);
}

const std::vector<uint64_t> Hash::PRIMES = {
        17,
        257,
        1297,
        65537,
        160001,
        331777,
        614657,
        1336337,
        4477457,
        5308417,
        8503057,
        9834497,
        29986577,
        40960001,
        45212177,
        59969537,
        65610001,
        126247697,
        193877777,
        303595777,
        384160001,
        406586897,
        562448657,
        655360001,
        723394817,
        916636177,
        1049760001,
        1416468497,
        1536953617,
        1731891457,
        1944810001,
        2342560001,
        2702336257,
        3208542737,
        3429742097,
        3782742017,
        4162314257,
        5006411537,
        5473632257,
        5802782977,
        5972816657,
        6879707137,
        7676563457,
        9475854337,
        10485760001,
        11574317057,
        12444741137,
        13363360001,
        15352201217,
        17555190017,
        19565295377,
        29376588817,
        34188010001,
        36136489217
};
