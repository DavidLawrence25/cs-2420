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
  explicit Collection(size_t capacity);
  // Constructs a deep copy of `other`.
  Collection(const Collection<T> &other);
  Collection<T> &operator=(const Collection<T> &other);
  virtual ~Collection() = default;

  size_t capacity() const { return capacity_; }
  size_t length() const { return length_; }

  // Returns the element at index `i`.
  T ItemAt(int i) const;
  const T &operator[](int i) const;
  // Appends `item` to the collection.
  virtual void Add(T item);
  // Moves the element at index `i` to index `j`.
  virtual void Move(int i, int j);
  // Removes the last element in the collection.
  void RemoveEnd();
  // Swaps the values of the elements at indices `i` and `j`.
  void Swap(int i, int j);

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const Collection<_T> &collection);

 protected:
  // Scales `capacity_` by a constant factor.
  void Expand();
  void IncrementLength() { ++length_; }
  // Frick around with the index so it's valid.
  int FixIndex(int i) const;

 private:
  // Used to set `capacity_` if no capacity is given during construction.
  static const size_t kInitialCapacity = 8;
  // Represents how many elements could fit in the collection.
  size_t capacity_ = kInitialCapacity;
  // Represents how many elements are currently in the collection.
  size_t length_ = 0;
  std::shared_ptr<T[]> elements_;
};

}  // namespace rose

#include "custom_libraries/collection.cc"

#endif  // CS2420_NOBRAINERS_03COLLECTION_COLLECTION_H_
