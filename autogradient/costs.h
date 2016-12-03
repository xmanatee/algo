#ifndef _COSTS_H_
#define _COSTS_H_

template<typename T>
T sigmoid(const T& x) {
    return T(1) / (exp(-x) + T(1));
}

template<typename T>
T naive_cost(const T& a, const T& b, const T& c, const Vec2d& v, bool y) {
    T dist = (a * v.x + b * v.y + c) / sqrt(a * a + b * b);
    if (y) return exp(dist);
    else return exp(-dist);
}

template<typename T>
T naive_svm_cost(const T& a, const T& b, const T& c, const Vec2d& v, bool y) {
    T dist = (a * v.x + b * v.y + c) / sqrt(a * a + b * b);
    if (y) return gate(dist);
    else return gate(-dist);
}

template<typename T>
T svm_cost(const T& a, const T& b, const T& c, const Vec2d& v, bool y) {
    static const double margin = 1e-6;
    T dist = (a * v.x + b * v.y + c) / sqrt(a * a + b * b);
    if (y) return gate(dist + margin);
    else return gate(-dist + margin);
}

template<typename T>
T logistic_regression_cost(const T& a, const T& b, const T& c, const Vec2d& v, bool y) {
    T dist = (a * v.x + b * v.y + c) / sqrt(a * a + b * b);
    T activation = sigmoid(dist);
    if (y) return -log(activation);
    else return -log(T(1) - activation);
}

template<typename T>
T totalCost(const T& a, const T& b, const T& c, const std::vector<Vec2d>& x, const std::vector<bool>& y) {
    int n = (int) x.size();
    T tcost(0);
    for (int i = 0; i < n; ++i) {
        //T new_cost = svm_cost(a, b, c, x[i], y[i]);
        T new_cost = logistic_regression_cost(a, b, c, x[i], y[i]);
        tcost = tcost + new_cost;
    }
    tcost = tcost;// / x.size();// + T(0.1) * sqr(a * a + b * b - 1);
    return tcost;
}

#endif //_COSTS_H_