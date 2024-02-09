#include "custom_libraries/s_linked_list.h"

#include <stdlib.h>

#include <memory>
#include <optional>
#include <ostream>
#include <ranges>
#include <vector>

namespace rose {

template <typename T>
bool SLinkedList<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t SLinkedList<T>::size() const {
  return size_;
}

template <typename T>
SLinkedListIterator<T> SLinkedList<T>::begin() const {
  return SLinkedListIterator<T>(/*list=*/this, /*ptr=*/front_);
}

template <typename T>
SLinkedListIterator<T> SLinkedList<T>::end() const {
  return SLinkedListIterator<T>(/*list=*/this, /*ptr=*/nullptr);
}

template <typename T>
std::optional<T> SLinkedList<T>::PeekFront() const {
  return front_ ? std::optional<T>(front_->data) : std::nullopt;
}

template <typename T>
std::optional<T> SLinkedList<T>::PeekBack() const {
  return Peek(size_ - 1);
}

template <typename T>
std::optional<T> SLinkedList<T>::Peek(int i) const {
  std::shared_ptr<SNode<T>> ptr = GetNodePointer(i);
  return ptr ? std::optional<T>(ptr->data) : std::nullopt;
}

template <typename T>
void SLinkedList<T>::PushFront(T data) {
  auto new_front = std::make_shared<SNode<T>>(data, /*next=*/front_);
  front_ = new_front;
  ++size_;
}

template <typename T>
void SLinkedList<T>::PushBack(T data) {
  if (size_ == 0) {
    PushFront(data);
  } else {
    std::shared_ptr<SNode<T>> back = GetNodePointer(size_ - 1);
    auto new_back = std::make_shared<SNode<T>>(data, /*next=*/nullptr);
    if (back) back->next = new_back;
    ++size_;
  }
}

template <typename T>
void SLinkedList<T>::Insert(int i, T data) {
  if (i == 0) {
    PushFront(data);
  } else if (i == size_) {
    PushBack(data);
  } else {
    std::shared_ptr<SNode<T>> before = GetNodePointer(i - 1);
    // If `before` doesn't exist, we would have called PushFront earlier had `i`
    // been a valid index.
    if (before == nullptr) return;

    auto new_node = std::make_shared<SNode<T>>(data, /*next=*/before->next);
    before->next = new_node;
    ++size_;
  }
}

template <typename T>
void SLinkedList<T>::PopFront() {
  if (empty()) return;
  front_ = front_->next;
  --size_;
}

template <typename T>
void SLinkedList<T>::PopBack() {
  if (empty()) return;
  // `new_back` will point to the second-to-last node.
  std::shared_ptr<SNode<T>> new_back = GetNodePointer(size_ - 2);
  if (new_back == nullptr) {
    PopFront();  // ? not sure about this
  } else {
    new_back->next = nullptr;
    --size_;
  }
}

template <typename T>
void SLinkedList<T>::Erase(int i) {
  if (i == 0) {
    PopFront();
  } else if (i == size_ - 1) {
    PopBack();
  } else {
    std::shared_ptr<SNode<T>> before_erase = GetNodePointer(i - 1);
    std::shared_ptr<SNode<T>> to_erase = GetNodePointer(i);
    // Existence of before_erase is guaranteed by the existence of to_erase.
    if (to_erase == nullptr) return;
    before_erase->next = to_erase->next;
    --size_;
  }
}

template <typename T>
void SLinkedList<T>::Remove(T data) {
  std::vector<int> indices_to_delete;
  for (auto const [i, x] : std::views::enumerate(*this)) {
    if (x == data) indices_to_delete.push_back(i);
  }
  for (int i : indices_to_delete) Erase(i);
}

template <typename _T>
std::ostream &operator<<(std::ostream &out, const SLinkedList<_T> &list) {
  if (list.empty()) return out;

  for (_T x : std::views::counted(list.begin(), list.size_ - 1)) {
    out << x << ' ';
  }

  out << list.PeekBack().value();
  return out;
}

template <typename T>
std::shared_ptr<SNode<T>> SLinkedList<T>::GetNodePointer(int i) const {
  if (i < 0 || i >= size_) return nullptr;

  std::shared_ptr<SNode<T>> ptr = front_;
  for (int j = 0; j < i; ++j) ptr = ptr->next;

  return ptr;
}

template <typename T>
std::shared_ptr<SNode<T>> SLinkedListIterator<T>::ptr() const {
  return ptr_;
}

template <typename T>
SLinkedListIterator<T>::reference SLinkedListIterator<T>::operator*() const {
  return ptr_->data;
}

template <typename T>
SLinkedListIterator<T>::pointer SLinkedListIterator<T>::operator->() const {
  return &operator*();
}

template <typename T>
SLinkedListIterator<T> &SLinkedListIterator<T>::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
SLinkedListIterator<T> SLinkedListIterator<T>::operator++(int) {
  SLinkedListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
bool SLinkedListIterator<T>::operator==(
    const SLinkedListIterator &other) const {
  return list_ == other.list_ && ptr_ == other.ptr_;
}

}  // namespace rose
