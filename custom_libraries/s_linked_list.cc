#include "custom_libraries/s_linked_list.h"

#include <stdlib.h>

#include <ostream>
#include <ranges>

#include "custom_libraries/aliases.h"

namespace rose {

template <typename T>
SLinkedList<T>::SLinkedList(const SLinkedList<T> &other) : size_(other.size_) {
  if (other.empty()) return;

  front_ = std::make_shared<SNode<T>>(other.PeekFront(), /*next=*/nullptr);
  sptr<SNode<T>> back = front_;
  for (T data : other) {
    auto new_back = std::make_shared<SNode<T>>(data, /*next=*/nullptr);
    back->next = new_back;
    back = new_back;
  }
}

template <typename T>
SLinkedList<T> &SLinkedList<T>::operator=(const SLinkedList<T> &other) {
  front_ = nullptr;
  size_ = other.size_;
  if (other.empty()) return *this;

  front_ = std::make_shared<SNode<T>>(other.PeekFront(), /*next=*/nullptr);
  sptr<SNode<T>> back = front_;
  for (T data : other) {
    auto new_back = std::make_shared<SNode<T>>(data, /*next=*/nullptr);
    back->next = new_back;
    back = new_back;
  }
  return *this;
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
opt<T> SLinkedList<T>::PeekFront() const {
  return front_ ? opt<T>(front_->data) : std::nullopt;
}

template <typename T>
opt<T> SLinkedList<T>::PeekBack() const {
  return Peek(size_ - 1);
}

template <typename T>
opt<T> SLinkedList<T>::Peek(uindex_t i) const {
  sptr<SNode<T>> ptr = GetNodePointer(i);
  return ptr ? opt<T>(ptr->data) : std::nullopt;
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
    sptr<SNode<T>> back = GetNodePointer(size_ - 1);
    auto new_back = std::make_shared<SNode<T>>(data, /*next=*/nullptr);
    if (back) back->next = new_back;
    ++size_;
  }
}

template <typename T>
void SLinkedList<T>::Insert(uindex_t i, T data) {
  if (i == 0) {
    PushFront(data);
  } else if (i == size_) {
    PushBack(data);
  } else {
    sptr<SNode<T>> before = GetNodePointer(i - 1);
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
  sptr<SNode<T>> new_back = GetNodePointer(size_ - 2);
  if (new_back == nullptr) {
    PopFront();  // ? not sure about this
  } else {
    new_back->next = nullptr;
    --size_;
  }
}

template <typename T>
void SLinkedList<T>::Erase(uindex_t i) {
  if (i == 0) {
    PopFront();
  } else if (i == size_ - 1) {
    PopBack();
  } else {
    sptr<SNode<T>> before_erase = GetNodePointer(i - 1);
    sptr<SNode<T>> to_erase = GetNodePointer(i);
    // Existence of before_erase is guaranteed by the existence of to_erase.
    if (to_erase == nullptr) return;
    before_erase->next = to_erase->next;
    --size_;
  }
}

template <typename T>
void SLinkedList<T>::Remove(T data) {
  vector<int> indices_to_delete;
  for (const auto [i, x] : std::views::enumerate(*this)) {
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
sptr<SNode<T>> SLinkedList<T>::GetNodePointer(uindex_t i) const {
  if (i >= size_) return nullptr;

  sptr<SNode<T>> ptr = front_;
  for (uindex_t j = 0; j < i; ++j) ptr = ptr->next;

  return ptr;
}

template <typename T>
sptr<SNode<T>> SLinkedListIterator<T>::ptr() const {
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
