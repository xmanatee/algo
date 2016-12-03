#include "io.h"

template<class T>
void readVector(std::vector<T>& items, std::istream& in) {
    size_t size = 0;
    in >> size;
    items.resize(size);
    for (size_t i = 0; i < size; ++i) {
        in >> items[i];
    }
}

void writeBoolAnswers(const std::vector<bool>& answers, std::ostream& out) {
    for (bool answer : answers) {
        if (answer) {
            out << "Yes\n";
        } else {
            out << "No\n";
        }
    }
}
