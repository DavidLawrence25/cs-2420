#include <sstream>
#include <string>

#include "custom_libraries/collection.h"
#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/09_quadratic_sorts/quadratic_sorter.h"

using rose::Collection, rose::QuadraticSorter, rose::TestCase, rose::TestResult;

class QuadraticSortsTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestSimpleSwap();
    TestInsertionSort();
    TestBubbleSort();
    TestSelectionSort();
    TestPivot();
    TestPartition();
    TestQuickSort();
  }

  void TestSimpleSwap() {
    Collection<int> nums;
    for (int x = 2; x < 6; ++x) nums.Add(x);
    nums.Swap(1, 2);
    std::stringstream sout;
    sout << nums;
    ASSERT_EQUAL(sout.str(), std::string("[2, 4, 3, 5]"));
  }

  void TestInsertionSort() {
    Collection<char> msg;
    for (char c : "insertionsort") {
      if (c == '\0') break;
      msg.Add(c);
    }
    QuadraticSorter::InsertionSort(msg);
    std::stringstream sout;
    sout << msg;
    ASSERT_EQUAL(sout.str(),
                 std::string("[e, i, i, n, n, o, o, r, r, s, s, t, t]"));
  }

  void TestBubbleSort() {
    Collection<char> msg;
    for (char c : "bubblesort") {
      if (c == '\0') break;
      msg.Add(c);
    }
    QuadraticSorter::BubbleSort(msg);
    std::stringstream sout;
    sout << msg;
    ASSERT_EQUAL(sout.str(), std::string("[b, b, b, e, l, o, r, s, t, u]"));
  }

  void TestSelectionSort() {
    Collection<char> msg;
    for (char c : "selectionsortseemsinefficient") {
      if (c == '\0') break;
      msg.Add(c);
    }
    QuadraticSorter::SelectionSort(msg);
    std::stringstream sout;
    sout << msg;
    ASSERT_EQUAL(sout.str(),
                 std::string("[c, c, e, e, e, e, e, e, f, f, i, i, i, i, l, m, "
                             "n, n, n, o, o, r, s, s, s, s, t, t, t]"));
  }

  void TestPivot() {
    Collection<int> nums;
    for (int x : std::array<int, 10>{99, 99, 5, 2, 6, 3, 7, 4, 90, 91}) {
      nums.Add(x);
    }
    int pivot_index = QuadraticSorter::Partition(nums, 2, 7);
    ASSERT_EQUAL(nums[pivot_index], 5);
  }

  void TestPartition() {
    Collection<int> nums;
    for (int x : std::array<int, 10>{99, 99, 5, 2, 6, 3, 7, 4, 90, 91}) {
      nums.Add(x);
    }
    static_cast<void>(QuadraticSorter::Partition(nums, 2, 7));
    std::stringstream sout;
    sout << nums;
    ASSERT_EQUAL(sout.str(), std::string("[99, 99, 4, 2, 3, 5, 7, 6, 90, 91]"));
  }

  void TestQuickSort() {
    Collection<char> msg;
    for (char c : "nlognquicksortismoreefficient") {
      if (c == '\0') break;
      msg.Add(c);
    }
    QuadraticSorter::QuickSort(msg);
    std::stringstream sout;
    sout << msg;
    ASSERT_EQUAL(sout.str(),
                 std::string("[c, c, e, e, e, f, f, g, i, i, i, i, k, l, m, n, "
                             "n, n, o, o, o, q, r, r, s, s, t, t, u]"));
  }
};
