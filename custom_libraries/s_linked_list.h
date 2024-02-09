#include <stdlib.h>

#include <iterator>
#include <memory>
#include <optional>
#include <ostream>

#ifndef CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_
#define CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_

namespace rose {

// Represents a node in a singly-linked list.
template <typename T>
struct SNode {
  T data;
  std::shared_ptr<SNode<T>> next;
};

template <typename T>
class SLinkedListIterator;

// Represents a singly-linked list of nodes.
template <typename T>
class SLinkedList {
 public:
  SLinkedList() : front_(nullptr), size_(0) {}

  bool empty() const;
  size_t size() const;
  SLinkedListIterator<T> begin() const;
  SLinkedListIterator<T> end() const;

  // Returns the value stored at the front of the list.
  // If the list is empty, returns std::nullopt.
  std::optional<T> PeekFront() const;
  // Returns the value stored at the back of the list.
  // If the list is empty, returns std::nullopt.
  std::optional<T> PeekBack() const;
  // Returns the value stored at index `i`.
  // If `i` is not on the interval `[0, size_)`, returns std::nullopt.
  std::optional<T> Peek(int i) const;

  // Pushes `data` to the front of the list.
  void PushFront(T data);
  // Pushes `data` to the back of the list.
  void PushBack(T data);
  // Inserts `data` at index `i`.
  // If `i` is not on the interval `[0, size_]`, does nothing.
  void Insert(int i, T data);
  // Pops the front off the list.
  // If the list is empty, does nothing.
  void PopFront();
  // Pops the back off the list.
  // If the list is empty, does nothing.
  void PopBack();
  // Erases the node at index `i`.
  // If `i` is not on the interval `[0, size_)`, does nothing.
  void Erase(int i);
  // Removes all nodes containing `data`.
  void Remove(T data);

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const SLinkedList<_T> &list);

 protected:
  // Returns a pointer to the node at index `i`.
  // If `i` is not on the interval `[0, size_)`, returns nullptr.
  std::shared_ptr<SNode<T>> GetNodePointer(int i) const;

  std::shared_ptr<SNode<T>> front_;
  size_t size_;
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
  SLinkedListIterator(const SLinkedList<T> *list, std::shared_ptr<SNode<T>> ptr)
      : list_(list), ptr_(ptr) {}

  std::shared_ptr<SNode<T>> ptr() const;

  reference operator*() const;
  pointer operator->() const;
  SLinkedListIterator &operator++();
  SLinkedListIterator operator++(int);
  bool operator==(const SLinkedListIterator &other) const;

 private:
  const SLinkedList<T> *list_;
  std::shared_ptr<SNode<T>> ptr_;
};

}  // namespace rose

#include "custom_libraries/s_linked_list.cc"

#endif  // CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_
