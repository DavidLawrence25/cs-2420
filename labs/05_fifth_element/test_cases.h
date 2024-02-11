#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/05_fifth_element/fifth_element.h"

using rose::Assertion, rose::TestCase, rose::TestResult, rose::TestSuite;
using rose::FifthElement;

class FifthElementTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestPeekFifthIntOf10();
    TestPeekFifthIntOf5();
    TestPeekFifthIntOf4();
    TestPeekFifthStringOf10();
    TestInsertFifthIn10();
    TestInsertFifthIn5();
    TestInsertFifthIn4();
    TestInsertFifthIn3();
    TestEraseFifthOf10();
    TestEraseFifthOf6();
    TestEraseFifthOf5();
    TestEraseFifthOf4();
    TestSwapFourthAndFifth();
  }

  void TestPeekFifthIntOf10() {
    FifthElement<int> list;
    for (int x = 10; x < 20; ++x) list.PushBack(x);
    ASSERT_EQUAL(list.PeekFifth(), 14);
  }

  void TestPeekFifthIntOf5() {
    FifthElement<int> list;
    for (int x = 10; x < 15; ++x) list.PushBack(x);
    ASSERT_EQUAL(list.PeekFifth(), 14);
  }

  void TestPeekFifthIntOf4() {
    FifthElement<int> list;
    for (int x = 10; x < 14; ++x) list.PushBack(x);
    ASSERT_THROWS_AS(std::runtime_error, list.PeekFifth());
  }

  void TestPeekFifthStringOf10() {
    FifthElement<std::string> all_star;
    all_star.PushBack("somebody");
    all_star.PushBack("once");
    all_star.PushBack("told");
    all_star.PushBack("me");
    all_star.PushBack("the");
    all_star.PushBack("world");
    all_star.PushBack("is");
    all_star.PushBack("gonna");
    all_star.PushBack("roll");
    all_star.PushBack("me");
    ASSERT_EQUAL(all_star.PeekFifth(), std::string("the"));
  }

  void TestInsertFifthIn10() {
    FifthElement<int> list;
    for (int x = 10; x < 20; ++x) list.PushBack(x);
    list.InsertFifth(69);
    ASSERT_EQUAL(list.Peek(4).value(), 69);
  }

  void TestInsertFifthIn5() {
    FifthElement<int> list;
    for (int x = 10; x < 15; ++x) list.PushBack(x);
    list.InsertFifth(420);
    ASSERT_EQUAL(list.Peek(4).value(), 420);
  }

  void TestInsertFifthIn4() {
    FifthElement<int> list;
    for (int x = 10; x < 14; ++x) list.PushBack(x);
    list.InsertFifth(42);
    ASSERT_EQUAL(list.Peek(4).value(), 42);
  }

  void TestInsertFifthIn3() {
    FifthElement<int> list;
    for (int x = 10; x < 13; ++x) list.PushBack(x);
    list.InsertFifth(7);
    ASSERT_FALSE(list.Peek(4).has_value());
  }

  void TestEraseFifthOf10() {
    FifthElement<int> list;
    for (int x = 10; x < 20; ++x) list.PushBack(x);
    list.EraseFifth();
    ASSERT_EQUAL(list.Peek(4).value(), 15);
  }

  void TestEraseFifthOf6() {
    FifthElement<int> list;
    for (int x = 10; x < 16; ++x) list.PushBack(x);
    list.EraseFifth();
    ASSERT_EQUAL(list.Peek(4).value(), 15);
  }

  void TestEraseFifthOf5() {
    FifthElement<int> list;
    for (int x = 10; x < 15; ++x) list.PushBack(x);
    list.EraseFifth();
    ASSERT_FALSE(list.Peek(4).has_value());
  }

  void TestEraseFifthOf4() {
    FifthElement<int> list;
    for (int x = 10; x < 14; ++x) list.PushBack(x);
    std::stringstream before_erase;
    before_erase << list;
    list.EraseFifth();
    std::stringstream after_erase;
    after_erase << list;
    ASSERT_EQUAL(before_erase.str(), after_erase.str());
  }

  void TestSwapFourthAndFifth() {
    FifthElement<int> list;
    for (int x = 10; x < 20; ++x) list.PushBack(x);
    list.SwapFourthAndFifth();
    std::stringstream after_swap;
    after_swap << list;
    ASSERT_EQUAL(after_swap.str(),
                 std::string("10 11 12 14 13 15 16 17 18 19"));
  }
};
