#include <iostream>
#include <memory>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/04_palindrome/palindrome.h"

using rose::CommandLineFlags;
using rose::Palindrome, rose::TestCase, rose::TestResult, rose::TestSuite;

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

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<PalindromeTest>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
