#include "taylor.hpp"
#include <iostream>

int main() {

    using T = long double;
    std::cout << derive_inverse<T>(2, 10) << std::endl;
    T x(1.0);
    T h(0.2);
    std::cout << "x=" << x << " h=" << h << std::endl;
    long double real = static_cast<long double>(1.0)/(static_cast<long double>(x)+static_cast<long double>(h));
    long double approx = Taylor(derive_inverse<T>(x, 4), h);
    std::cout << "Real 1/x+h:" << real << " Taylor dev:" << approx << std::endl;
    std::cout << "Difference: " << real - static_cast<long double>(approx) << std::endl;

    // Binomial

    binomial<long> bin(16);
    std::cout << bin << std::endl;
    std::cout << bin(16, 1) << std::endl;
    auto f = derive_inverse<long double>(5.0L, 5);
    auto g = derive_inverse<long double>(3.0L, 5);
    std::cout << derive_product(f, g, 3) << std::endl;


    return 0;
}