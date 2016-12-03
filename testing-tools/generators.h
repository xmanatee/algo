#pragma once

template<class T>
std::vector<T> generateRandomVector(size_t size = static_cast<size_t>(1e5),
                                    T range = 1e9,
                                    size_t seed = 0);

template<class T>
std::vector<T> generateConseqVector(size_t size = static_cast<size_t>(1e5),
                                    T start = 0);


