#include "no_brainers/03_collection/collection.h"

#include <iostream>

namespace rose {

template <typename T>
Collection<T>::Collection() {
  capacity_ = kInitialCapacity;
  length_ = 0;
  elements_ = std::make_shared<T[]>(capacity_);
}

template <typename T>
Collection<T>::Collection(size_t capacity) {
  capacity_ = capacity;
  length_ = 0;
  elements_ = std::make_shared<T[]>(capacity_);
}

template <typename T>
Collection<T>::Collection(const Collection<T> &other) {
  capacity_ = other.capacity_;
  length_ = other.length_;
  elements_ = std::make_shared<T[]>(capacity_);
  for (size_t i = 0; i < length_; ++i) elements_[i] = other.elements_[i];
}

template <typename T>
size_t Collection<T>::capacity() const {
  return capacity_;
}

template <typename T>
size_t Collection<T>::length() const {
  return length_;
}

template <typename T>
T Collection<T>::ItemAt(int i) const {
  // Modular arithmetic in C++ gets weird when stuff is negative.
  int len = static_cast<int>(length_);
  return elements_[abs(len + i - len * (i / len)) % len];
}

template <typename T>
void Collection<T>::Add(T item) {
  if (length_ == capacity_) Expand();
  elements_[length_++] = item;  // Post-increment is intentional.
}

template <typename T>
void Collection<T>::RemoveEnd() {
  if (length_ != 0) --length_;
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
