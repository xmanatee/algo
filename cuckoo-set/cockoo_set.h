#pragma once

#include <vector>

#include "random.h"
#include "optional.h"

template<class T, class UpdatableHash>
class CuckooSet {
public:
    CuckooSet(size_t maxSize,
              size_t maxHash_ = 1e9,
              size_t updateSeed = 1234);

    ~CuckooSet();

    void Initialize(const std::vector<T>& items);
    void put(T key);

    bool Contains(const T& key) const;

    size_t getSize() const;
    size_t getCapacity() const;
    size_t getRehashCount() const;

    std::vector<T> allKeys() const;

    size_t id(const T& item, size_t table_num) const;

private:
    void rehash();

    Random* random;
    size_t maxHash;
    std::vector<std::vector<Optional<T>>> tables;
    std::vector<UpdatableHash> hashes;
    size_t rehash_count = 0;
    size_t currentSize = 0;
    size_t capacity;
    static constexpr size_t MAX_BOUNCE = 100;
    static constexpr double LOAD_EPSILON = 0.1;
};
