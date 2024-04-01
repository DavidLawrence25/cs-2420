#include <sstream>
#include <string>

#include "custom_libraries/bst.h"
#include "custom_libraries/unit_test/unit_test.h"

using rose::BST, rose::BSTParentChildPair;
using rose::TestCase, rose::TestResult;

class HardBSTTest : public TestCase {
 public:
  HardBSTTest() { Repair(); }
  void Repair() override {
    tree_ = BST<int>();
    for (int n : kNums) tree_.Insert(n);
  }

  void Run() override {
    TestContains49();
    TestDoesntContain200();
    TestRightmostDescendantOf49();
    TestFindParentOf25();
    TestFindParentOf15();
    tree_.Remove(13);
    TestRemoveLeaf();
    TestOrderAfterRemoveLeaf();
    Repair();
    tree_.Remove(67);
    TestRemoveParentOfLeft();
    TestOrderAfterRemoveParentOfLeft();
    TestContains55AfterRemoveParentOfLeft();
    Repair();
    tree_.Remove(42);
    TestRemoveParentOfRight();
    TestOrderAfterRemoveParentOfRight();
    TestContains55AfterRemoveParentOfRight();
    Repair();
    tree_.Remove(73);
    TestRemoveParentOfBoth();
    TestOrderAfterRemoveParentOfBoth();
    TestContains49AfterRemoveParentOfBoth();
    TestContains95AfterRemoveParentOfBoth();
    TestContains63AfterRemoveParentOfBoth();
    Repair();
    tree_.Remove(37);
    TestRemoveRoot();
    TestOrderAfterRemoveRoot();
    TestContains32AfterRemoveRoot();
    TestContains95AfterRemoveRoot();
    Repair();
  }

  void TestContains49() { ASSERT_TRUE(tree_.Contains(49)); }
  void TestDoesntContain200() { ASSERT_FALSE(tree_.Contains(200)); }

  void TestRightmostDescendantOf49() {
    BSTParentChildPair<int> pair = tree_.FindWithParent(49);
    pair.AdvanceGenerationRightward();
    BST<int>::pointer result = tree_.FindRightWithParent(pair).child;
    ASSERT_EQUAL(result ? result->data : -1, 67);
  }

  void TestFindParentOf25() {
    // You could use FindParent directly, but it just dereferences the pointer
    // you pass in to execute basically the same code, and you'd have to obtain
    // the pointer to the 25 node anyway, so...
    BST<int>::pointer result = tree_.FindWithParent(25).parent;
    ASSERT_EQUAL(result ? result->data : -1, 17);
  }

  void TestFindParentOf15() {
    BST<int>::pointer result = tree_.FindWithParent(15).parent;
    ASSERT_EQUAL(result ? result->data : -1, 17);
  }

  void TestRemoveLeaf() { ASSERT_FALSE(tree_.Contains(13)); }

  void TestOrderAfterRemoveLeaf() {
    std::stringstream sout;
    tree_.ExtractInOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("0 3 5 7 12 15 17 23 25 27 32 33 35 37 42 43 45 47 49 "
                    "53 55 63 65 67 73 75 77 83 85 87 93 95 97 98"));
  }

  void TestRemoveParentOfLeft() { ASSERT_FALSE(tree_.Contains(67)); }

  void TestOrderAfterRemoveParentOfLeft() {
    std::stringstream sout;
    tree_.ExtractInOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("0 3 5 7 12 13 15 17 23 25 27 32 33 35 37 42 43 45 47 49 "
                    "53 55 63 65 73 75 77 83 85 87 93 95 97 98"));
  }

  void TestContains55AfterRemoveParentOfLeft() {
    ASSERT_TRUE(tree_.Contains(55));
  }

  void TestRemoveParentOfRight() { ASSERT_FALSE(tree_.Contains(42)); }

  void TestOrderAfterRemoveParentOfRight() {
    std::stringstream sout;
    tree_.ExtractInOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("0 3 5 7 12 13 15 17 23 25 27 32 33 35 37 43 45 47 49 "
                    "53 55 63 65 67 73 75 77 83 85 87 93 95 97 98"));
  }

  void TestContains55AfterRemoveParentOfRight() {
    ASSERT_TRUE(tree_.Contains(55));
  }

  void TestRemoveParentOfBoth() { ASSERT_FALSE(tree_.Contains(73)); }

  void TestOrderAfterRemoveParentOfBoth() {
    std::stringstream sout;
    tree_.ExtractInOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("0 3 5 7 12 13 15 17 23 25 27 32 33 35 37 42 43 45 47 49 "
                    "53 55 63 65 67 75 77 83 85 87 93 95 97 98"));
  }

  void TestContains49AfterRemoveParentOfBoth() {
    ASSERT_TRUE(tree_.Contains(49));
  }

  void TestContains95AfterRemoveParentOfBoth() {
    ASSERT_TRUE(tree_.Contains(95));
  }

  void TestContains63AfterRemoveParentOfBoth() {
    ASSERT_TRUE(tree_.Contains(63));
  }

  void TestRemoveRoot() { ASSERT_FALSE(tree_.Contains(37)); }

  void TestOrderAfterRemoveRoot() {
    std::stringstream sout;
    tree_.ExtractInOrder(sout);
    ASSERT_EQUAL(
        sout.str(),
        std::string("0 3 5 7 12 13 15 17 23 25 27 32 33 35 42 43 45 47 49 "
                    "53 55 63 65 67 73 75 77 83 85 87 93 95 97 98"));
  }

  void TestContains32AfterRemoveRoot() { ASSERT_TRUE(tree_.Contains(32)); }
  void TestContains95AfterRemoveRoot() { ASSERT_TRUE(tree_.Contains(95)); }

 private:
  static constexpr std::array<int, 35> kNums = {
      37, 32, 73, 95, 42, 12, 0,  49, 98, 7,  27, 17, 47, 87, 77, 97, 67, 85,
      15, 5,  35, 55, 65, 75, 25, 45, 3,  93, 83, 53, 63, 23, 13, 43, 33};
  BST<int> tree_;
};
