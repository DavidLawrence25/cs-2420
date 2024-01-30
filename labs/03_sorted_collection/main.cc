#include <format>
#include <iostream>

#include "../../custom_libraries/test.h"
#include "sorted_collection.h"

using rose::SortedCollection, rose::TestCase, rose::TestResult;

class CollectionIntTest : public rose::TestCase<SortedCollection<int>> {
 public:
  CollectionIntTest() {
    AddGlobal("nums", {&nums_, nums_, "SortedCollection<int>()"});
  }

  TestResult Run() {
    RunTest(TestAdd1, "TestAdd1");
    RunTest(TestAdd2, "TestAdd2");
    RunTest(TestItemAt1, "TestItemAt1");
    RunTest(TestItemAt2, "TestItemAt2");
    RunTest(TestRemoveEnd1, "TestRemoveEnd1");
    RunTest(TestRemoveEnd2, "TestRemoveEnd2");
    RunTest(TestRemoveEnd3, "TestRemoveEnd3");
    RunTest(TestExpand1, "TestExpand1");
    RunTest(TestExpand2, "TestExpand2");
    RunTest(TestExtract, "TestExtract");
    return result_;
  }

  // Note: All these tests have intended side-effects and are therefore meant to
  // be run in the order they are defined.

  void TestAdd1() {
    nums_.Add(69);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                /*repr=*/"nums.Add(69)");
    AssertEqual(nums_.length(), size_t{1}, /*repr0=*/"nums.length",
                /*repr1=*/"1", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestAdd2() {
    for (int x : std::vector<int>({42, 17, 21})) {
      nums_.Add(x);
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                  /*repr=*/std::format("nums.Add({})", x));
    }
    AssertEqual(nums_.length(), size_t{4}, /*repr0=*/"nums.length",
                /*repr1=*/"4", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestItemAt1() {
    AssertEqual(nums_.ItemAt(0), 17, /*repr0=*/"nums.ItemAt(0)",
                /*repr1=*/"17", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestItemAt2() {
    AssertEqual(nums_.ItemAt(-2), 42, /*repr0=*/"nums.ItemAt(-2)",
                /*repr1=*/"42", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestRemoveEnd1() {
    nums_.RemoveEnd();
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                /*repr=*/"nums.RemoveEnd()");
    AssertEqual(nums_.length(), size_t{3}, /*repr0=*/"nums.length",
                /*repr1=*/"3", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestRemoveEnd2() {
    for (size_t i = 0; i < 3; ++i) {
      nums_.RemoveEnd();
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                  /*repr=*/"nums.RemoveEnd()");
    }
    AssertEqual(nums_.length(), size_t{0}, /*repr0=*/"nums.length",
                /*repr1=*/"0", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestRemoveEnd3() {
    nums_.RemoveEnd();
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                /*repr=*/"nums.RemoveEnd()");
    AssertEqual(nums_.length(), size_t{0}, /*repr0=*/"nums.length",
                /*repr1=*/"0", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestExpand1() {
    for (int i = 0; i < 9; ++i) {
      nums_.Add(i);
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                  /*repr=*/std::format("nums.Add({})", i));
    }
    AssertEqual(nums_.capacity(), size_t{16}, /*repr0=*/"nums.capacity",
                /*repr1=*/"16", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestExpand2() {
    for (int i = 9; i < 65; ++i) {
      nums_.Add(i);
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"nums"},
                  /*repr=*/std::format("nums.Add({})", i));
    }
    AssertEqual(nums_.capacity(), size_t{128}, /*repr0=*/"nums.capacity",
                /*repr1=*/"128", /*relevant_locals=*/{},
                /*relevant_globals=*/{"nums"});
  }

  void TestExtract() {
    std::stringstream expected;
    AddValueSet(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"expected", /*value=*/"std::stringstream()");
    expected << '[';
    AddFuncCall(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*repr=*/"operator<<(expected, '[')");
    for (int i = 0; i < 64; ++i) {
      expected << i << ", ";
      AddFuncCall(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                  /*repr=*/std::format("operator<<(expected, \"{}, \")", i));
    }
    expected << "64]";
    AddFuncCall(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*repr=*/"operator<<(expected, \"64]\")");
    std::stringstream sout;
    AddValueSet(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"sout", /*value=*/"std::stringstream()");
    sout << nums_;
    AddFuncCall(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{"nums"},
                /*repr=*/"operator<<(sout, nums)");
    AssertEqual(sout.str(), expected.str(), /*repr0=*/"sout.str()",
                /*repr1=*/"expected.str()",
                /*relevant_locals=*/{"expected", "sout"},
                /*relevant_globals=*/{});
  }

 private:
  SortedCollection<int> nums_;
};

class CollectionCharTest : public TestCase<SortedCollection<char>> {
 public:
  CollectionCharTest() {
    AddGlobal("str", {&str_, str_, "SortedCollection<char>()"});
  }

  TestResult Run() {
    RunTest(TestAdd, "TestAdd");
    RunTest(TestItemAt, "TestItemAt");
    RunTest(TestRemoveEnd, "TestRemoveEnd");
    RunTest(TestExpand, "TestExpand");
    RunTest(TestExtract1, "TestExtract1");
    RunTest(TestExtract2, "TestExtract2");
    return result_;
  }

  // Note: All these tests have intended side-effects and are therefore meant to
  // be run in the order they are defined.

  void TestAdd() {
    for (char c : "apple") {
      if (c == '\0') break;
      str_.Add(c);
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"str"},
                  /*repr=*/std::format("str.Add({})", c));
    }
    AssertEqual(str_.length(), size_t{5}, /*repr0=*/"str.length", /*repr1=*/"5",
                /*relevant_locals=*/{}, /*relevant_globals=*/{"str"});
  }

  void TestItemAt() {
    AssertEqual(str_.ItemAt(4), 'p', /*repr0=*/"str.ItemAt(4)", /*repr1=*/"p",
                /*relevant_locals=*/{}, /*relevant_globals=*/{"str"});
  }

  void TestRemoveEnd() {
    str_.RemoveEnd();
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"str"},
                /*repr=*/"str.RemoveEnd()");
    AssertEqual(str_.length(), size_t{4}, /*repr0=*/"str.length", /*repr1=*/"4",
                /*relevant_locals=*/{}, /*relevant_globals=*/{"str"});
  }

  void TestExpand() {
    for (char c : "ps taste pretty good") {
      if (c == '\0') break;
      str_.Add(c);
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"str"},
                  /*repr=*/std::format("str.Add({})", c));
    }
    AssertEqual(str_.capacity(), size_t{32}, /*repr0=*/"str.capacity",
                /*repr1=*/"32", /*relevant_locals=*/{},
                /*relevant_globals=*/{"str"});
  }

  void TestExtract1() {
    std::stringstream expected;
    AddValueSet(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"expected", /*value=*/"std::stringstream()");
    expected << '[';
    AddFuncCall(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*repr=*/"operator<<(expected, '[')");
    // apples taste pretty good
    for (char c : "   aadeeeglooppprsstttt") {
      if (c == '\0') break;
      expected << c << ", ";
      AddFuncCall(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                  /*repr=*/std::format("operator<<(expected, \"{}, \")", c));
    }
    expected << "y]";
    AddFuncCall(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*repr=*/"operator<<(expected, \"y]\")");
    std::stringstream sout;
    AddValueSet(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"sout", /*value=*/"std::stringstream()");
    sout << str_;
    AddFuncCall(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{"str"},
                /*repr=*/"operator<<(sout, str)");
    AssertEqual(sout.str(), expected.str(), /*repr0=*/"sout.str()",
                /*repr1=*/"expected.str()",
                /*relevant_locals=*/{"expected", "sout"},
                /*relevant_globals=*/{});
  }

  void TestExtract2() {
    std::string expected = "[]";
    AddValueSet(/*relevant_locals=*/{"expected"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"expected", /*value=*/"[]");
    while (str_.length()) {
      str_.RemoveEnd();
      AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"str"},
                  /*repr=*/"str.RemoveEnd()");
    }
    std::stringstream sout;
    AddValueSet(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false,
                /*value_name=*/"sout", /*value=*/"std::stringstream()");
    sout << str_;
    AddFuncCall(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{"str"},
                /*repr=*/"operator<<(sout, str)");
    AssertEqual(sout.str(), expected, /*repr0=*/"sout.str()",
                /*repr1=*/"expected", /*relevant_locals=*/{"expected", "sout"},
                /*relevant_globals=*/{});
  }

 private:
  SortedCollection<char> str_;
};

int main() {
  CollectionIntTest int_test;
  TestResult int_results = int_test.Run();
  int_results.LogJson("int_test_log");

  CollectionCharTest char_test;
  TestResult char_results = char_test.Run();
  char_results.LogJson("char_test_log");

  return 0;
}
