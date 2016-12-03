#include <chrono>

#include "hash.h"
#include "cuckoo_set.h"

void testCuckooSetSmall();

void testCuckooSetWithTime(size_t seed = 0);


void testCuckooSetSmall() {
    CuckooSet<int64_t, UpdatableInt64Hash> set(4, 3000);

    set.put(1013);
    set.put(113);
    set.put(2013);
    set.put(13);


    assert(set.Contains(1013));
    assert(set.Contains(113));
    assert(set.Contains(2013));
    assert(set.Contains(13));
}

void testCuckooSetWithTime(size_t seed) {
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::duration<float> fsec;

    typedef int64_t Integer;

    size_t size = static_cast<size_t>(1e5);
    size_t range = static_cast<size_t>(1e9);

    CuckooSet<Integer, UpdatableInt64Hash> set(size, range);
    std::vector<Integer> numbers = generateRandomVector<Integer>(2 * size, range, seed);
    std::sort(numbers.begin(), numbers.end());

    int64_t sum = 0;
    for (int64_t number : numbers) {
        sum += number;
    }
    std::cerr << "Generated " << numbers.size() << " numbers with sum " << sum << std::endl;

    auto start_time = Time::now();
    for (size_t i = 0; i < size; ++i) {
        set.put(numbers[i]);
    }
    auto finish_time = Time::now();
    fsec period = finish_time - start_time;

    std::cerr << "Time: " << period.count() << "s" << std::endl;
    std::cerr << "Rehash Count: " << set.getRehashCount() << std::endl;
    assert(period.count() < 1);

    for (size_t i = 0; i < size; ++i) {
        assert(set.Contains(numbers[i]));
    }

    size_t id = size;
    while (numbers[id - 1] == numbers[id]) {
        ++id;
    }

    for (; id < numbers.size(); ++id) {
        assert(!set.Contains(numbers[id]));
    }
}
