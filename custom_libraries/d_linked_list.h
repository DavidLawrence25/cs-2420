#include <stdlib.h>

#include <iterator>
#include <memory>
#include <optional>
#include <ostream>

#ifndef CS2420_CUSTOMLIBRARIES_DLINKEDLIST_H_
#define CS2420_CUSTOMLIBRARIES_DLINKEDLIST_H_

namespace rose {

// Represents a node in a doubly-linked list.
template <typename T>
struct DNode {
  T data;
  std::shared_ptr<DNode<T>> previous;
  std::shared_ptr<DNode<T>> next;
};

template <typename T>
class DLinkedListIterator;

// Represents a doubly-linked list of nodes.
template <typename T>
class DLinkedList {
 public:
  DLinkedList() : front_(nullptr), back_(nullptr), size_(0) {}

  bool empty() const;
  size_t size() const;
  DLinkedListIterator<T> begin() const;
  DLinkedListIterator<T> end() const;

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
                                  const DLinkedList<_T> &list);

 protected:
  // Returns a pointer to the node at index `i`.
  // If `i` is not on the interval `[0, size_)`, returns nullptr.
  std::shared_ptr<DNode<T>> GetNodePointer(int i) const;

  std::shared_ptr<DNode<T>> front_;
  std::shared_ptr<DNode<T>> back_;
  size_t size_;
};

// Iterates over a doubly-linked list.
template <typename T>
class DLinkedListIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using element_type = T;
  using reference = T &;
  using pointer = T *;
  using difference_type = std::ptrdiff_t;

  DLinkedListIterator() = default;
  DLinkedListIterator(const DLinkedList<T> *list, std::shared_ptr<DNode<T>> ptr)
      : list_(list), ptr_(ptr) {}

  std::shared_ptr<DNode<T>> ptr() const;

  reference operator*() const;
  pointer operator->() const;
  DLinkedListIterator &operator++();
  DLinkedListIterator operator++(int);
  DLinkedListIterator &operator--();
  DLinkedListIterator operator--(int);
  bool operator==(const DLinkedListIterator &other) const;

 private:
  const DLinkedList<T> *list_;
  std::shared_ptr<DNode<T>> ptr_;
};

}  // namespace rose

#include "custom_libraries/d_linked_list.cc"

#endif  // CS2420_CUSTOMLIBRARIES_DLINKEDLIST_H_
