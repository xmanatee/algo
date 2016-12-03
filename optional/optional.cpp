#include "optional.h"

template<class T>
Optional<T>::Optional(): present(false), value() {}

template<class T>
Optional<T>::Optional(const T& _value): present(true), value(_value) {}

template<class T>
T Optional<T>::get() const {
    return value;
}

template<class T>
T& Optional<T>::val() {
    return value;
}

template<class T>
bool Optional<T>::equals(const T& other) const {
    return present && value == other;
}

template<class T>
void Optional<T>::operator=(const T& other) {
    present = true;
    value = other;
}

template<class T>
Optional<T>::operator bool() const {
    return present;
}
