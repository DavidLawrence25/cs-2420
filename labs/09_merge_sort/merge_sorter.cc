#include "labs/09_merge_sort/merge_sorter.h"

#include <stdlib.h>

#include <memory>
#include <utility>
#include <vector>

namespace rose {

template <Sortable T>
void MergeSorter::Merge(DLinkedList<T> &a, DLinkedList<T> &&b) {
  if (a.empty()) {
    a = b;
    return;
  }
  std::shared_ptr<DNode<T>> ptr_a = a.front();
  std::shared_ptr<DNode<T>> ptr_b = b.front();
  while (ptr_b) {
    std::shared_ptr<DNode<T>> ptr_insert = ptr_b;
    if (ptr_b->previous) ptr_b->previous->next = ptr_b->next;
    if (ptr_b->next) ptr_b->next->previous = ptr_b->previous;
    ptr_b = ptr_b->next;
    if (ptr_a->data < ptr_insert->data) {
      // Insert ptr_insert before ptr_a.
      ptr_insert->previous = ptr_a->previous;
      ptr_insert->next = ptr_a;
      ptr_a->previous = ptr_insert;
      if (ptr_insert->previous) {
        ptr_insert->previous->next = ptr_insert;
      } else {
        a.set_front(ptr_insert);
      }
    } else {
      // Insert ptr_insert after ptr_a.
      ptr_insert->previous = ptr_a;
      ptr_insert->next = ptr_a->next;
      ptr_a->next = ptr_insert;
      if (ptr_insert->next) {
        ptr_insert->next->previous = ptr_insert;
      } else {
        a.set_back(ptr_insert);
      }
      ptr_a = ptr_a->next;
    }
  }
  a.set_size(a.size() + b.size());
}

template <Sortable T>
void MergeSorter::Sort(DLinkedList<T> &ls) {
  if (ls.size() < 2) return;
  DLinkedList<T> b = ls.Subdivide();
  Sort(ls);
  Sort(b);
  Merge(ls, std::move(b));
}

}  // namespace rose
