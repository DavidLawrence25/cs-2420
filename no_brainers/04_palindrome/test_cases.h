#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/04_palindrome/palindrome.h"

using rose::Palindrome, rose::TestCase, rose::TestResult;

class PalindromeTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestEasy();
    TestSpaces();
    TestMixedCase();
    TestPunctuation();
    TestNotPalindrome();
  }

  void TestEasy() {
    Palindrome palindrome = {/*sentence=*/"mom"};
    ASSERT_TRUE(palindrome.is_palindrome());
  }

  void TestSpaces() {
    Palindrome palindrome = {/*sentence=*/"taco cat"};
    ASSERT_TRUE(palindrome.is_palindrome());
  }

  void TestMixedCase() {
    Palindrome palindrome = {/*sentence=*/"A man a plan a canal Panama"};
    ASSERT_TRUE(palindrome.is_palindrome());
  }

  void TestPunctuation() {
    Palindrome palindrome = {/*sentence=*/"Don't nod."};
    ASSERT_TRUE(palindrome.is_palindrome());
  }

  void TestNotPalindrome() {
    Palindrome not_palindrome = {/*sentence=*/"madams"};
    ASSERT_FALSE(not_palindrome.is_palindrome());
  }
};
