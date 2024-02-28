#include "no_brainers/07_stack/stack.h"

#include <stdlib.h>

#include <ostream>

#include "custom_libraries/d_linked_list.h"

namespace rose {

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
  Clear();
  for (const T &value : other.data_) data_.PushBack(value);
  return *this;
}

template <typename _T>
std::ostream &operator<<(std::ostream &out, const Stack<_T> &stack) {
  out << stack.data_;
  return out;
}

}  // namespace rose
