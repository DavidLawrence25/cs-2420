#include <stdlib.h>

#include <memory>
#include <ostream>

#ifndef CS2420_NOBRAINERS_03COLLECTION_COLLECTION_H_
#define CS2420_NOBRAINERS_03COLLECTION_COLLECTION_H_

namespace rose {

// Represents a variable-sized list of elements in memory.
template <typename T>
class Collection {
 public:
  // Constructs an empty collection with the default capacity.
  Collection();
  // Constructs an empty collection with a set capacity.
  Collection(size_t capacity);
  // Constructs a deep copy of `other`.
  Collection(const Collection<T> &other);

  size_t capacity() const;
  size_t length() const;

  // Returns the element at index `i`.
  T ItemAt(int i) const;
  // Appends `item` to the collection.
  void Add(T item);
  // Removes the last element in the collection.
  void RemoveEnd();

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const Collection<_T> &collection);

 private:
  // Used to set `capacity_` if no capacity is given during construction.
  static const size_t kInitialCapacity = 8;
  // Represents how many elements could fit in the collection.
  size_t capacity_;
  // Represents how many elements are currently in the collection.
  size_t length_;
  std::unique_ptr<T[]> elements_;

  // Scales `capacity_` by a constant factor.
  void Expand();
};

}  // namespace rose

#include "collection.cc"

#endif  // CS2420_NOBRAINERS_03COLLECTION_COLLECTION_H_
