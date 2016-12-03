#pragma once

#include <vector>
#include <algorithm>

std::vector<size_t> buildMap(std::vector<size_t>& vector) {
    std::vector<size_t> unique(vector.begin(), vector.end());
    std::sort(unique.begin(), unique.end());
    std::unique(unique.begin(), unique.end());
    return unique;
}

size_t to(std::vector<size_t>& map, size_t number) {
    auto it = std::lower_bound(map.begin(), map.end(), number);
    return it - map.begin();
}

size_t from(std::vector<size_t>& map, size_t number) {
    return map[number];
}

