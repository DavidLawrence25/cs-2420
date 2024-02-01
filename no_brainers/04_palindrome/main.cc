#include "../../custom_libraries/test.h"
#include "palindrome.h"

using rose::NoGlobals, rose::Palindrome, rose::TestCase, rose::TestResult;

class PalindromeTest : public TestCase<NoGlobals> {
 public:
  TestResult Run() {
    RunTest(TestEasy, "TestEasy");
    RunTest(TestSpaces, "TestSpaces");
    RunTest(TestMixedCase, "TestMixedCase");
    RunTest(TestPunctuation, "TestPunctuation");
    RunTest(TestNotPalindrome, "TestNotPalindrome");
    return result_;
  }

  void TestEasy() {
    Palindrome palindrome = {/*sentence=*/"mom"};
    AddValueSet(/*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"palindrome", /*value=*/"Palindrome(\"mom\")");
    AssertTrue(palindrome.is_palindrome(),
               /*repr=*/"palindrome.is_palindrome()",
               /*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{});
  }

  void TestSpaces() {
    Palindrome palindrome = {/*sentence=*/"taco cat"};
    AddValueSet(/*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"palindrome",
                /*value=*/"Palindrome(\"taco cat\")");
    AssertTrue(palindrome.is_palindrome(),
               /*repr=*/"palindrome.is_palindrome()",
               /*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{});
  }

  void TestMixedCase() {
    Palindrome palindrome = {/*sentence=*/"A man a plan a canal Panama"};
    AddValueSet(/*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"palindrome",
                /*value=*/"Palindrome(\"A man a plan a canal Panama\")");
    AssertTrue(palindrome.is_palindrome(),
               /*repr=*/"palindrome.is_palindrome()",
               /*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{});
  }

  void TestPunctuation() {
    Palindrome palindrome = {/*sentence=*/"Don't nod."};
    AddValueSet(/*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"palindrome",
                /*value=*/"Palindrome(\"Don't nod.\")");
    AssertTrue(palindrome.is_palindrome(),
               /*repr=*/"palindrome.is_palindrome()",
               /*relevant_locals=*/{"palindrome"}, /*relevant_globals=*/{});
  }

  void TestNotPalindrome() {
    Palindrome not_palindrome = {/*sentence=*/"madams"};
    AddValueSet(/*relevant_locals=*/{"not_palindrome"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"not_palindrome",
                /*value=*/"Palindrome(\"madams\")");
    AssertFalse(not_palindrome.is_palindrome(),
                /*repr=*/"not_palindrome.is_palindrome()",
                /*relevant_locals=*/{"not_palindrome"},
                /*relevant_globals=*/{});
  }
};

int main() {
  PalindromeTest test;
  TestResult results = test.Run();
  results.LogJson("test_log");

  return 0;
}
