#include <iostream>

#include "../../custom_libraries/test.h"
#include "collection.h"

using rose::Collection, rose::TestCase, rose::TestResult;

class CollectionTest : public rose::TestCase {
 public:
  TestResult Run() {
    RunTest(TestAdd1, "TestAdd1");
    RunTest(TestAdd2, "TestAdd2");
    RunTest(TestAdd3, "TestAdd3");
    RunTest(TestItemAt1, "TestItemAt1");
    RunTest(TestItemAt2, "TestItemAt2");
    RunTest(TestItemAt3, "TestItemAt3");
    RunTest(TestRemoveEnd1, "TestRemoveEnd1");
    RunTest(TestRemoveEnd2, "TestRemoveEnd2");
    RunTest(TestRemoveEnd3, "TestRemoveEnd3");
    RunTest(TestRemoveEnd4, "TestRemoveEnd4");
    RunTest(TestExpand1, "TestExpand1");
    RunTest(TestExpand2, "TestExpand2");
    RunTest(TestExpand3, "TestExpand3");
    RunTest(TestExtract1, "TestExtract1");
    RunTest(TestExtract2, "TestExtract2");
    RunTest(TestExtract3, "TestExtract3");
    return result_;
  }

  void ResetGlobals() {
    // Not implemented; never used.
  }

  // Note: All these tests have intended side-effects and are therefore meant to
  // be run in the order they are defined.

  void TestAdd1() {
    nums_.Add(69);
    AssertEqual(nums_.length(), size_t{1}, "[69].length", "1");
  }

  void TestAdd2() {
    nums_.Add(42);
    nums_.Add(17);
    nums_.Add(21);
    AssertEqual(nums_.length(), size_t{4}, "[69, 42, 17, 21].length", "4");
  }

  void TestAdd3() {
    for (char c : "apple") {
      if (c) str_.Add(c);
    }
    AssertEqual(str_.length(), size_t{5}, "Collection(\"apple\").length", "5");
  }

  void TestItemAt1() {
    AssertEqual(nums_.ItemAt(0), 69, "[69, 42, 17, 21][0]", "69");
  }

  void TestItemAt2() {
    AssertEqual(nums_.ItemAt(-2), 17, "[69, 42, 17, 21][-2]", "17");
  }

  void TestItemAt3() {
    AssertEqual(str_.ItemAt(4), 'e', "Collection(\"apple\")[4]", "e");
  }

  void TestRemoveEnd1() {
    nums_.RemoveEnd();
    AssertEqual(nums_.length(), size_t{3}, "[69, 42, 17].length", "3");
  }

  void TestRemoveEnd2() {
    for (size_t i = 0; i < 3; ++i) nums_.RemoveEnd();
    AssertEqual(nums_.length(), size_t{0}, "[].length", "0");
  }

  void TestRemoveEnd3() {
    nums_.RemoveEnd();
    AssertEqual(nums_.length(), size_t{0}, "[].length (end removed)", "0");
  }

  void TestRemoveEnd4() {
    str_.RemoveEnd();
    AssertEqual(str_.length(), size_t{4}, "Collection(\"appl\").length", "4");
  }

  void TestExpand1() {
    for (int i = 0; i < 9; ++i) nums_.Add(i);
    AssertEqual(nums_.capacity(), size_t{16}, "[0, 1, 2, ..., 7, 8].capacity",
                "16");
  }

  void TestExpand2() {
    for (int i = 9; i < 65; ++i) nums_.Add(i);
    AssertEqual(nums_.capacity(), size_t{128},
                "[0, 1, 2, ..., 63, 64].capacity", "128");
  }

  void TestExpand3() {
    for (char c : "es taste pretty good") {
      if (c) str_.Add(c);
    }
    AssertEqual(str_.capacity(), size_t{32},
                "Collection(\"apples taste pretty good\").capacity", "32");
  }

  void TestExtract1() {
    std::stringstream expected;
    expected << '[';
    for (int i = 0; i < 64; ++i) expected << i << ", ";
    expected << "64]";
    std::stringstream sout;
    sout << nums_;
    AssertEqual(sout.str(), expected.str(), "Extracted [0, 1, 2, ..., 63, 64]",
                "[0, 1, 2, ..., 63, 64]");
  }

  void TestExtract2() {
    std::stringstream expected;
    expected << '[';
    for (char c : "apples taste pretty goo") {
      if (c) expected << c << ", ";
    }
    expected << "d]";
    std::stringstream sout;
    sout << str_;
    AssertEqual(sout.str(), expected.str(),
                "Extracted Collection(\"apples taste pretty good\")",
                "apples taste pretty good");
  }

  void TestExtract3() {
    std::string expected = "[]";
    while (str_.length()) str_.RemoveEnd();
    std::stringstream sout;
    sout << str_;
    AssertEqual(sout.str(), expected, "Extracted []", "[]");
  }

 private:
  Collection<int> nums_;
  Collection<char> str_;
};

int main() {
  CollectionTest test;
  TestResult results = test.Run();
  results.Report();

  return 0;
}
