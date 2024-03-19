#include <stdlib.h>

#include <memory>
#include <optional>
#include <ostream>

#ifndef CS2420_LABS_08DYNAMICHASHTABLE_HASHTABLE_H_
#define CS2420_LABS_08DYNAMICHASHTABLE_HASHTABLE_H_

namespace rose {

template <typename T>
concept Hashable = requires(T t, std::ostream &out) {
  { T() };         // Must be default-constructible.
  { t + 1 };       // Must support adding to an integer.
  { fmod(t, 1) };  // Must have a sensible modulus.
  { out << t };    // Must* be capable of stream extraction.
};

template <Hashable T>
struct Bucket {
  T data = T();
  bool empty = true;
};

// Dynamically-sized hash table implemented via quadratic probing.
template <Hashable T>
class HashTable {
 public:
  HashTable(size_t capacity = 17, double load_factor_threshold = 0.65)
      : capacity_(capacity),
        load_factor_threshold_(load_factor_threshold),
        table_(std::make_unique<Bucket<T>[]>(capacity)) {}
  // Constructs a deep copy of `other`.
  HashTable(const HashTable &other);
  // Works as a deep copy assignment operator.
  HashTable &operator=(const HashTable &other);
  virtual ~HashTable() = default;

  bool empty() const { return size_ == 0; }
  size_t capacity() const { return capacity_; }
  size_t size() const { return size_; }
  double load_factor_threshold() const { return load_factor_threshold_; }

  // Returns the index of `data` in the table (or std::nullopt if absent).
  // Time Complexity: O(1) - O(n)
  // Space Complexity: O(1)
  std::optional<int> Index(T data) const;
  // Inserts `data` into the table.
  // Time Complexity: O(1) - O(n)
  // Space Complexity: O(1) - O(n)
  void Insert(T data);
  // Removes `data` from the table. Does nothing if `data` is absent.
  // Time Complexity: O(1) - O(n)
  // Space Complexity: O(1)
  void Remove(T data);
  // Returns true if `data` is present in the table.
  // Time Complexity: O(1) - O(n)
  // Space Complexity: O(1)
  bool Contains(T data) const;
  // Removes all elements from the table.
  // Time Complexity: O(1)
  // Space Complexity: O(n) (kinda)
  void Clear();
  // Increases the capacity of the table roughly by a factor of 2.
  // Time Complexity: O(n)
  // Space Complexity: O(n)
  void Rehash();

  template <Hashable _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const HashTable<_T> &hash_table);

 private:
  // Returns `floor(data % capacity)`.
  // Guaranteed to return a value on the interval `[0, capacity)`.
  int Hash(T data) const;
  // Returns the next free index in the table according to quadratic probing.
  // Returns std::nullopt if all possible indices are taken.
  std::optional<int> NextFreeIndex(T data) const;

  size_t capacity_;
  size_t size_ = 0;
  // Ratio of size to capacity after which the table will rehash.
  double load_factor_threshold_;
  std::unique_ptr<Bucket<T>[]> table_;
};

}  // namespace rose

#include "labs/08_dynamic_hash_table/hash_table.cc"

#endif  // CS2420_LABS_08DYNAMICHASHTABLE_HASHTABLE_H_
