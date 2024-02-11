#include "labs/05_fifth_element/fifth_element.h"

#include <memory>
#include <optional>

#include "custom_libraries/d_linked_list.h"

namespace rose {

template <typename T>
T FifthElement<T>::PeekFifth() const {
  std::optional<T> fifth = this->Peek(/*i=*/4);
  if (fifth.has_value()) return fifth.value();
  // The assignment requires me to throw an error here.
  throw std::runtime_error("No fifth element exists.");
}

template <typename T>
void FifthElement<T>::InsertFifth(T data) {
  this->Insert(/*i=*/4, data);
}

template <typename T>
void FifthElement<T>::EraseFifth() {
  this->Erase(/*i=*/4);
}

template <typename T>
void FifthElement<T>::SwapFourthAndFifth() {
  if (this->size_ < 5) return;

  std::shared_ptr<DNode<T>> third = this->GetNodePointer(/*i=*/2);
  std::shared_ptr<DNode<T>> fourth = third->next;
  std::shared_ptr<DNode<T>> fifth = fourth->next;
  std::shared_ptr<DNode<T>> sixth = fifth->next;

  third->next = fifth;
  fourth->previous = fifth;
  fourth->next = sixth;
  fifth->previous = third;
  fifth->next = fourth;
  if (sixth) sixth->previous = fourth;
}

}  // namespace rose
