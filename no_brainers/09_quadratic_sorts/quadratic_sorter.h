#include "custom_libraries/collection.h"

#ifndef CS2420_NOBRAINERS_09QUADRATICSORTS_QUADRATICSORTER_H_
#define CS2420_NOBRAINERS_09QUADRATICSORTS_QUADRATICSORTER_H_

namespace rose {

template <typename T>
concept Sortable = requires(T t, T u) {
  { t == u };  // Must be directly comparable.
  { t < u };   // Must have a sensible ordering.
};

// Sorts collections using various quadratic sorting algorithms.
class QuadraticSorter {
 public:
  // Returns the index of the minimum value in the range of indices `[l, r)`.
  template <Sortable T>
  static int IndexOfMinInRange(const Collection<T> &collection, int l, int r);

  // Given the interval `[l, r]`, returns a corresponding value in `collection`
  // to use as a pivot. The values `collection[l]`,
  // `collection[floor((l + r) / 2)]`, and `collection[r]` may be shuffled
  // around to place the median at index `r`.
  template <Sortable T>
  static int ChooseInitPivotValue(Collection<T> &collection, int l, int r);

  // Given the interval `[l, r]`, partitions the corresponding values such that
  // all values to the left of the pivot are less than or equal to the pivot and
  // all values to the right are greater than or equal to it. Pivots and swaps
  // are chosen by Lomuto's partition scheme. Returns the pivot index once
  // complete. Example (with `l=1`, `r=6`):
  //   Before: `[6, 5, 3, 1, 8, 7, 2, 4, 9]`
  //   After:  `[6, 1, 2, 3, 8, 7, 5, 4, 9]`
  //                      ^
  //                    Pivot
  template <Sortable T>
  static int Partition(Collection<T> &collection, int l, int r);

  // Sorts `collection` in non-descending order via insertion sort.
  // Time Complexity: O(n ** 2)
  // Space Complexity: O(1)
  // Stable: Yes
  template <Sortable T>
  static void InsertionSort(Collection<T> &collection);

  // Sorts `collection` in non-descending order via bubble sort.
  // Time Complexity: O(n ** 2)
  // Space Complexity: O(1)
  // Stable: Yes
  template <Sortable T>
  static void BubbleSort(Collection<T> &collection);

  // Sorts `collection` in non-descending order via selection sort.
  // Time Complexity: O(n ** 2)
  // Space Complexity: O(1)
  // Stable: Yes
  template <Sortable T>
  static void SelectionSort(Collection<T> &collection);

  // Sorts `collection` in non-descending order via QuickSort.
  // Time Complexity: O(n log n) - O(n ** 2)
  // Space Complexity: O(log n)
  // Stable: No
  template <Sortable T>
  static void QuickSort(Collection<T> &collection);

  // Sorts the portion of `collection` with indices on the interval `[l, r]` in
  // non-descending order via QuickSort.
  // Time Complexity: O(n log n) - O(n ** 2)
  // Space Complexity: O(log n)
  // Stable: No
  template <Sortable T>
  static void QuickSort(Collection<T> &collection, int l, int r);
};

}  // namespace rose

#include "no_brainers/09_quadratic_sorts/quadratic_sorter.cc"

#endif  // CS2420_NOBRAINERS_09QUADRATICSORTS_QUADRATICSORTER_H_
