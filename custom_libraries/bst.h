#include <stdlib.h>

#include <iterator>
#include <memory>
#include <optional>
#include <ostream>
#include <stack>
#include <utility>

#ifndef CS2420_CUSTOMLIBRARIES_BST_H_
#define CS2420_CUSTOMLIBRARIES_BST_H_

namespace rose {

template <typename T>
concept Orderable = requires(T t, T u) {
  { t == u };  // Must be directly comparable.
  { t < u };   // Must have a sensible ordering.
};

// A node in a binary search tree.
template <Orderable T>
struct BSTNode {
  T data;
  std::shared_ptr<BSTNode<T>> left;
  std::shared_ptr<BSTNode<T>> right;
};

// Contains pointers to a BST node and its parent.
template <Orderable T>
struct BSTParentChildPair {
  std::shared_ptr<BSTNode<T>> parent;
  std::shared_ptr<BSTNode<T>> child;
};

// A binary search tree: a tree structure in which...
// - each node has 0-2 children
// - left child < parent
// - right child >= parent
template <Orderable T>
class BST {
 public:
  // Shorthand for a pointer to a BST node.
  using pointer = std::shared_ptr<BSTNode<T>>;

  BST() = default;
  // Constructs a deep copy of `other`.
  BST(const BST<T> &other);
  // Deletes this tree and replaces it with a deep copy of `other`.
  BST<T> &operator=(const BST<T> &other);
  virtual ~BST() = default;

  pointer root() const { return root_; }
  size_t GetNumNodes() const { return GetNumNodes(root_); }
  // Returns the number of leaves in the tree.
  // A leaf is a node with no children.
  size_t GetNumLeaves() const { return GetNumLeaves(root_); }

  // Returns a pointer to the closest node to the root with the value `data`.
  // Returns nullptr if no such node exists.
  pointer Find(const T &data) const { return Find(data, root_); }
  // Returns a parent-child pair where the child has the value `data`.
  BSTParentChildPair<T> FindWithParent(const T &data) const;
  // Returns a parent-child pair where the child is the rightmost descendant of
  // the parent in `pair`. Used as a helper method for removing nodes.
  BSTParentChildPair<T> FindRightWithParent(BSTParentChildPair<T> pair) const;
  // Returns a pointer to the parent of the node pointed to by `ptr`.
  // Returns nullptr if that node is an orphan.
  pointer FindParent(pointer ptr) const;
  // Returns true if there is some node in the tree with the value `data`.
  bool Contains(const T &data) const { return Find(data) != nullptr; }

  // Inserts a node with the value `data` into the tree.
  void Insert(const T &data) { Insert(data, root_); }
  // Removes the closest node to the root with the value `data`.
  void Remove(const T &data) { Remove(FindWithParent(data)); }

  // Extracts the binary tree into `out` via pre-order traversal.
  // Space-delimits nodes.
  std::ostream &ExtractPreOrder(std::ostream &out) const;
  // Extracts the binary tree into `out` via in-order traversal.
  // Space-delimits nodes.
  std::ostream &ExtractInOrder(std::ostream &out) const;
  // Extracts the binary tree into `out` via post-order traversal.
  // Space-delimits nodes.
  std::ostream &ExtractPostOrder(std::ostream &out) const;

 private:
  // Returns true if `ptr` points to a node with at least one child.
  bool IsParent(pointer ptr) const { return ptr && (ptr->left || ptr->right); }
  // Returns true if `ptr` points to a leaf.
  bool IsLeaf(pointer ptr) const { return !IsParent(ptr); }

  // Returns the number of nodes in a hypothetical tree with the root node being
  // the one pointed to by `ptr`.
  size_t GetNumNodes(pointer ptr) const;
  // Returns the number of leaves in a hypothetical tree with the root node
  // being the one pointed to by `ptr`.
  size_t GetNumLeaves(pointer ptr) const;

  // Returns a pointer to the closest node to the node pointed to by `ptr` with
  // the value `data`. Returns nullptr if no such node exists.
  pointer Find(const T &data, pointer ptr) const;

  // Inserts a node with the value `data` into the tree, starting at the node
  // pointed to by `ptr`.
  void Insert(const T &data, pointer ptr);
  // Removes the child node in `pair` from the tree.
  void Remove(BSTParentChildPair<T> pair);
  // Removes the child node in `pair` from the tree, assuming it is a leaf.
  void RemoveLeaf(BSTParentChildPair<T> pair);
  // Removes the child node in `pair` from the tree, assuming it only has a
  // child node to its left.
  void RemoveParentOfLeft(BSTParentChildPair<T> pair);
  // Removes the child node in `pair` from the tree, assuming it only has a
  // child node to its right.
  void RemoveParentOfRight(BSTParentChildPair<T> pair);
  // Removes the child node in `pair` from the tree, assuming it has two
  // children.
  void RemoveParentOfBoth(BSTParentChildPair<T> pair);

  pointer root_;
};

// An interface for an object to iterate over a binary search tree.
template <Orderable T>
class BSTIterator {
 public:
  using iterator_category = std::forward_iterator_tag;
  using element_type = T;
  using reference = T &;
  using pointer = T *;
  using difference_type = std::ptrdiff_t;

  BSTIterator() = default;
  BSTIterator(const BST<T> *tree, BST<T>::pointer ptr)
      : tree_(tree), ptr_(ptr) {}

  BST<T>::pointer ptr() const { return ptr_; }

  // Returns true if the pointer is at the last node in the traversal.
  virtual bool IsAtLastNode() const = 0;

  reference operator*() const { return ptr_->data; }
  pointer operator->() const { return &operator*(); }
  // virtual BSTIterator &operator++() = 0;
  bool operator==(const BSTIterator &other) const {
    // Doesn't compare stacks for the sake of speed, but it might matter.
    return tree_ == other.tree_ && ptr_ == other.ptr_;
  }

 protected:
  // Navigates down the tree from the node at the top of the stack, always going
  // to the left.
  void NavigateToLeftmostNode() {
    while (stack_.top()->left) stack_.push(stack_.top()->left);
  }

  // Moves the pointer at the top of the stack into the iterator's pointer.
  void SetPointerToTop() {
    this->ptr_ = stack_.top();
    stack_.pop();
  }

  const BST<T> *tree_;
  BST<T>::pointer ptr_;
  std::stack<typename BST<T>::pointer> stack_;
};

// An iterator that iterates over a binary search tree via pre-order traversal.
// Pre-order traversal is recursively defined as...
// 1. Get the root node.
// 2. Traverse the left branch.
// 3. Traverse the right branch.
template <Orderable T>
class BSTPreOrderIterator : public BSTIterator<T> {
 public:
  BSTPreOrderIterator(
      const BST<T> *tree,
      std::optional<typename BST<T>::pointer> ptr = std::nullopt)
      : BSTIterator<T>(tree, ptr.value_or(tree->root())) {
    if (this->ptr_) AddChildrenToStack();
  }

  BSTPreOrderIterator begin() const { return BSTPreOrderIterator(this->tree_); }
  BSTPreOrderIterator end() const {
    return BSTPreOrderIterator(this->tree_, nullptr);
  }

  bool IsAtLastNode() const override {
    return this->stack_.empty() && this->ptr_;
  }

  BSTPreOrderIterator<T> &operator++();

 private:
  void AddChildrenToStack() {
    // The order is reversed because a stack is a LIFO data structure.
    if (this->ptr_->right) this->stack_.push(this->ptr_->right);
    if (this->ptr_->left) this->stack_.push(this->ptr_->left);
  }
};

// An iterator that iterates over a binary search tree via in-order traversal.
// In-order traversal is recursively defined as...
// 1. Traverse the left branch.
// 2. Get the root node.
// 3. Traverse the right branch.
template <Orderable T>
class BSTInOrderIterator : public BSTIterator<T> {
 public:
  BSTInOrderIterator(const BST<T> *tree,
                     std::optional<typename BST<T>::pointer> ptr = std::nullopt)
      : BSTIterator<T>(tree, ptr.value_or(tree->root())) {
    if (this->ptr_) {
      this->stack_.push(this->ptr_);
      this->NavigateToLeftmostNode();
      this->SetPointerToTop();
    }
  }

  BSTInOrderIterator begin() const { return BSTInOrderIterator(this->tree_); }
  BSTInOrderIterator end() const {
    return BSTInOrderIterator(this->tree_, nullptr);
  }

  bool IsAtLastNode() const override {
    return this->ptr_ && !this->ptr_->right && this->stack_.empty();
  }

  BSTInOrderIterator<T> &operator++();
};

// An iterator that iterates over a binary search tree via post-order traversal.
// Post-order traversal is recursively defined as...
// 1. Traverse the left branch.
// 2. Traverse the right branch.
// 3. Get the root node.
template <Orderable T>
class BSTPostOrderIterator : public BSTIterator<T> {
 public:
  BSTPostOrderIterator(
      const BST<T> *tree,
      std::optional<typename BST<T>::pointer> ptr = std::nullopt)
      : BSTIterator<T>(tree, ptr.value_or(tree->root())) {
    if (this->ptr_) {
      this->stack_.push(this->ptr_);
      this->NavigateToLeftmostNode();
      NavigateRightToLeftmostLeaf();
      this->SetPointerToTop();
    }
  }

  BSTPostOrderIterator begin() const {
    return BSTPostOrderIterator(this->tree_);
  }

  BSTPostOrderIterator end() const {
    return BSTPostOrderIterator(this->tree_, nullptr);
  }

  bool IsAtLastNode() const override {
    return this->stack_.empty() && this->ptr_;
  }

  BSTPostOrderIterator<T> &operator++();

 private:
  // Navigates down the tree by going right once, then going left as much as
  // possible, and repeating until it reaches a leaf.
  void NavigateRightToLeftmostLeaf() {
    while (this->stack_.top()->right) {
      this->stack_.push(this->stack_.top()->right);
      this->NavigateToLeftmostNode();
    }
  }
};

}  // namespace rose

#include "custom_libraries/bst.cc"

#endif  // CS2420_CUSTOMLIBRARIES_BST_H_
