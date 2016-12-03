#ifndef _VECND_H_
#define _VECND_H_

#include <vector>

typedef double T;


class VecND {
private:
    int n;
    std::vector<T> coord;
public:
    VecND(const std::vector<T>& _coord): coord(_coord) {}
    int size() const;

    friend VecND operator + (const VecND& a, const VecND& b);
    //friend void operator += (VecND& a, const VecND& b);
    friend VecND operator - (const VecND& a, const VecND& b);
    //friend void operator -= (VecND& a, const VecND& b);
    //friend T operator * (const VecND& a, const VecND& b);
    //friend ostream& operator << (ostream& out, const VecND& a);
    //friend istream& operator >> (istream& in, VecND& a);
};

int VecND::size() const {
    return n;
}

VecND operator + (const VecND& a, const VecND& b) {
#ifdef CHK_DIMENSIONS
    assert(a.size() == b.size())
#endif
    int n = a.n;
    std::vector<T> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = a.coord[i] + b.coord[i];
    }
    return VecND(c);
}

VecND operator - (const VecND& a, const VecND& b) {
#ifdef CHK_DIMENSIONS
    assert(a.size() == b.size())
#endif
    int n = a.n;
    std::vector<T> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = a.coord[i] - b.coord[i];
    }
    return VecND(c);
}

#endif // _VECND_H_
