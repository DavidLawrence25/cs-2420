#include "custom_libraries/unit_test/unit_test.h"
#include "labs/06_recursion/subsequence.h"

using rose::Subsequence, rose::TestCase, rose::TestResult;

class EmptySubsequenceTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestEmpty();
    TestChar();
    TestWord();
    TestSentence();
  }

  void TestEmpty() { ASSERT_TRUE(subsequence_.IsSubsequence("")); }
  void TestChar() { ASSERT_FALSE(subsequence_.IsSubsequence("a")); }
  void TestWord() { ASSERT_FALSE(subsequence_.IsSubsequence("pineapple")); }
  void TestSentence() { ASSERT_FALSE(subsequence_.IsSubsequence("She died.")); }

 private:
  Subsequence subsequence_ = Subsequence();
};

class ProgrammingSubsequenceTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestUppercasePin();
    TestLowercasePin();
  }

  void TestUppercasePin() { ASSERT_TRUE(subsequence_.IsSubsequence("Pin")); }
  void TestLowercasePin() { ASSERT_FALSE(subsequence_.IsSubsequence("pin")); }

 private:
  Subsequence subsequence_ = Subsequence("Programming");
};

class AbcdeSubsequenceTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestAce();
    TestBad();
    TestAxe();
    TestTooLong();
  }

  void TestAce() { ASSERT_TRUE(subsequence_.IsSubsequence("ace")); }
  void TestBad() { ASSERT_FALSE(subsequence_.IsSubsequence("bad")); }
  void TestAxe() { ASSERT_FALSE(subsequence_.IsSubsequence("axe")); }
  void TestTooLong() { ASSERT_FALSE(subsequence_.IsSubsequence("abcdef")); }

 private:
  Subsequence subsequence_ = Subsequence("abcde");
};
