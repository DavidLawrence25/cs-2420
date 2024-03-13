#include "no_brainers/08_lp_hash_table/hash_table.h"

#include <stdlib.h>

#include <memory>
#include <ostream>
#include <sstream>

#include "no_brainers/08_lp_hash_table/out_of_space_error.h"

namespace rose {

template <Hashable T>
HashTable<T>::HashTable(const HashTable<T> &other)
    : capacity_(other.capacity_),
      size_(other.size_),
      table_(std::make_unique<Bucket<T>[]>(other.capacity_)) {
  for (int i = 0; i < other.capacity_; ++i) table_[i] = other.table_[i];
}

template <Hashable T>
HashTable<T> &HashTable<T>::operator=(const HashTable<T> &other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  table_ = std::make_unique<Bucket<T>[]>(other.capacity_);
  for (int i = 0; i < other.capacity_; ++i) table_[i] = other.table_[i];
  return *this;
}

template <Hashable T>
std::optional<int> HashTable<T>::Index(T data) const {
  int offset = 0;
  for (; table_[Hash(data + offset)].data != data; ++offset) {
    if (offset == capacity_) return std::nullopt;  // Prevents an infinite loop.
  }
  return Hash(data + offset);
}

template <Hashable T>
void HashTable<T>::Insert(T data) {
  if (size_ >= capacity_) {
    std::stringstream error_message("Cannot add ");
    error_message << data << " to full HashTable.";
    throw OutOfSpaceError(error_message.str());
  }
  int offset = 0;
  for (; !table_[Hash(data + offset)].empty; ++offset)
    ;
  table_[Hash(data + offset)] = Bucket<T>(data, false);
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

template <Hashable _T>
std::ostream &operator<<(std::ostream &out, const HashTable<_T> &hash_table) {
  out << "\nCapacity: " << hash_table.capacity_ << '\n';
  for (int i = 0; i < hash_table.capacity_; ++i) {
    if (hash_table.table_[i].empty) continue;
    out << i << ": " << hash_table.table_[i].data << '\n';
  }
  return out;
}

template <Hashable T>
int HashTable<T>::Hash(T data) const {
  return static_cast<int>(fmod(data, capacity_));
}

}  // namespace rose
