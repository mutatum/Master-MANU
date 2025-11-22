#pragma once
#include "class_dynamic_vector.hpp"
#include "class_list.hpp"
#include <iostream>

template <typename T> const list<T> derive_inverse(T const &a, std::size_t n) {
  list<T> derivatives(n + 1, 1.0 / a);
  for (std::size_t ii = 1; ii < n + 1; ++ii) {
    derivatives(ii) = derivatives[ii - 1] * (-T(ii) / a);
  }
  return derivatives;
}

template <class T> const T Taylor(list<T> const &f, T const &h) {
  std::size_t N = f.number();
  T taylor_dev(f[N - 1]);

  for (std::size_t ii = N - 1; ii > 0;
       --ii) { // Horner's scheme for taylor expansion
    taylor_dev = f[ii - 1] + taylor_dev * (h / T(ii));
  }
  return taylor_dev;
}

template <typename T> class binomial : public list<dynamic_vector<T>> {
public:
  using list<dynamic_vector<T>>::operator();

  binomial(std::size_t n) : list<dynamic_vector<T>>(n + 1) {
    this->item_[0] = new dynamic_vector<T>(1, T(1.0));
    for (std::size_t ii = 1; ii < n + 1; ++ii) {
      this->item_[ii] = new dynamic_vector<T>{ii + 1, T(1.0)};
      for (std::size_t jj = 1; jj < ii; ++jj) {
        (*this)(ii)(jj) = (*this)[ii - 1][jj - 1] + (*this)[ii - 1][jj];
      }
    }
  }
  T operator()(std::size_t const& n, std::size_t const& k) { return (*this)(n)(k); }
};

template <typename T>
T derive_product(list<T> const &f, list<T> const &g, std::size_t order) {
  T result{0.0};
  std::cout << f.number() << " " << g.number() << " " << order << std::endl;
  assert(f.number() == g.number() && f.number()>=order);
  binomial<T> factors{order};
  for (std::size_t ii = 0; ii <= order; ++ii) {
    result += factors(order, ii) * f[ii] * g[order-ii];
  }
  return result;
}