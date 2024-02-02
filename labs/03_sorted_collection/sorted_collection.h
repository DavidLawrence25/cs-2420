#include <stdlib.h>

#include "no_brainers/03_collection/collection.h"

#ifndef CS2420_LABS_03SORTEDCOLLECTION_SORTEDCOLLECTION_H_
#define CS2420_LABS_03SORTEDCOLLECTION_SORTEDCOLLECTION_H_

namespace rose {

template <typename T>
class SortedCollection : public Collection<T> {
 public:
  SortedCollection();
  SortedCollection(size_t capacity);
  SortedCollection(const SortedCollection<T> &other);

  void Add(T item) override;
  SortedCollection &operator+=(const T &item);
  SortedCollection &operator<<(const T &item);
};

}  // namespace rose

#include "sorted_collection.cc"

#endif  // CS2420_LABS_03SORTEDCOLLECTION_SORTEDCOLLECTION_H_
