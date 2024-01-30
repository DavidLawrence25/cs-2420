#include "s_linked_list.h"

#include <stdlib.h>

namespace rose {

template <typename T>
SLinkedList<T>::SLinkedList() {
  head_ = nullptr;
  length_ = 0;
}

template <typename T>
SLinkedList<T>::~SLinkedList() {
  while (!IsEmpty()) Pop();
}

// Returns a pointer to the first element in the list.
// If no such element exists, returns `nullptr`.
template <typename T>
Node<T> *SLinkedList<T>::head() const {
  return head_;
}

// Returns a pointer to the last element in the list.
// If no such element exists, returns `nullptr`.
template <typename T>
Node<T> *SLinkedList<T>::tail() const {
  if (IsEmpty()) return nullptr;

  Node<T> *current = head();
  while (current->next != nullptr) current = current->next;
  return current;
}

// Returns the number of elements in the list.
template <typename T>
size_t SLinkedList<T>::length() const {
  return length_;
}

// Returns true if the list contains 0 elements.
template <typename T>
bool SLinkedList<T>::IsEmpty() const {
  return length_ == 0;
}

// Returns true if the list contains at least 1 element of the given value.
template <typename T>
bool SLinkedList<T>::Contains(T element) const {
  Node<T> *current = head_;
  while (current != nullptr) {
    if (current->data == element) return true;
    current = current->next;
  }
  return false;
}

// Pushes an element with the given value to the front of the list.
template <typename T>
void SLinkedList<T>::Push(T element) {
  Node<T> *to_add = new Node<T>{element, head_};
  head_ = to_add;
  ++length_;
}

// Inserts an element with the given value at the given index `i`.
// Does nothing if `i` is strictly greater than the length of the list.
template <typename T>
void SLinkedList<T>::Insert(T element, size_t i) {
  if (i > length_) return;
  if (i == 0) {
    Push(element);
    return;
  }
  if (i == length_) {
    Append(element);
    return;
  }

  Node<T> *before = head_;
  for (size_t j = 0; j < i - 1; ++j) before = before->next;

  Node<T> *to_add = new Node<T>{element, before->next};
  before->next = to_add;
  ++length_;
}

// Appends an element with the given value to the end of the list.
template <typename T>
void SLinkedList<T>::Append(T element) {
  Node<T> *to_add = new Node<T>{element, nullptr};

  if (IsEmpty()) {
    head_ = to_add;
  } else {
    tail()->next = to_add;
  }

  ++length_;
}

// Removes the first element in the list. Does not return the element's value.
template <typename T>
void SLinkedList<T>::Pop() {
  if (IsEmpty()) return;

  Node<T> *old_head = head_;
  head_ = head_->next;
  delete old_head;
  --length_;
}

// Removes the first element in the list with the given value.
// Does nothing if no such element exists.
template <typename T>
void SLinkedList<T>::Remove(T element) {
  Node<T> *before = nullptr;
  Node<T> *to_delete = head_;
  while (true) {
    if (to_delete == nullptr) return;
    if (to_delete->data == element) break;
    before = to_delete;
    to_delete = to_delete->next;
  }
  if (before == nullptr) {
    head_ = head_->next;
  } else {
    before->next = to_delete->next;
  }
  delete to_delete;
  --length_;
}

// Removes the element at the specified index `i`.
// Does nothing if `i` is greater than or equal to the length of the list.
template <typename T>
void SLinkedList<T>::Remove(size_t i) {
  if (i >= length_) return;
  if (i == 0) {
    Pop();
    return;
  }

  Node<T> *before = head_;
  for (size_t j = 0; j < i - 1; ++j) before = before->next;

  Node<T> *to_delete = before->next;
  before->next = to_delete->next;
  delete to_delete;
  --length_;
}

// Returns the value of the first element in the list.
// Returns 0 if no such element exists.
template <typename T>
T SLinkedList<T>::PeekHead() const {
  return IsEmpty() ? 0 : head()->data;
}

// Returns the value of the last element in the list.
// Returns 0 if no such element exists.
template <typename T>
T SLinkedList<T>::PeekTail() const {
  return IsEmpty() ? 0 : tail()->data;
}

// Reverses the order of elements in the list.
template <typename T>
void SLinkedList<T>::Reverse() {
  Node<T> *before = nullptr;
  Node<T> *current = head_;
  Node<T> *after = nullptr;
  while (current != nullptr) {
    after = current->next;
    current->next = before;
    before = current;
    current = after;
  }
  head_ = before;
}

}  // namespace rose
