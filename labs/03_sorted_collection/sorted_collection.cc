#include "../../no_brainers/03_collection/collection.h"
#include "sorted_collection.h"

namespace rose {

template <typename T>
SortedCollection<T>::SortedCollection() : Collection<T>() {}

template <typename T>
SortedCollection<T>::SortedCollection(size_t capacity)
    : Collection<T>(capacity) {}

template <typename T>
SortedCollection<T>::SortedCollection(const SortedCollection<T> &other)
    : Collection<T>(other) {}

template <typename T>
void SortedCollection<T>::Add(T item) {
  if (this->length_ == this->capacity_) this->Expand();
  this->elements_[this->length_++] = item;  // Post-increment is intentional.

  for (int i = static_cast<int>(this->length_) - 2; i >= 0; --i) {
    if (item >= this->elements_[i]) break;

    this->elements_[i + 1] = this->elements_[i];
    this->elements_[i] = item;
  }
}

template <typename T>
SortedCollection<T> &SortedCollection<T>::operator+=(const T &item) {
  Add(item);
  return *this;
}

template <typename T>
SortedCollection<T> &SortedCollection<T>::operator<<(const T &item) {
  Add(item);
  return *this;
}

}  // namespace rose
