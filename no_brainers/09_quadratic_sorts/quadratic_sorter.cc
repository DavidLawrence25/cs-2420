#include "no_brainers/09_quadratic_sorts/quadratic_sorter.h"

#include "custom_libraries/collection.h"
#include "quadratic_sorter.h"

namespace rose {

template <Sortable T>
int QuadraticSorter::IndexOfMinInRange(const Collection<T> &collection, int l,
                                       int r) {
  T min = collection[l];
  int index_of_min = l;
  for (int i = l + 1; i < r; ++i) {
    if (collection[i] < min) {
      min = collection[i];
      index_of_min = i;
    }
  }
  return index_of_min;
}

template <Sortable T>
int QuadraticSorter::ChooseInitPivotValue(Collection<T> &collection, int l,
                                          int r) {
  int m = l + ((r - l) >> 1);
  if (collection[m] < collection[l]) collection.Swap(l, m);
  if (collection[r] < collection[l]) collection.Swap(l, r);
  if (collection[m] < collection[r]) collection.Swap(m, r);
  return collection[r];
}

template <Sortable T>
int QuadraticSorter::Partition(Collection<T> &collection, int l, int r) {
  T pivot_value = ChooseInitPivotValue(collection, l, r);
  int i = l - 1;
  for (int j = l; j < r; ++j) {
    if (collection[j] <= pivot_value) collection.Swap(++i, j);
  }
  collection.Swap(++i, r);
  return i;
}

template <Sortable T>
void QuadraticSorter::InsertionSort(Collection<T> &collection) {
  for (int n = 1; n < collection.length(); ++n) {
    for (int i = 0; i < n; ++i) {
      if (collection[i] > collection[n]) {
        collection.Move(n, i);
        break;
      }
    }
  }
}

template <Sortable T>
void QuadraticSorter::BubbleSort(Collection<T> &collection) {
  for (int n = collection.length() - 1; n > 0; --n) {
    for (int i = 0; i < n; ++i) {
      if (collection[i] > collection[i + 1]) collection.Swap(i, i + 1);
    }
  }
}

template <Sortable T>
void QuadraticSorter::SelectionSort(Collection<T> &collection) {
  for (int i = 0; i < collection.length() - 1; ++i) {
    collection.Swap(i, IndexOfMinInRange(collection, i, collection.length()));
  }
}

template <Sortable T>
void QuadraticSorter::QuickSort(Collection<T> &collection) {
  QuickSort(collection, 0, collection.length() - 1);
}

template <Sortable T>
void QuadraticSorter::QuickSort(Collection<T> &collection, int l, int r) {
  if (l >= r || l < 0) return;
  int pivot = Partition(collection, l, r);
  QuickSort(collection, l, pivot - 1);
  QuickSort(collection, pivot + 1, r);
}

}  // namespace rose
