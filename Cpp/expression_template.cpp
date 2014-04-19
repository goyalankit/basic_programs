#include <iostream>
#include <cstdint>

#include <vector>

using std::cout;
using std::endl;
using std::vector;


struct Identity {
    double operator()(double in) const { return in; }
};

template <typename LType, typename RType>
struct MulProxy {
    typename RefType<LType>::type left;
    typename RefType<RType>::type right;
    MulProxy(LType _l, RType _r) : left(_l), right(_r) {}
    double operator()(double in) const { return left(in) * right(in); }
};

MulProxy<Identity, Identity> operator*(Identity left, Identity right) {
    return MulProxy<Identity, Identity>(left, right);
}

template<typename L1, typename L2>
MulProxy<MulProxy<L1, L2>, Identity>
operator*(MulProxy<L1, L2> left, Identity right) {
    return MulProxy<MulProxy<L1, L2>, Identity>(left, right);
}

template<typename L1, typename L2, typename R1, typename R2>
MulProxy<MulProxy<L1, L2>, MulProxy<R1, R2>>
operator*(MulProxy<L1, L2> left, MulProxy<R1, R2> right) {
    return MulProxy<MulProxy<L1, L2>, MulProxy<R1, R2>>(left, right);
}

template <typename L, typename R>
MulProxy<L, R> operator*(L left, R right) {
    return MulProxy<L, R>(left, right);
}

template <typename Fun>
double integrate(Fun f, double start, double end, double incr) {
    double result = 0.0;
    for (double x = start; x < end; x += incr) {
        result += f(x) * incr;
    }
    return result;
}

template <typename T, typename R=vector<T>>
struct Valarray : public R {
    explicit Valarray(uint64_t sz) : R(sz) {}
};


template <typename T1, typename R1, typename T2, typename R2>
Valarray<T1, AddProxy<R1, R2>>
operartor + (const Valarray<T1, R1>& x, const Valarray<T2, R2>& y) {
    return Valarray<T1, AddProxy<R1, R2>>(x, y);
}

int main(void) {
    Identity i;
    auto fun = i * i;
    double x = integrate(fun, 0, 5, 0.001);
    cout << "the integral is: " << x << endl;
    cout << "the integral is: " << integrate(i * i * i, 0, 5, 0.001) << endl;
    cout << "the integral is: " << integrate(i * i * i * i, 0, 5, 0.001) << endl;
    
    Valarray<double> x(10);
    Valarray<double> y(10);
    cout << x + y;
    cout << x + y + x + getvector();
}


