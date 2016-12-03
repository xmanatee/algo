#pragma once

#include <vector>

int lcs(const std::vector<int>& first, const std::vector<int>& second) {
    std::vector<std::vector<int>> matrix(first.size() + 1);
    for (auto& vector : matrix) {
        vector.resize(second.size() + 1);
    }

    for (size_t i = 1; i < matrix.size(); ++i) {
        for (size_t j = 1; j < matrix[0].size(); ++j) {
            if (first[i - 1] == second[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            } else {
                matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }
    return matrix[first.size()][second.size()];
}
