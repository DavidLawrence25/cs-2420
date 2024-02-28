#include <stdlib.h>

#include <optional>
#include <ostream>

#include "custom_libraries/d_linked_list.h"

#ifndef CS2420_NOBRAINERS_07STACK_STACK_H_
#define CS2420_NOBRAINERS_07STACK_STACK_H_

namespace rose {

// Represents a LIFO stack.
template <typename T>
class Stack {
 public:
  Stack() = default;
  Stack(const Stack &other) = default;
  virtual ~Stack() = default;

  // Returns the value at the top of the stack.
  // If no such value exists, returns std::nullopt.
  inline std::optional<T> top() const { return data_.PeekFront(); }
  inline bool empty() const { return data_.empty(); }
  inline size_t size() const { return data_.size(); }

  // Pushes `value` onto the top of the stack.
  inline void Push(T value) { data_.PushFront(value); }
  // Pops the top value off the stack.
  // Does nothing if the stack is empty.
  inline void Pop() { data_.PopFront(); }

  // Linearly pops all items off the stack.
  inline void Clear() {
    while (size()) data_.PopFront();
  }

  Stack &operator=(const Stack &other);

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out, const Stack<_T> &stack);

 protected:
  DLinkedList<T> data_;
};

}  // namespace rose

#include "no_brainers/07_stack/stack.cc"

#endif  // CS2420_NOBRAINERS_07STACK_STACK_H_
