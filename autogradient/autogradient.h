#ifndef _AUTOGRAD_H_
#define _AUTOGRAD_H_

#include <cmath>
#include <ostream>

template <typename T>
class TAutoGradient {
private:
    T val, deriv;
public:
    TAutoGradient(const T &_val, const T &_deriv) : val(_val), deriv(_deriv) {}
    TAutoGradient(const T &c): val(c), deriv(0) {}
    TAutoGradient(void): val(0), deriv(0) {}

    static TAutoGradient IndependentVariable(const T &x) {
        return TAutoGradient(x, 1);
    }

    static TAutoGradient Constant(const T &x) {
        return TAutoGradient(x, 0);
    }


    T getValue() const {
        return val;
    }
    T getDerivative() const {
        return deriv;
    }

    TAutoGradient operator + (const TAutoGradient& f) const {
        return TAutoGradient(val + f.val, deriv + f.deriv);
    }

    TAutoGradient operator + (const T& value) const {
        return TAutoGradient(val + value, deriv);
    }

    TAutoGradient operator - (const TAutoGradient& f) const {
        return TAutoGradient(val - f.val, deriv - f.deriv);
    }

    TAutoGradient operator - (const T& value) const {
        return TAutoGradient(val - value, deriv);
    }

    TAutoGradient operator * (const TAutoGradient& f) const {
        return TAutoGradient(val * f.val, deriv * f.val + val * f.deriv);
    }

    TAutoGradient operator * (const T& value) const {
        return TAutoGradient(val * value, deriv * value);
    }

    TAutoGradient operator / (const TAutoGradient& f) const {
        return TAutoGradient(val / f.val, (deriv * f.val - val * f.deriv) / f.val / f.val);
    }

    friend TAutoGradient cos(const TAutoGradient<T>& f) {
        return TAutoGradient(cos(f.val), -sin(f.val)*f.deriv);
    };

    friend TAutoGradient sin(const TAutoGradient& f) {
        return TAutoGradient(sin(f.val), cos(f.val)*f.deriv);
    };

    friend TAutoGradient exp(const TAutoGradient& f) {
        return TAutoGradient(exp(f.val), exp(f.val)*f.deriv);
    };

    friend TAutoGradient log(const TAutoGradient& f) {
        return TAutoGradient(log(f.val), f.deriv / f.val);
    };

    friend TAutoGradient pow(const TAutoGradient& f, double k) {
        return TAutoGradient(pow(f.val, k), k * pow(f.val, k - 1) * f.deriv);
    };

    friend TAutoGradient sqrt(const TAutoGradient& f) {
        return TAutoGradient(sqrt(f.val), f.deriv / 2 / sqrt(f.val));
    }

    friend TAutoGradient<T> gate(const TAutoGradient<T>& f) {
        if (f.getValue() > 0) return TAutoGradient<T>(f.getValue(), f.getDerivative());
        else return TAutoGradient<T>(0, 0);
    }

    friend TAutoGradient<T> sqr(const TAutoGradient<T>& f) {
        return TAutoGradient<T>(f.getValue() * f.getValue(), 2 * f.getValue() * f.getDerivative());
    }
};

template <typename T>
std::ostream& operator << (std::ostream& out, const TAutoGradient<T>& a) {
    out << "{" << a.getValue() << "/" << a.getDerivative() << "}";
    return out;
}

template <typename T>
TAutoGradient<T> operator - (const TAutoGradient<T>& f) {
    return TAutoGradient<T>(-f.getValue(), -f.getDerivative());
}

#endif // _AUTOGRAD_H_
