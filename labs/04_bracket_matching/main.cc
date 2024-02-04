#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/04_bracket_matching/bracket_check.h"

using rose::BracketCheck, rose::TestCase, rose::TestResult, rose::TestSuite;
using rose::CommandLineFlags;

class BracketTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    Test1Pair();
    TestMismatchedPair();
    TestBackwards();
    TestValidMix();
    TestExtraClosing();
    TestPulledApart();
    TestExtraOpening();
    TestValidCode();
    TestInvalidCode();
    TestHugeYetValidMess();
    TestCount3IndependentPairs();
    TestCount4NestedPairs();
    TestValidStreamExtraction();
    TestInvalidStreamExtraction();
  }

  void Test1Pair() {
    BracketCheck check = {"()"};
    ASSERT_TRUE(check.is_balanced());
  }

  void TestMismatchedPair() {
    BracketCheck check = {"(}"};
    ASSERT_FALSE(check.is_balanced());
  }

  void TestBackwards() {
    BracketCheck check = {")("};
    ASSERT_FALSE(check.is_balanced());
  }

  void TestValidMix() {
    BracketCheck check = {"({}[])"};
    ASSERT_TRUE(check.is_balanced());
  }

  void TestExtraClosing() {
    BracketCheck check = {"({}[])]"};
    ASSERT_FALSE(check.is_balanced());
  }

  void TestPulledApart() {
    BracketCheck check = {"({)(})"};
    ASSERT_FALSE(check.is_balanced());
  }

  void TestExtraOpening() {
    BracketCheck check = {"{()"};
    ASSERT_FALSE(check.is_balanced());
  }

  void TestValidCode() {
    BracketCheck check = {"if (x > 7) { std::cout << x; }"};
    ASSERT_TRUE(check.is_balanced());
  }

  void TestInvalidCode() {
    BracketCheck check = {"if (x > 7) std::cout << x; }"};
    ASSERT_FALSE(check.is_balanced());
  }

  void TestHugeYetValidMess() {
    BracketCheck check = {"[([[]]{()()}){}](){[]}"};
    ASSERT_TRUE(check.is_balanced());
  }

  void TestCount3IndependentPairs() {
    BracketCheck check = {"()[]{}"};
    ASSERT_EQUAL(check.pairs().value(), 3);
  }

  void TestCount4NestedPairs() {
    BracketCheck check = {"({}[()])"};
    ASSERT_EQUAL(check.pairs().value(), 4);
  }

  void TestValidStreamExtraction() {
    BracketCheck check = {"[]()"};
    std::stringstream sout;
    sout << check;
    ASSERT_EQUAL(sout.str(), std::string("Balanced"));
  }

  void TestInvalidStreamExtraction() {
    BracketCheck check = {"{"};
    std::stringstream sout;
    sout << check;
    ASSERT_EQUAL(sout.str(), std::string("Not Balanced"));
  }
};

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<BracketTest>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
