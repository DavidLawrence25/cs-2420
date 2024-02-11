#include "custom_libraries/d_linked_list.h"

#ifndef CS2420_LABS_05FIFTHELEMENT_FIFTHELEMENT_H_
#define CS2420_LABS_05FIFTHELEMENT_FIFTHELEMENT_H_

namespace rose {

// Extends a doubly-linked list with methods involving the fifth element.
template <typename T>
class FifthElement : public DLinkedList<T> {
 public:
  // Returns the value stored at index 4.
  // If `size_ < 5`, throws std::runtime_error.
  T PeekFifth() const;

  // Inserts `data` at index 4.
  // If there is no fourth node, does nothing.
  void InsertFifth(T data);
  // Erases the fifth node.
  // If there is no fifth node, does nothing.
  void EraseFifth();
  // Swaps the fourth and fifth nodes.
  // If there is no fifth node, does nothing.
  void SwapFourthAndFifth();
};

}  // namespace rose

#include "labs/05_fifth_element/fifth_element.cc"

#endif  // CS2420_LABS_05FIFTHELEMENT_FIFTHELEMENT_H_
