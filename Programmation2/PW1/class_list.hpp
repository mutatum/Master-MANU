#pragma once
#include <cstddef>
#include <iostream>

template <typename T> class list {
protected:
  std::size_t number_;
  T **item_;

public:
  // Constructors
  list(std::size_t number = 0): number_(number), item_(number_ ? new T*[number_]: nullptr) {};
  list(std::size_t number, T value);
  list(const list &o);
  list(list &&o) noexcept;
  ~list();
  // Operator Overloading
  list &operator=(const list &source);
  list &operator=(list &&o) noexcept;
  T &operator()(std::size_t i);
  const T &operator[](std::size_t i) const;

  template <typename S>
  friend std::ostream &operator<<(std::ostream &os, const list<S> &lst);
  // Methods
  std::size_t number() const { return number_; }
  T *item(std::size_t i) { return item_[i]; }
  T *const item(std::size_t i) const { return item_[i]; }
};

// Constructors
template<typename T>
list<T>::list(std::size_t number, T value)
    : number_(number), item_(number ? new T *[number] : nullptr) {
  for (std::size_t ii = 0; ii < number_; ++ii) {
    item_[ii] = new T(value);
  }
}

template<typename T>
list<T>::list(const list &o)
    : number_(o.number_), item_(o.number_ ? new T *[o.number_] : nullptr) {
  for (std::size_t ii = 0; ii < number_; ++ii) {
    item_[ii] = new T(*o.item_[ii]);
  }
}

template<typename T>
list<T>::list(list &&o) noexcept : number_(o.number_), item_(o.item_) {
  o.number_ = 0;
  o.item_ = nullptr;
}

template<typename T>
list<T>::~list() {
  if (item_) {
    for (std::size_t ii = 0; ii < number_; ++ii)
      delete item_[ii];
    delete[] item_;
  }
}

template<typename T>
list<T> &list<T>::operator=(const list &source) {
  if (this != &source) {
    for (std::size_t ii = 0; ii < number_; ++ii) {
      delete item_[ii];
    }
    delete[] item_;
    number_ = source.number_;
    item_ = number_ ? new T *[number_] : nullptr;
    for (std::size_t ii = 0; ii < number_; ++ii) {
      item_[ii] = new T(source[ii]);
    }
  }
  return *this;
}

template<typename T>
list<T> &list<T>::operator=(list &&o) noexcept {
  if (this != &o) {
    for (std::size_t ii = 0; ii < number_; ++ii) {
      delete item_[ii];
    }
    delete[] item_;
    number_ = o.number_;
    item_ = o.item_;
    o.number_ = 0;
    o.item_ = nullptr;
  }
  return *this;
}

template<typename T>
T &list<T>::operator()(std::size_t i) { return *item_[i]; }

template<typename T>
const T &list<T>::operator[](std::size_t i) const { return *item_[i]; }

template <typename S>
std::ostream &operator<<(std::ostream &os, const list<S> &lst) {
  os << '{';
  if (lst.number_ != 0) {
    for (std::size_t ii = 0; ii < lst.number_ - 1; ++ii)
      os << *lst.item_[ii] << ", ";
    os << *lst.item_[lst.number_ - 1];
  }
  os << '}' << std::endl;
  return os;
}