#include "labs/08_dynamic_hash_table/hash_table.h"

#include <stdlib.h>

#include <memory>
#include <optional>
#include <queue>

#include "custom_libraries/number_utils.h"

namespace rose {

template <Hashable T>
HashTable<T>::HashTable(const HashTable<T> &other)
    : capacity_(other.capacity_),
      size_(other.size_),
      load_factor_threshold_(other.load_factor_threshold_),
      table_(std::make_unique<Bucket<T>[]>(other.capacity_)) {
  for (int i = 0; i < other.capacity_; ++i) table_[i] = other.table_[i];
}

template <Hashable T>
HashTable<T> &HashTable<T>::operator=(const HashTable<T> &other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  load_factor_threshold_ = other.load_factor_threshold_;
  table_ = std::make_unique<Bucket<T>[]>(other.capacity_);
  for (int i = 0; i < other.capacity_; ++i) table_[i] = other.table_[i];
  return *this;
}

template <Hashable T>
std::optional<int> HashTable<T>::Index(T data) const {
  int offset = 0;
  int next_odd_number = 1;
  // The indices produced by quadratic probing are symmetrical unless the
  // capacity is 2, so we can ignore the second half in most cases.
  int max_iterations = (capacity_ == 2) ? 2 : (capacity_ + 1) >> 1;
  for (int _ = 0; _ < max_iterations; ++_) {
    int index = Hash(data + offset);
    if (table_[index].data == data) return index;
    // The sum of the first n odd integers = n ** 2.
    offset += next_odd_number;
    next_odd_number += 2;
  }
  return std::nullopt;
}

template <Hashable T>
void HashTable<T>::Insert(T data) {
  std::optional<int> index = NextFreeIndex(data);
  double fill = static_cast<double>(size_ + 1) / static_cast<double>(capacity_);
  if (!index.has_value() || fill > load_factor_threshold_) {
    Rehash();
    index = NextFreeIndex(data);
  }
  table_[index.value()] = Bucket<T>(data, false);
  ++size_;
}

template <Hashable T>
void HashTable<T>::Remove(T data) {
  std::optional<int> index = Index(data);
  if (!index.has_value()) return;
  table_[index.value()] = Bucket<T>();
  --size_;
}

template <Hashable T>
bool HashTable<T>::Contains(T data) const {
  return Index(data).has_value();
}

template <Hashable T>
void HashTable<T>::Clear() {
  size_ = 0;
  table_ = std::make_unique<Bucket<T>[]>(capacity_);
}

template <Hashable T>
void HashTable<T>::Rehash() {
  std::queue<T> backup_data;
  for (int i = 0; i < capacity_; ++i) {
    if (!table_[i].empty) backup_data.push(table_[i].data);
  }
  capacity_ = NextPrime(capacity_ << 1);
  Clear();
  for (; !backup_data.empty(); backup_data.pop()) Insert(backup_data.front());
}

template <Hashable T>
int HashTable<T>::Hash(T data) const {
  return static_cast<int>(fmod(data, capacity_));
}

template <Hashable T>
std::optional<int> HashTable<T>::NextFreeIndex(T data) const {
  if (size_ == capacity_) return std::nullopt;

  int offset = 0;
  int next_odd_number = 1;
  // The indices produced by quadratic probing are symmetrical unless the
  // capacity is 2, so we can ignore the second half in most cases.
  int max_iterations = (capacity_ == 2) ? 2 : (capacity_ + 1) >> 1;
  for (int _ = 0; _ < max_iterations; ++_) {
    int index = Hash(data + offset);
    if (table_[index].empty) return index;
    // The sum of the first n odd integers = n ** 2.
    offset += next_odd_number;
    next_odd_number += 2;
  }
  return std::nullopt;
}

}  // namespace rose
