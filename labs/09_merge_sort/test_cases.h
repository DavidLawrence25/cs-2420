#include <array>
#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/09_merge_sort/merge_sorter.h"

using rose::DLinkedList;
using rose::MergeSorter, rose::TestCase, rose::TestResult;

class MergeSortTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestFindMidOdd();
    TestFindMidEven();
    TestMerge();
    TestMergeSort();
  }

  void TestFindMidOdd() {
    DLinkedList<int> nums;
    for (int n : kNums) nums.PushBack(n);
    nums.PushBack(72);
    // I didn't write a method to find the middle, but there's a similar method
    // for subdividing it that can be used for the same purpose if you don't
    // mind the hacky solution.
    static_cast<void>(nums.Subdivide());
    ASSERT_EQUAL(nums.PeekBack().value_or(-1), 81);
  }

  void TestFindMidEven() {
    DLinkedList<int> nums;
    for (int n : kNums) nums.PushBack(n);
    static_cast<void>(nums.Subdivide());
    ASSERT_EQUAL(nums.PeekBack().value_or(-1), 97);
  }

  void TestMerge() {
    DLinkedList<int> a;
    for (int n : std::array<int, 4>{1, 3, 5, 7}) a.PushBack(n);
    DLinkedList<int> b;
    for (int n : std::array<int, 4>{2, 4, 6, 8}) b.PushBack(n);
    MergeSorter::Merge(a, std::move(b));
    std::stringstream sout;
    sout << a;
    ASSERT_EQUAL(sout.str(), std::string("1 2 3 4 5 6 7 8"));
  }

  void TestMergeSort() {
    DLinkedList<int> nums;
    for (int n : kNums) nums.PushBack(n);
    MergeSorter::Sort(nums);
    std::stringstream sout;
    sout << nums;
    ASSERT_EQUAL(sout.str(),
                 std::string("12 13 18 25 32 42 50 54 55 68 75 81 96 97"));
  }

 private:
  static constexpr std::array<int, 14> kNums = {50, 75, 25, 32, 55, 42, 97,
                                                81, 12, 96, 18, 68, 13, 54};
};
