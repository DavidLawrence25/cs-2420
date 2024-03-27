#include <memory>
#include <utility>

#include "custom_libraries/d_linked_list.h"

#ifndef CS2420_LABS_09MERGESORT_MERGESORTER_H_
#define CS2420_LABS_09MERGESORT_MERGESORTER_H_

namespace rose {

template <typename T>
concept Sortable = requires(T t, T u) {
  { t == u };  // Must be directly comparable.
  { t < u };   // Must have a sensible ordering.
};

class MergeSorter {
 public:
  // Merges sorted linked lists `a` and `b`, placing the sorted result in `a`.
  // Discards `b` entirely.
  template <Sortable T>
  static void Merge(DLinkedList<T> &a, DLinkedList<T> &&b);

  // Uses merge sort to recursively sort `ls` in-place.
  template <Sortable T>
  static void Sort(DLinkedList<T> &ls);
};

}  // namespace rose

#include "labs/09_merge_sort/merge_sorter.cc"

#endif  // CS2420_LABS_09MERGESORT_MERGESORTER_H_
