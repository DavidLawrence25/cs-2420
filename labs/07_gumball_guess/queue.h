#include <stdlib.h>

#include <optional>
#include <ostream>

#include "custom_libraries/d_linked_list.h"

#ifndef CS2420_LABS_07GUMBALLGUESS_QUEUE_H_
#define CS2420_LABS_07GUMBALLGUESS_QUEUE_H_

namespace rose {

// Represents a FIFO queue.
template <typename T>
class Queue {
 public:
  Queue() = default;
  Queue(const Queue &other) { data_ = other.data_; }
  virtual ~Queue() = default;

  bool empty() const { return data_.empty(); }
  size_t size() const { return data_.size(); }

  // Returns the value at the front of the queue.
  // If no such value exists, returns std::nullopt.
  std::optional<T> PeekFront() const { return data_.PeekFront(); }
  // Returns the value at the back of the queue.
  // If no such value exists, returns std::nullopt.
  std::optional<T> PeekBack() const { return data_.PeekBack(); }

  // Puts `data` at the back of the queue.
  void Enqueue(T data) { data_.PushBack(data); }
  // Removes the value at the front of the queue.
  // Does nothing if the queue is empty.
  void Dequeue() { data_.PopFront(); }

  // Linearly dequeues all items.
  void Clear() {
    while (size()) Dequeue();
  }

  operator bool() const { return size(); }

  template <typename _T>
  friend std::ostream &operator<<(std::ostream &out, const Queue<_T> &queue);

 private:
  DLinkedList<T> data_;
};

}  // namespace rose

#include "labs/07_gumball_guess/queue.cc"

#endif  // CS2420_LABS_07GUMBALLGUESS_QUEUE_H_
