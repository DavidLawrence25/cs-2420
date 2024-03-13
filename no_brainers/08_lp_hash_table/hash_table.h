#include <math.h>
#include <stdlib.h>

#include <concepts>
#include <memory>
#include <optional>
#include <ostream>

#ifndef CS2420_NOBRAINERS_08LPHASHTABLE_HASHTABLE_H_
#define CS2420_NOBRAINERS_08LPHASHTABLE_HASHTABLE_H_

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

template <Hashable T>
class HashTable {
 public:
  explicit HashTable(size_t capacity = 17)
      : capacity_(capacity), table_(std::make_unique<Bucket<T>[]>(capacity)) {}
  HashTable(const HashTable &other);
  HashTable &operator=(const HashTable &other);
  virtual ~HashTable() = default;

  bool empty() const { return size_ == 0; }
  size_t capacity() const { return capacity_; }
  size_t size() const { return size_; }

  std::optional<int> Index(T data) const;
  void Insert(T data);
  void Remove(T data);
  bool Contains(T data) const;
  void Clear();

  template <Hashable _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const HashTable<_T> &hash_table);

 private:
  int Hash(T data) const;

  size_t capacity_;
  size_t size_ = 0;
  std::unique_ptr<Bucket<T>[]> table_;
};

}  // namespace rose

#include "no_brainers/08_lp_hash_table/hash_table.cc"

#endif  // CS2420_NOBRAINERS_08LPHASHTABLE_HASHTABLE_H_
