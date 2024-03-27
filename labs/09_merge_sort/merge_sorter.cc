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
  while (ptr_a && ptr_b) {
    if (ptr_a->data < ptr_b->data) {
      ptr_a = ptr_a->next;
      continue;
    }
    std::shared_ptr<DNode<T>> ptr_insert = ptr_b;
    if (ptr_b->previous) ptr_b->previous->next = ptr_b->next;
    if (ptr_b->next) ptr_b->next->previous = ptr_b->previous;
    ptr_b = ptr_b->next;
    a.Insert(ptr_insert, /*before=*/ptr_a);
  }
  if (ptr_a == nullptr) a.Insert(ptr_b, /*before=*/nullptr);
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
