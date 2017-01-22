#pragma once

#include <ostream>
#include <vector>
#include <cstdarg>

template <int, class>
class CyclicVector;

template <class T>
class CyclicVector<1, T> {
private:
    std::vector<T> data;
public:

    template <class ... Args>
    void resize(size_t size, Args ... other) {
        data.resize(size);
    }

    template <class ... Args>
    T& get(int i,  Args ... other) {
        i = (i + data.size()) % data.size();
        return data[i];
    }

    void print(std::ostream& out = std::cout) {
        for (T item : data) {
            out << item << " ";
        }
    }
};

template <int N, class T>
class CyclicVector {
private:
    std::vector<CyclicVector<N-1, T>> data;
public:

    template <class ... Args>
    void resize(size_t size, Args ... other) {
        data.resize(size);
        for (auto& row : data) {
            row.resize(other...);
        }
    }

    template <class ... Args>
    T& get(int i, Args ... other) {

        i = (i + data.size()) % data.size();
        return data[i].get(other...);
    }

    template <class ... Args>
    CyclicVector<N-1, T>& get(int i) {

        i = (i + data.size()) % data.size();
        return data[i];
    }

    void print(std::ostream& out = std::cout) {
        for (auto& row : data) {
            row.print(out);
            out << std::endl;
        }
    }
};
