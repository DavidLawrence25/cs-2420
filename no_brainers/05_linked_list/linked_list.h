#include <stdlib.h>

#include <iterator>
#include <memory>
#include <optional>
#include <ostream>

#ifndef CS2420_NOBRAINERS_05LINKEDLIST_LINKEDLIST_H_
#define CS2420_NOBRAINERS_05LINKEDLIST_LINKEDLIST_H_

namespace rose {

template <typename T>
struct Node {
  T data;
  std::shared_ptr<Node<T>> previous;
  std::shared_ptr<Node<T>> next;
};

template <typename T>
class LinkedListIterator;

template <typename T>
class LinkedList {
 public:
  LinkedList() : front_(nullptr), back_(nullptr), size_(0) {}

  bool empty() const;
  size_t size() const;
  LinkedListIterator<T> begin() const;
  LinkedListIterator<T> end() const;

  std::optional<T> PeekFront() const;
  std::optional<T> PeekBack() const;
  std::optional<T> Peek(int i) const;

  void PushFront(T data);
  void PushBack(T data);
  void Insert(int i, T data);
  void PopFront();
  void PopBack();
  void Erase(int i);
  void Remove(T data);

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out,
                                  const LinkedList<_T> &list);

 protected:
  std::shared_ptr<Node<T>> GetNodePointer(int i) const;

  std::shared_ptr<Node<T>> front_;
  std::shared_ptr<Node<T>> back_;
  size_t size_;
};

template <typename T>
class LinkedListIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using element_type = T;
  using reference = T &;
  using pointer = T *;
  using difference_type = std::ptrdiff_t;

  LinkedListIterator() = default;
  LinkedListIterator(const LinkedList<T> *list, std::shared_ptr<Node<T>> ptr)
      : list_(list), ptr_(ptr) {}

  std::shared_ptr<Node<T>> ptr() const;

  reference operator*() const;
  pointer operator->() const;
  LinkedListIterator &operator++();
  LinkedListIterator operator++(int);
  LinkedListIterator &operator--();
  LinkedListIterator operator--(int);
  bool operator==(const LinkedListIterator &other) const;

 private:
  const LinkedList<T> *list_;
  std::shared_ptr<Node<T>> ptr_;
};

}  // namespace rose

#include "no_brainers/05_linked_list/linked_list.cc"

#endif  // CS2420_NOBRAINERS_05LINKEDLIST_LINKEDLIST_H_

static_assert(std::bidirectional_iterator<rose::LinkedListIterator<int>>);
static_assert(std::ranges::bidirectional_range<rose::LinkedList<int>>);
