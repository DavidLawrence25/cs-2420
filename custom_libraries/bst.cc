#include "custom_libraries/bst.h"

#include <stdlib.h>

#include <memory>
#include <ostream>
#include <ranges>

namespace rose {

template <Orderable T>
BST<T>::BST(const BST<T> &other) {
  for (T data : BSTPreOrderIterator<T>(&other)) Insert(data);
}

template <Orderable T>
BST<T> &BST<T>::operator=(const BST<T> &other) {
  root_ = nullptr;
  for (T data : BSTPreOrderIterator<T>(&other)) Insert(data);
  return *this;
}

template <Orderable T>
size_t BST<T>::GetNumNodes(pointer ptr) const {
  return ptr ? GetNumNodes(ptr->left) + GetNumNodes(ptr->right) + 1 : 0;
}

template <Orderable T>
size_t BST<T>::GetNumLeaves(pointer ptr) const {
  if (!ptr) return 0;
  return (ptr->left || ptr->right)
             ? GetNumLeaves(ptr->left) + GetNumLeaves(ptr->right)
             : 1;
}

template <Orderable T>
BST<T>::pointer BST<T>::Find(const T &data, pointer ptr) const {
  if (!ptr) return nullptr;
  if (data == ptr->data) return ptr;
  return Find(data, data < ptr->data ? ptr->left : ptr->right);
}

template <Orderable T>
BSTParentChildPair<T> BST<T>::FindWithParent(const T &data) const {
  BSTParentChildPair<T> pair = {.parent = nullptr, .child = root_};
  while (pair.child) {
    if (data == pair.child->data) break;
    if (data < pair.child->data) {
      pair.AdvanceGenerationLeftward();
    } else {
      pair.AdvanceGenerationRightward();
    }
  }
  return pair;
}

template <Orderable T>
BSTParentChildPair<T> BST<T>::FindRightWithParent(
    BSTParentChildPair<T> pair) const {
  while (pair.child && pair.child->right) pair.AdvanceGenerationRightward();
  return pair;
}

template <Orderable T>
BST<T>::pointer BST<T>::FindParent(pointer ptr) const {
  return ptr ? FindWithParent(ptr->data).parent : nullptr;
}

template <Orderable T>
void BST<T>::Insert(const T &data, pointer ptr) {
  if (!ptr && !root_) {
    root_ = std::make_shared<BSTNode<T>>(data, nullptr, nullptr);
  } else if (data < ptr->data) {
    if (ptr->left) {
      Insert(data, ptr->left);
    } else {
      ptr->left = std::make_shared<BSTNode<T>>(data, nullptr, nullptr);
    }
  } else {
    if (ptr->right) {
      Insert(data, ptr->right);
    } else {
      ptr->right = std::make_shared<BSTNode<T>>(data, nullptr, nullptr);
    }
  }
}

template <Orderable T>
void BST<T>::Remove(BSTParentChildPair<T> pair) {
  if (!pair.child) return;
  if (IsLeaf(pair.child)) {
    RemoveLeaf(pair);
  } else if (!pair.child->right) {
    RemoveParentOfLeft(pair);
  } else if (!pair.child->left) {
    RemoveParentOfRight(pair);
  } else {
    RemoveParentOfBoth(pair);
  }
}

template <Orderable T>
void BST<T>::RemoveLeaf(BSTParentChildPair<T> pair) {
  if (!pair.parent && pair.child == root_) {
    root_ = nullptr;
  } else if (pair.parent->left == pair.child) {
    pair.parent->left = nullptr;
  } else {
    pair.parent->right = nullptr;
  }
}

template <Orderable T>
void BST<T>::RemoveParentOfLeft(BSTParentChildPair<T> pair) {
  if (!pair.parent && pair.child == root_) {
    root_ = pair.child->left;
  } else if (pair.parent->left == pair.child) {
    pair.parent->left = pair.child->left;
  } else {
    pair.parent->right = pair.child->left;
  }
}

template <Orderable T>
void BST<T>::RemoveParentOfRight(BSTParentChildPair<T> pair) {
  if (!pair.parent && pair.child == root_) {
    root_ = pair.child->right;
  } else if (pair.parent->left == pair.child) {
    pair.parent->left = pair.child->right;
  } else {
    pair.parent->right = pair.child->right;
  }
}

template <Orderable T>
void BST<T>::RemoveParentOfBoth(BSTParentChildPair<T> pair) {
  BST<T>::pointer to_overwrite = pair.child;
  pair.AdvanceGenerationLeftward();
  BSTParentChildPair<T> remove_pair = FindRightWithParent(pair);
  to_overwrite->data = remove_pair.child->data;
  Remove(remove_pair);
}

template <Orderable T>
std::ostream &BST<T>::ExtractPreOrder(std::ostream &out) const {
  if (root_) {
    BSTPreOrderIterator<T> it = {this};
    for (; !it.IsAtLastNode(); ++it) out << *it << ' ';
    out << *it;
  }
  return out;
}

template <Orderable T>
std::ostream &BST<T>::ExtractInOrder(std::ostream &out) const {
  if (root_) {
    BSTInOrderIterator<T> it = {this};
    for (; !it.IsAtLastNode(); ++it) out << *it << ' ';
    out << *it;
  }
  return out;
}

template <Orderable T>
std::ostream &BST<T>::ExtractPostOrder(std::ostream &out) const {
  if (root_) {
    BSTPostOrderIterator<T> it = {this};
    for (; !it.IsAtLastNode(); ++it) out << *it << ' ';
    out << *it;
  }
  return out;
}

template <Orderable T>
BSTPreOrderIterator<T> &BSTPreOrderIterator<T>::operator++() {
  if (this->stack_.empty()) {
    this->ptr_ = nullptr;
  } else {
    this->SetPointerToTop();
    AddChildrenToStack();
  }
  return *this;
}

template <Orderable T>
BSTInOrderIterator<T> &BSTInOrderIterator<T>::operator++() {
  if (this->ptr_->right) {
    this->stack_.push(this->ptr_->right);
    this->NavigateToLeftmostNode();
  } else if (this->stack_.empty()) {
    this->ptr_ = nullptr;
    return *this;
  }
  this->SetPointerToTop();
  return *this;
}

template <Orderable T>
BSTPostOrderIterator<T> &BSTPostOrderIterator<T>::operator++() {
  if (this->stack_.empty()) {
    this->ptr_ = nullptr;
    return *this;
  }
  if (this->stack_.top()->left == this->ptr_) {
    NavigateRightToLeftmostLeaf();
  }
  this->SetPointerToTop();
  return *this;
}

}  // namespace rose
