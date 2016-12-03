#ifndef _FRACTION_H_
#define _FRACTION_H_

template <typename T>
class Fraction {
public:
    T p, q;
    Fraction(): p(0), q(1) { }
    Fraction(T _p): p(_p), q(1) { }
    Fraction(T _p, T _q): p(_p), q(_q) { }

    static T gcd(T a, T b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }
    void normalize() {
        T g = gcd(p, q);
        p /= g;
        q /= g;
    }


    Fraction operator - () const {
        return Fraction(-p, q);
    }

    Fraction operator + (const Fraction& b) {
        Fraction ans(p * b.q + b.p * q, q * b.q);
        ans.normalize();
        return ans;
    }

    Fraction operator - (const Fraction& b) {
        Fraction ans(p * b.q - b.p * q, q * b.q);
        ans.normalize();
        return ans;
    }

    Fraction operator * (T b) {
        Fraction ans(p * b, q);
        ans.normalize();
        return ans;
    }

    Fraction operator / (T b) {
        Fraction ans(p, q * b);
        ans.normalize();
        return ans;
    }

    Fraction operator / (Fraction b) {
        Fraction ans(p * b.q, q * b.p);
        ans.normalize();
        return ans;
    }

    Fraction operator * (const Fraction& b) {
        Fraction ans(p * b.p, q * b.q);
        ans.normalize();
        return ans;
    }

    bool operator < (const Fraction& b) const {
        return p * b.q < b.p * q;
    }

};


template <typename T>
std::istream& operator >> (std::istream& in, Fraction<T>& a) {
    in >> a.p >> a.q;
    return in;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Fraction<T>& a) {
    out << a.p << " / " << a.q;
    return out;
}

template <typename T>
Fraction<T> operator * (T b, const Fraction<T>& a) {
    Fraction<T> ans(a.p * b, a.q);
    ans.normalize();
    return ans;
}


#endif // _FRACTION_H_