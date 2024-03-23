#include "custom_libraries/collection.h"

#include <stdlib.h>

#include <memory>
#include <ostream>

namespace rose {

template <typename T>
Collection<T>::Collection() {
  elements_ = std::make_shared<T[]>(capacity_);
}

template <typename T>
Collection<T>::Collection(size_t capacity)
    : capacity_(capacity), elements_(std::make_shared<T[]>(capacity)) {}

template <typename T>
Collection<T>::Collection(const Collection<T> &other)
    : capacity_(other.capacity_),
      length_(other.length_),
      elements_(std::make_shared<T[]>(other.capacity_)) {
  for (size_t i = 0; i < length_; ++i) elements_[i] = other.elements_[i];
}

template <typename T>
Collection<T> &Collection<T>::operator=(const Collection<T> &other) {
  capacity_ = other.capacity_;
  length_ = other.length_;
  elements_ = std::make_shared<T[]>(other.capacity_);
  for (size_t i = 0; i < length_; ++i) elements_[i] = other.elements_[i];
  return *this;
}

template <typename T>
T Collection<T>::ItemAt(int i) const {
  return elements_[FixIndex(i)];
}

template <typename T>
const T &Collection<T>::operator[](int i) const {
  return elements_[FixIndex(i)];
}

template <typename T>
void Collection<T>::Add(T item) {
  if (length_ == capacity_) Expand();
  elements_[length_++] = item;  // Post-increment is intentional.
}

template <typename T>
void Collection<T>::Move(int i, int j) {
  i = FixIndex(i);
  j = FixIndex(j);
  T at_i = elements_[i];
  if (i > j) {
    for (int k = i; k > j; --k) elements_[k] = elements_[k - 1];
  } else if (i < j) {
    for (int k = i; k < j; ++k) elements_[k] = elements_[k + 1];
  }
  elements_[j] = at_i;
}

template <typename T>
void Collection<T>::RemoveEnd() {
  if (length_) --length_;
}

template <typename T>
void Collection<T>::Swap(int i, int j) {
  T value_at_i = ItemAt(i);
  i = FixIndex(i);
  j = FixIndex(j);
  elements_[i] = elements_[j];
  elements_[j] = value_at_i;
}

template <typename T>
void Collection<T>::Expand() {
  // A higher scaling factor results in fewer, but more expensive expansions.
  static const int kScaleFactor = 2;

  capacity_ *= kScaleFactor;
  // `elements_` must be copied to a new area in memory to accomodate for a
  // larger capacity.
  auto new_elements = std::make_shared<T[]>(capacity_);
  for (size_t i = 0; i < length_; ++i) new_elements[i] = elements_[i];
  elements_ = std::move(new_elements);
}

template <typename T>
int Collection<T>::FixIndex(int i) const {
  // Modular arithmetic in C++ gets weird when stuff is negative.
  auto len = static_cast<int>(length_);
  return abs(len + i - len * (i / len)) % len;
}

template <typename _T>
std::ostream &operator<<(std::ostream &out, const Collection<_T> &collection) {
  if (collection.length_ == 0) {
    out << "[]";
    return out;
  }

  out << '[';
  for (size_t i = 0; i < collection.length_ - 1; ++i) {
    out << collection.elements_[i] << ", ";
  }
  out << collection.ItemAt(-1) << ']';
  return out;
}

}  // namespace rose
