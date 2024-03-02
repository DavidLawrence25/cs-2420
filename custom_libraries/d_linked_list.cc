#include "custom_libraries/d_linked_list.h"

#include <stdlib.h>

#include <memory>
#include <optional>
#include <ostream>
#include <ranges>
#include <vector>

namespace rose {

template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &other) {
  front_ = nullptr;
  back_ = nullptr;
  size_ = 0;
  for (T data : other) PushBack(data);
}

template <typename T>
bool DLinkedList<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t DLinkedList<T>::size() const {
  return size_;
}

template <typename T>
DLinkedListIterator<T> DLinkedList<T>::begin() const {
  return DLinkedListIterator<T>(/*list=*/this, /*ptr=*/front_);
}

template <typename T>
DLinkedListIterator<T> DLinkedList<T>::end() const {
  return DLinkedListIterator<T>(/*list=*/this, /*ptr=*/nullptr);
}

template <typename T>
std::optional<T> DLinkedList<T>::PeekFront() const {
  return front_ ? std::optional<T>(front_->data) : std::nullopt;
}

template <typename T>
std::optional<T> DLinkedList<T>::PeekBack() const {
  return back_ ? std::optional<T>(back_->data) : std::nullopt;
}

template <typename T>
std::optional<T> DLinkedList<T>::Peek(int i) const {
  std::shared_ptr<DNode<T>> ptr = GetNodePointer(i);
  return ptr ? std::optional<T>(ptr->data) : std::nullopt;
}

template <typename T>
void DLinkedList<T>::PushFront(T data) {
  auto new_front = std::make_shared<DNode<T>>(data, /*previous=*/nullptr,
                                              /*next=*/front_);
  if (front_) front_->previous = new_front;
  front_ = new_front;
  if (!back_) back_ = front_;
  ++size_;
}

template <typename T>
void DLinkedList<T>::PushBack(T data) {
  auto new_back = std::make_shared<DNode<T>>(data, /*previous=*/back_,
                                             /*next=*/nullptr);
  if (back_) back_->next = new_back;
  back_ = new_back;
  if (!front_) front_ = back_;
  ++size_;
}

template <typename T>
void DLinkedList<T>::Insert(int i, T data) {
  if (i == 0) {
    PushFront(data);
  } else if (i == size_) {
    PushBack(data);
  } else {
    std::shared_ptr<DNode<T>> ptr = GetNodePointer(i);
    if (ptr == nullptr) return;

    auto new_node = std::make_shared<DNode<T>>(data, /*previous=*/ptr->previous,
                                               /*next=*/ptr);

    ptr->previous->next = new_node;
    ptr->previous = new_node;
    ++size_;
  }
}

template <typename T>
void DLinkedList<T>::PopFront() {
  if (empty()) return;
  front_ = front_->next;
  if (front_) front_->previous = nullptr;
  if (size_ == 1) back_ = front_;
  --size_;
}

template <typename T>
void DLinkedList<T>::PopBack() {
  if (empty()) return;
  back_ = back_->previous;
  if (back_) back_->next = nullptr;
  if (size_ == 1) front_ = back_;
  --size_;
}

template <typename T>
void DLinkedList<T>::Erase(int i) {
  if (i == 0) {
    PopFront();
  } else if (i == size_ - 1) {
    PopBack();
  } else {
    std::shared_ptr<DNode<T>> to_erase = GetNodePointer(i);
    if (to_erase == nullptr) return;
    to_erase->previous->next = to_erase->next;
    to_erase->next->previous = to_erase->previous;
    --size_;
  }
}

template <typename T>
void DLinkedList<T>::Remove(T data) {
  std::vector<int> indices_to_delete;
  for (const auto [i, x] : std::views::enumerate(*this)) {
    if (x == data) indices_to_delete.push_back(i);
  }
  for (int i : indices_to_delete) Erase(i);
}

template <typename _T>
std::ostream &operator<<(std::ostream &out, const DLinkedList<_T> &list) {
  if (list.empty()) return out;

  for (_T x : std::views::counted(list.begin(), list.size_ - 1)) {
    out << x << ' ';
  }

  out << list.PeekBack().value();
  return out;
}

template <typename T>
std::shared_ptr<DNode<T>> DLinkedList<T>::GetNodePointer(int i) const {
  if (i < 0 || i >= size_) return nullptr;

  int dist_from_left = i;
  int dist_from_right = size_ - i - 1;

  std::shared_ptr<DNode<T>> ptr;
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
std::shared_ptr<DNode<T>> DLinkedListIterator<T>::ptr() const {
  return ptr_;
}

template <typename T>
DLinkedListIterator<T>::reference DLinkedListIterator<T>::operator*() const {
  return ptr_->data;
}

template <typename T>
DLinkedListIterator<T>::pointer DLinkedListIterator<T>::operator->() const {
  return &operator*();
}

template <typename T>
DLinkedListIterator<T> &DLinkedListIterator<T>::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
DLinkedListIterator<T> DLinkedListIterator<T>::operator++(int) {
  DLinkedListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
DLinkedListIterator<T> &DLinkedListIterator<T>::operator--() {
  ptr_ = ptr_->previous;
  return *this;
}

template <typename T>
DLinkedListIterator<T> DLinkedListIterator<T>::operator--(int) {
  DLinkedListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
bool DLinkedListIterator<T>::operator==(
    const DLinkedListIterator &other) const {
  return list_ == other.list_ && ptr_ == other.ptr_;
}

}  // namespace rose
