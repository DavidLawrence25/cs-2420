#include <stdlib.h>

#include <iterator>
#include <ostream>

#include "custom_libraries/aliases.h"

#ifndef CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_
#define CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_

namespace rose {

// Represents a node in a singly-linked list.
template <typename T>
struct SNode {
  T data;
  sptr<SNode<T>> next;
};

template <typename T>
class SLinkedListIterator;

// Represents a singly-linked list of nodes.
template <typename T>
class SLinkedList {
 public:
  SLinkedList() = default;
  SLinkedList(const SLinkedList &other);
  SLinkedList &operator=(const SLinkedList &other);
  ~SLinkedList() = default;

  bool empty() const { return size_ == 0; }
  size_t size() const { return size_; }
  SLinkedListIterator<T> begin() const;
  SLinkedListIterator<T> end() const;

  // Returns the value stored at the front of the list.
  // Returns std::nullopt if list is empty.
  opt<T> PeekFront() const;
  // Returns the value stored at the back of the list.
  // Returns std::nullopt if list is empty.
  opt<T> PeekBack() const;
  // Returns the value stored at index `i`.
  // Returns std::nullopt if `i >= size_`.
  opt<T> Peek(uindex_t i) const;

  // Pushes `data` to the front of the list.
  void PushFront(T data);
  // Pushes `data` to the back of the list.
  void PushBack(T data);
  // Inserts `data` at index `i`. Does nothing if `i > size_`.
  void Insert(uindex_t i, T data);
  // Pops the front off the list.
  // If the list is empty, does nothing.
  void PopFront();
  // Pops the back off the list.
  // If the list is empty, does nothing.
  void PopBack();
  // Erases the node at index `i`. Does nothing if `i >= size_`.
  void Erase(uindex_t i);
  // Removes all nodes containing `data`.
  void Remove(T data);

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const SLinkedList<_T> &list);

 private:
  // Returns a pointer to the node at index `i`.
  // If `i` is not on the interval `[0, size_)`, returns nullptr.
  sptr<SNode<T>> GetNodePointer(uindex_t i) const;

  sptr<SNode<T>> front_ = nullptr;
  size_t size_ = 0;
};

// Iterates over a singly-linked list.
template <typename T>
class SLinkedListIterator {
 public:
  using iterator_category = std::forward_iterator_tag;
  using element_type = T;
  using reference = T &;
  using pointer = T *;
  using difference_type = std::ptrdiff_t;

  SLinkedListIterator() = default;
  SLinkedListIterator(const SLinkedList<T> *list, sptr<SNode<T>> ptr)
      : list_(list), ptr_(ptr) {}

  sptr<SNode<T>> ptr() const;

  reference operator*() const;
  pointer operator->() const;
  SLinkedListIterator &operator++();
  SLinkedListIterator operator++(int);
  bool operator==(const SLinkedListIterator &other) const;

 private:
  const SLinkedList<T> *list_;
  sptr<SNode<T>> ptr_;
};

}  // namespace rose

#include "custom_libraries/s_linked_list.cc"

#endif  // CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_
