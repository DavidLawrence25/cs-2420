#include <stdlib.h>

#include "custom_libraries/collection.h"

#ifndef CS2420_LABS_03SORTEDCOLLECTION_SORTEDCOLLECTION_H_
#define CS2420_LABS_03SORTEDCOLLECTION_SORTEDCOLLECTION_H_

namespace rose {

template <typename T>
class SortedCollection : public Collection<T> {
 public:
  void Add(T item) override;
  SortedCollection &operator+=(const T &item);
  SortedCollection &operator<<(const T &item);
};

}  // namespace rose

#include "labs/03_sorted_collection/sorted_collection.cc"

#endif  // CS2420_LABS_03SORTEDCOLLECTION_SORTEDCOLLECTION_H_
