#include <sstream>

#include "custom_libraries/test.h"
#include "no_brainers/02_point_revisited/point.h"

using rose::Point, rose::TestCase, rose::TestResult;

class PointIntTest : public TestCase<Point<int>> {
 public:
  PointIntTest() {
    AddGlobal("one_one", {&one_one_, one_one_, "Point<int>(1, 1)"});
    AddGlobal("three_four", {&three_four_, three_four_, "Point<int>(3, 4)"});
  }

  TestResult Run() {
    RunTest(TestAddition, "TestAddition");
    RunTest(TestInPlaceAdd, "TestInPlaceAdd");
    RunTest(TestSubtraction, "TestSubtraction");
    RunTest(TestInPlaceSub, "TestInPlaceSub");
    RunTest(TestInsertion, "TestInsertion");
    RunTest(TestExtraction, "TestExtraction");
    return result_;
  }

  void TestAddition() {
    AssertEqual(one_one_ + three_four_, {4, 5},
                /*repr0=*/"one_one + three_four", /*repr1=*/"(4, 5)",
                /*relevant_locals=*/{},
                /*relevant_globals=*/{"one_one", "three_four"});
  }

  void TestInPlaceAdd() {
    one_one_ += three_four_;
    AddFuncCall(/*relevant_locals=*/{},
                /*relevant_globals=*/{"one_one", "three_four"},
                /*repr=*/"one_one.operator+=(three_four)");
    AssertEqual(one_one_, {4, 5}, /*repr0=*/"one_one", /*repr1=*/"(4, 5)",
                /*relevant_locals=*/{}, /*relevant_globals=*/{"one_one"});
    ResetGlobal("one_one");
  }

  void TestSubtraction() {
    AssertEqual(one_one_ - three_four_, {-2, -3},
                /*repr0=*/"one_one - three_four", /*repr1=*/"(-2, -3)",
                /*relevant_locals=*/{},
                /*relevant_globals=*/{"one_one", "three_four"});
  }

  void TestInPlaceSub() {
    one_one_ -= three_four_;
    AddFuncCall(/*relevant_locals=*/{},
                /*relevant_globals=*/{"one_one", "three_four"},
                /*repr=*/"one_one.operator-=(three_four)");
    AssertEqual(one_one_, {-2, -3}, /*repr0=*/"one_one", /*repr1=*/"(-2, -3)",
                /*relevant_locals=*/{}, /*relevant_globals=*/{"one_one"});
    ResetGlobal("one_one");
  }

  void TestInsertion() {
    std::stringstream sin;
    AddValueSet(/*relevant_locals=*/{"sin"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"sin",
                /*value=*/"std::stringstream()");
    Point<int> p;
    AddValueSet(/*relevant_locals=*/{"p"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"p",
                /*value=*/"Point<int>()");
    sin << "3 4";
    AddFuncCall(/*relevant_locals=*/{"sin"}, /*relevant_globals=*/{},
                /*repr=*/"operator<<(sin, \"3 4\")");
    sin >> p;
    AddFuncCall(/*relevant_locals=*/{"sin", "p"}, /*relevant_globals=*/{},
                /*repr=*/"operator>>(sin, p)");

    AssertEqual(p, {3, 4}, /*repr0=*/"p", /*repr1=*/"(3, 4)",
                /*relevant_locals=*/{"p"}, /*relevant_globals=*/{});
  }

  void TestExtraction() {
    std::stringstream sout;
    AddValueSet(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"sout",
                /*value=*/"std::stringstream()");
    sout << one_one_;
    AddFuncCall(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{"one_one"},
                /*repr=*/"operator<<(sout, one_one)");

    AssertEqual(sout.str(), std::string("(1, 1)"), /*repr0=*/"sout.str()",
                /*repr1=*/"(1, 1)", /*relevant_locals=*/{"sout"},
                /*relevant_globals=*/{});
  }

 private:
  Point<int> one_one_ = {1, 1};
  Point<int> three_four_ = {3, 4};
};

class PointFloatTest : public TestCase<Point<float>> {
 public:
  PointFloatTest() {
    AddGlobal("e_pi", {&e_pi_, e_pi_, "Point<float>(2.71828, 3.14159)"});
    AddGlobal("fifth_root_of_unity",
              {&fifth_root_of_unity_, fifth_root_of_unity_,
               "Point<float>(0.30902, 0.95106)"});
  }

  TestResult Run() {
    RunTest(TestAddition, "TestAddition");
    RunTest(TestInPlaceAdd, "TestInPlaceAdd");
    RunTest(TestSubtraction, "TestSubtraction");
    RunTest(TestInPlaceSub, "TestInPlaceSub");
    RunTest(TestInsertion, "TestInsertion");
    RunTest(TestExtraction, "TestExtraction");
    return result_;
  }

  void TestAddition() {
    AssertEqual(e_pi_ + fifth_root_of_unity_, {3.0273f, 4.09265f},
                /*repr0=*/"e_pi + fifth_root_of_unity",
                /*repr1=*/"(3.0273, 4.09265)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"e_pi", "fifth_root_of_unity"});
  }

  void TestInPlaceAdd() {
    e_pi_ += fifth_root_of_unity_;
    AddFuncCall(/*relevant_locals=*/{},
                /*relevant_globals=*/{"e_pi", "fifth_root_of_unity"},
                /*repr=*/"e_pi.operator+=(fifth_root_of_unity)");
    AssertEqual(e_pi_, {3.0273f, 4.09265f}, /*repr0=*/"e_pi",
                /*repr1=*/"(3.0273, 4.09265)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"e_pi"});
    ResetGlobal("e_pi");
  }

  void TestSubtraction() {
    AssertEqual(e_pi_ - fifth_root_of_unity_, {2.40926f, 2.19053f},
                /*repr0=*/"e_pi - fifth_root_of_unity",
                /*repr1=*/"(2.40926, 2.19053)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"e_pi", "fifth_root_of_unity"});
  }

  void TestInPlaceSub() {
    e_pi_ -= fifth_root_of_unity_;
    AddFuncCall(/*relevant_locals=*/{},
                /*relevant_globals=*/{"e_pi", "fifth_root_of_unity"},
                /*repr=*/"e_pi.operator-=(fifth_root_of_unity)");
    AssertEqual(e_pi_, {2.40926f, 2.19053f}, /*repr0=*/"e_pi",
                /*repr1=*/"(2.40926, 2.19053)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"e_pi"});
    ResetGlobal("e_pi");
  }

  void TestInsertion() {
    std::stringstream sin;
    AddValueSet(/*relevant_locals=*/{"sin"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"sin",
                /*value=*/"std::stringstream()");
    Point<float> p;
    AddValueSet(/*relevant_locals=*/{"p"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"p",
                /*value=*/"Point<float>()");
    sin << "2.71828 3.14159";
    AddFuncCall(/*relevant_locals=*/{"sin"}, /*relevant_globals=*/{},
                /*repr=*/"operator<<(sin, \"2.71828 3.14159\")");
    sin >> p;
    AddFuncCall(/*relevant_locals=*/{"sin", "p"}, /*relevant_globals=*/{},
                /*repr=*/"operator>>(sin, p)");

    AssertEqual(p, {2.71828f, 3.14159f}, /*repr0=*/"p",
                /*repr1=*/"(2.71828, 3.14159)", /*relevant_locals=*/{"p"},
                /*relevant_globals=*/{});
  }

  void TestExtraction() {
    std::stringstream sout;
    AddValueSet(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"sout",
                /*value=*/"std::stringstream()");
    sout << fifth_root_of_unity_;
    AddFuncCall(/*relevant_locals=*/{"sout"},
                /*relevant_globals=*/{"fifth_root_of_unity"},
                /*repr=*/"operator<<(sout, fifth_root_of_unity)");

    AssertEqual(sout.str(), std::string("(0.30902, 0.95106)"),
                /*repr0=*/"sout.str()", /*repr1=*/"(0.30902, 0.95106)",
                /*relevant_locals=*/{"sout"}, /*relevant_globals=*/{});
  }

 private:
  Point<float> e_pi_ = {2.71828f, 3.14159f};
  Point<float> fifth_root_of_unity_ = {0.30902f, 0.95106f};
};

class PointDoubleTest : public TestCase<Point<double>> {
 public:
  PointDoubleTest() {
    AddGlobal("idk0", {&idk0_, idk0_, "Point<double>(-4.59643, 1.58321)"});
    AddGlobal("idk1", {&idk1_, idk1_, "Point<double>(12.49582, -59.95378)"});
  }

  TestResult Run() {
    RunTest(TestAddition, "TestAddition");
    RunTest(TestInPlaceAdd, "TestInPlaceAdd");
    RunTest(TestSubtraction, "TestSubtraction");
    RunTest(TestInPlaceSub, "TestInPlaceSub");
    return result_;
  }

  void TestAddition() {
    AssertEqual(idk0_ + idk1_, {7.89939, -58.37057},
                /*repr0=*/"idk0 + idk1", /*repr1=*/"(7.89939, -58.37057)",
                /*relevant_locals=*/{}, /*relevant_globals=*/{"idk0", "idk1"});
  }

  void TestInPlaceAdd() {
    idk0_ += idk1_;
    AddFuncCall(/*relevant_locals=*/{},
                /*relevant_globals=*/{"idk0", "idk1"},
                /*repr=*/"idk0.operator+=(idk1)");
    AssertEqual(idk0_, {7.89939, -58.37057}, /*repr0=*/"idk0",
                /*repr1=*/"(7.89939, -58.37057)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"idk0"});
    ResetGlobal("idk0");
  }

  void TestSubtraction() {
    AssertEqual(idk0_ - idk1_, {-17.09225, 61.53699}, /*repr0=*/"idk0 - idk1",
                /*repr1=*/"(-17.09225, 61.53699)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"idk0", "idk1"});
  }

  void TestInPlaceSub() {
    idk0_ -= idk1_;
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"idk0", "idk1"},
                /*repr=*/"idk0.operator-=(idk1)");
    AssertEqual(idk0_, {-17.09225, 61.53699}, /*repr0=*/"idk0",
                /*repr1=*/"(-17.09225, 61.53699)", /*relevant_locals=*/{},
                /*relevant_globals=*/{"idk0"});
    ResetGlobal("idk0");
  }

 private:
  Point<double> idk0_ = {-4.59643, 1.58321};
  Point<double> idk1_ = {12.49582, -59.95378};
};

int main() {
  PointIntTest int_test;
  TestResult int_test_results = int_test.Run();
  int_test_results.LogJson("int_test");

  PointFloatTest float_test;
  TestResult float_test_results = float_test.Run();
  float_test_results.LogJson("float_test");

  PointDoubleTest double_test;
  TestResult double_test_results = double_test.Run();
  double_test_results.LogJson("double_test");

  return 0;
}
