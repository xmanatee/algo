#include "cockoo_set.h"
#include "optional.h"
#include "hash.h"

template<class T, class UpdatableHash>
CuckooSet<T, UpdatableHash>::CuckooSet(size_t maxSize,
                                       size_t maxHash_,
                                       size_t updateSeed):
        maxHash(maxHash_) {
    currentSize = 0;
    capacity = static_cast<size_t> (maxSize * (1 + LOAD_EPSILON));
    random = new Random(updateSeed);
    tables.resize(2);
    for (size_t i = 0; i < 2; ++i) {
        tables[i].resize(capacity);
        hashes.push_back(std::move(UpdatableHash(*random, maxHash)));
    }
}

template<class T, class UpdatableHash>
CuckooSet<T, UpdatableHash>::~CuckooSet() {
    delete random;
}

template<class T, class UpdatableHash>
void CuckooSet<T, UpdatableHash>::Initialize(const std::vector<T>& keys) {
    for (const T& key : keys) {
        put(key);
    }
}

template<class T, class UpdatableHash>
bool CuckooSet<T, UpdatableHash>::Contains(const T& key) const {
    return (tables[0][id(key, 0)].equals(key)
            || tables[1][id(key, 1)].equals(key));
}

template<class T, class UpdatableHash>
void CuckooSet<T, UpdatableHash>::put(T key) {
    if (Contains(key)) {
        return;
    }
    size_t bounce = 0;
    bool foundCell = false;
    while (!foundCell) {
        size_t bucket = bounce % 2;
        size_t hash = id(key, bucket);
        if (!tables[bucket][hash]) {
            tables[bucket][hash] = key;
            foundCell = true;
        } else {
            std::swap(key, tables[bucket][hash].val());
            ++bounce;
        }

        if (!foundCell && bounce % MAX_BOUNCE == 0) {
            rehash();
        }
    }
    ++currentSize;
}

template<class T, class UpdatableHash>
std::vector<T> CuckooSet<T, UpdatableHash>::allKeys() const {
    std::vector<T> present;
    for (size_t i = 0; i < 2; ++i) {
        for (auto &item : tables[i]) {
            if (item) {
                present.push_back(item.get());
            }
        }
    }
    return present;
}

template<class T, class UpdatableHash>
void CuckooSet<T, UpdatableHash>::rehash() {
    std::vector<T> keys = allKeys();
    for (size_t i = 0; i < 2; ++i) {
        tables[i].clear();
        tables[i].resize(capacity);
        hashes[i].updateHash();
    }
    currentSize = 0;
    for (const T& key : keys) {
        put(key);
    }
    ++rehash_count;
}

template<class T, class UpdatableHash>
size_t CuckooSet<T, UpdatableHash>::getSize() const {
    return currentSize;
}

template<class T, class UpdatableHash>
size_t CuckooSet<T, UpdatableHash>::getCapacity() const {
    return capacity;
}

template<class T, class UpdatableHash>
size_t CuckooSet<T, UpdatableHash>::getRehashCount() const {
    return rehash_count;
}

template<class T, class UpdatableHash>
size_t CuckooSet<T, UpdatableHash>::id(const T& number, size_t table_num) const {
    return hashes[table_num](number) % capacity;
}
