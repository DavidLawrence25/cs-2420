#include "no_brainers/05_linked_list/linked_list.h"

#include <stdlib.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <ostream>
#include <ranges>

namespace rose {

template <typename T>
bool LinkedList<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t LinkedList<T>::size() const {
  return size_;
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::begin() const {
  return LinkedListIterator<T>(this, front_);
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::end() const {
  return LinkedListIterator<T>(this, nullptr);
}

template <typename T>
std::optional<T> LinkedList<T>::PeekFront() const {
  return front_ ? std::optional<T>(front_->data) : std::nullopt;
}

template <typename T>
std::optional<T> LinkedList<T>::PeekBack() const {
  return back_ ? std::optional<T>(back_->data) : std::nullopt;
}

template <typename T>
std::optional<T> LinkedList<T>::Peek(int i) const {
  std::shared_ptr<Node<T>> ptr = GetNodePointer(i);
  return ptr ? std::optional<T>(ptr->data) : std::nullopt;
}

template <typename T>
void LinkedList<T>::PushFront(T data) {
  auto new_front = std::make_shared<Node<T>>(data, /*previous=*/nullptr,
                                             /*next=*/front_);
  if (front_) front_->previous = new_front;
  front_ = new_front;
  if (!back_) back_ = front_;
  ++size_;
}

template <typename T>
void LinkedList<T>::PushBack(T data) {
  auto new_back = std::make_shared<Node<T>>(data, /*previous=*/back_,
                                            /*next=*/nullptr);
  if (back_) back_->next = new_back;
  back_ = new_back;
  if (!front_) front_ = back_;
  ++size_;
}

template <typename T>
void LinkedList<T>::Insert(int i, T data) {
  if (i == 0) {
    PushFront(data);
    return;
  }
  if (i == size_) {
    PushBack(data);
    return;
  }

  std::shared_ptr<Node<T>> ptr = GetNodePointer(i);
  if (ptr == nullptr) return;

  auto new_node = std::make_shared<Node<T>>(data, /*previous=*/ptr->previous,
                                            /*next=*/ptr);

  ptr->previous->next = new_node;
  ptr->previous = new_node;
  ++size_;
}

template <typename T>
void LinkedList<T>::PopFront() {
  if (empty()) return;
  front_ = front_->next;
  if (front_) front_->previous = nullptr;
  if (size_ == 1) back_ = front_;
  --size_;
}

template <typename T>
void LinkedList<T>::PopBack() {
  if (empty()) return;
  back_ = back_->previous;
  if (back_) back_->next = nullptr;
  if (size_ == 1) front_ = back_;
  --size_;
}

template <typename T>
void LinkedList<T>::Erase(int i) {
  std::shared_ptr<Node<T>> to_erase = GetNodePointer(i);
  if (to_erase == nullptr) return;

  if (i == 0) {
    PopFront();
  } else if (i == size_ - 1) {
    PopBack();
  } else {
    to_erase->previous->next = to_erase->next;
    to_erase->next->previous = to_erase->previous;
    --size_;
  }
}

template <typename T>
void LinkedList<T>::Remove(T data) {
  LinkedListIterator<T> iterator = std::find(begin(), end(), data);
  if (iterator == end()) return;

  std::shared_ptr<Node<T>> to_remove = iterator.ptr();
  if (iterator == begin()) {
    PopFront();
  } else if (to_remove->next == nullptr) {
    PopBack();
  } else {
    to_remove->previous->next = to_remove->next;
    to_remove->next->previous = to_remove->previous;
    --size_;
  }
}

template <typename _T>
std::ostream &operator<<(std::ostream &out, const LinkedList<_T> &list) {
  if (list.empty()) return out;

  for (_T x : std::views::counted(list.begin(), list.size_ - 1)) {
    out << x << ' ';
  }

  out << list.PeekBack().value();
  return out;
}

template <typename T>
std::shared_ptr<Node<T>> LinkedList<T>::GetNodePointer(int i) const {
  if (i < 0 || i >= size_) return nullptr;

  int dist_from_left = i;
  int dist_from_right = size_ - i - 1;

  std::shared_ptr<Node<T>> ptr;
  if (dist_from_left <= dist_from_right) {
    ptr = front_;
    for (int j = 0; j < dist_from_left; ++j) ptr = ptr->next;
  } else {
    ptr = back_;
    for (int j = 0; j < dist_from_right; ++j) ptr = ptr->previous;
  }

  return ptr;
}

template <typename T>
std::shared_ptr<Node<T>> LinkedListIterator<T>::ptr() const {
  return ptr_;
}

template <typename T>
LinkedListIterator<T>::reference LinkedListIterator<T>::operator*() const {
  return ptr_->data;
}

template <typename T>
LinkedListIterator<T>::pointer LinkedListIterator<T>::operator->() const {
  return &operator*();
}

template <typename T>
LinkedListIterator<T> &LinkedListIterator<T>::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator++(int) {
  LinkedListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
LinkedListIterator<T> &LinkedListIterator<T>::operator--() {
  ptr_ = ptr_->previous;
  return *this;
}

template <typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator--(int) {
  LinkedListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator &other) const {
  return list_ == other.list_ && ptr_ == other.ptr_;
}

}  // namespace rose
