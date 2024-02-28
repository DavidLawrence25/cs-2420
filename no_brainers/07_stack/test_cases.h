#include <stdlib.h>

#include <memory>
#include <optional>
#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/07_stack/stack.h"

using rose::Stack, rose::TestCase, rose::TestResult;

class StackSizeTest : public TestCase {
 public:
  void Repair() override { stack_ = Stack<int>(); }
  void Run() override {
    TestEmpty();
    TestNotEmpty();
    TestWasntEmptyBefore();
    TestSizeOf0();
    TestSizeOf2();
    TestSizeOf5();
  }

  void TestEmpty() { ASSERT_TRUE(stack_.empty()); }

  void TestNotEmpty() {
    stack_.Push(69);
    ASSERT_FALSE(stack_.empty());
    Repair();
  }

  void TestWasntEmptyBefore() {
    for (int n = 0; n < 4; ++n) stack_.Push(n);
    stack_.Clear();
    ASSERT_TRUE(stack_.empty());
    Repair();  // Redundant if the test passes.
  }

  void TestSizeOf0() { ASSERT_EQUAL(stack_.size(), size_t{0}); }

  void TestSizeOf2() {
    stack_.Push(12);
    stack_.Push(32);
    ASSERT_EQUAL(stack_.size(), size_t{2});
    Repair();
  }

  void TestSizeOf5() {
    stack_.Push(12);
    stack_.Push(32);
    stack_.Push(14);
    stack_.Push(53);
    stack_.Push(47);
    ASSERT_EQUAL(stack_.size(), size_t{5});
  }

 private:
  Stack<int> stack_;
};

class BasicStackTest : public TestCase {
 public:
  void Repair() override { stack_ = Stack<int>(); }

  void Run() override {
    TestPush1();
    TestPush5();
    TestPush16AndPop12();
    TestStreamExtraction();
  }

  void TestPush1() {
    stack_.Push(1);
    ASSERT_EQUAL(stack_.top().value_or(-1), 1);
    Repair();
  }

  void TestPush5() {
    for (int n = 1; n < 6; ++n) stack_.Push(n);
    ASSERT_EQUAL(stack_.top().value_or(-1), 5);
    Repair();
  }

  void TestPush16AndPop12() {
    for (int n = 1; n < 17; ++n) stack_.Push(n);
    for (int _ = 0; _ < 12; ++_) stack_.Pop();
    ASSERT_EQUAL(stack_.top().value_or(-1), 4);
    Repair();
  }

  void TestStreamExtraction() {
    for (int n = 1; n < 17; ++n) stack_.Push(n);
    std::stringstream sout;
    sout << stack_;
    ASSERT_EQUAL(sout.str(),
                 std::string("16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1"));
    Repair();
  }

 private:
  Stack<int> stack_;
};

class StringStackTest : public TestCase {
 public:
  StringStackTest() { Repair(); }

  void Repair() override {
    stack_ = Stack<std::string>();
    stack_.Push("pencil");
    stack_.Push("pen");
    stack_.Push("marker");
  }

  void Run() override {
    TestSizeOf3();
    TestPopPopReplace();
    TestPopPopReplacePop();
    TestClear();
  }

  void TestSizeOf3() { ASSERT_EQUAL(stack_.size(), size_t{3}); }

  void TestPopPopReplace() {
    std::string marker = stack_.top().value();  // I'm assuming it has a value.
    stack_.Pop();
    stack_.Pop();
    stack_.Push(marker);
    ASSERT_EQUAL(stack_.top().value_or("you messed up"), marker);
    Repair();
  }

  void TestPopPopReplacePop() {
    std::string marker = stack_.top().value();
    stack_.Pop();
    stack_.Pop();
    stack_.Push(marker);
    stack_.Pop();
    ASSERT_EQUAL(stack_.top().value_or("you messed up"), std::string("pencil"));
    Repair();
  }

  void TestClear() {
    stack_.Clear();
    ASSERT_TRUE(stack_.empty());
    Repair();
  }

 private:
  Stack<std::string> stack_;
};

class BadStackUseTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override { TestReadEmpty(); }

  void TestReadEmpty() { ASSERT_FALSE(stack_.top().has_value()); }

 private:
  Stack<int> stack_;
};
