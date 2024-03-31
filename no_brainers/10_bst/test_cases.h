#include <stdlib.h>

#include <array>
#include <sstream>
#include <string>

#include "custom_libraries/bst.h"
#include "custom_libraries/unit_test/unit_test.h"

using rose::BST;
using rose::TestCase, rose::TestResult;

class BasicBSTTest : public TestCase {
 public:
  BasicBSTTest() { Repair(); }
  void Repair() override {
    tree_ = BST<int>();
    for (int n : kNums) tree_.Insert(n);
  }

  void Run() override {
    TestNumNodes();
    TestNumLeaves();
    TestExtractPreOrder();
    TestExtractInOrder();
    TestExtractPostOrder();
  }

  void TestNumNodes() { ASSERT_EQUAL(tree_.GetNumNodes(), size_t{35}); }
  void TestNumLeaves() { ASSERT_EQUAL(tree_.GetNumLeaves(), size_t{11}); }

  void TestExtractPreOrder() {
    std::stringstream sout;
    tree_.ExtractPreOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string(
            "37 32 12 0 7 5 3 27 17 15 13 25 23 35 33 73 42 49 47 45 43 "
            "67 55 53 65 63 95 87 77 75 85 83 93 98 97 "));
  }

  void TestExtractInOrder() {
    std::stringstream sout;
    tree_.ExtractInOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("0 3 5 7 12 13 15 17 23 25 27 32 33 35 37 42 43 45 47 49 "
                    "53 55 63 65 67 73 75 77 83 85 87 93 95 97 98 "));
  }

  void TestExtractPostOrder() {
    std::stringstream sout;
    tree_.ExtractPostOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("3 5 7 0 13 15 25 23 17 27 12 33 35 32 43 45 47 53 63 65 "
                    "55 67 49 42 75 83 85 77 93 87 97 98 95 73 37 "));
  }

 private:
  static constexpr std::array<int, 35> kNums = {
      37, 32, 73, 95, 42, 12, 0,  49, 98, 7,  27, 17, 47, 87, 77, 97, 67, 85,
      15, 5,  35, 55, 65, 75, 25, 45, 3,  93, 83, 53, 63, 23, 13, 43, 33};
  BST<int> tree_;
};
