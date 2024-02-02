#include <stdlib.h>

#ifndef CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_
#define CS2420_CUSTOMLIBRARIES_SLINKEDLIST_H_

namespace rose {

// Represents a node in a linked list containing data of type `T`.
template <typename T>
struct Node {
  T data;
  Node *next;
};

// Represents a singly linked list containing data of type `T`.
template <typename T>
class SLinkedList {
 public:
  SLinkedList();
  ~SLinkedList();

  // Returns a pointer to the first element in the list.
  Node<T> *head() const;
  // Returns a pointer to the last element in the list.
  Node<T> *tail() const;
  // Returns how many elements are in the list.
  size_t length() const;

  // Returns true if there are no elements in the list.
  bool IsEmpty() const;
  // Returns true if the list contains an element with the given value.
  bool Contains(T element) const;
  // Adds an element with the given value to the front (index 0) of the list.
  void Push(T element);
  // Inserts an element with the given value at the specified index `i`.
  void Insert(T element, size_t i);
  // Adds an element with the given value to the end of the list.
  void Append(T element);
  // Removes the first element in the list.
  void Pop();
  // Removes the first element with the given value.
  void Remove(T element);
  // Removes the element at the specified index `i`.
  void Remove(size_t i);
  // Returns the value of the first element in the list.
  T PeekHead() const;
  // Returns the value of the last element in the list.
  T PeekTail() const;
  // Reverses the order of elements in the list.
  void Reverse();

 private:
  Node<T> *head_;
  size_t length_;
};

}  // namespace rose

#include "custom_libraries/s_linked_list.cc"

#endif  // CS2420_CUSTOMLIBRARIES_LINKEDLIST_H_
