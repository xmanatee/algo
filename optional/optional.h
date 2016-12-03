#pragma once

template<class T>
class Optional {
public:
    Optional();
    explicit Optional(const T& _value);
    T get() const;
    bool equals(const T& other) const;
    operator bool() const;

    void operator=(const T& other);
    T& val();
private:
    bool present;
    T value;
};
