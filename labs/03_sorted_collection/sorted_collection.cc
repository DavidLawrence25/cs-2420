#include "labs/03_sorted_collection/sorted_collection.h"

#include <stdlib.h>

#include "custom_libraries/collection.h"

namespace rose {

template <typename T>
void SortedCollection<T>::Add(T item) {
  Collection<T>::Add(item);

  for (int i = static_cast<int>(Collection<T>::length()) - 2; i >= 0; --i) {
    if (item >= (*this)[i]) break;
    Collection<T>::Swap(i, i + 1);
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
