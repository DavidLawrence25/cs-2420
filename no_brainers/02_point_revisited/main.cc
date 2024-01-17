#include <sstream>

#include "../../custom_libraries/test.h"
#include "point.h"

using rose::Point, rose::TestCase, rose::TestResult;

class PointTest : public TestCase {
 public:
  TestResult Run() {
    RunTest(TestAddition1, "TestAddition1");
    RunTest(TestAddition2, "TestAddition2");
    RunTest(TestAddition3, "TestAddition3");
    RunTest(TestInPlaceAdd1, "TestInPlaceAdd1");
    RunTest(TestInPlaceAdd2, "TestInPlaceAdd2");
    RunTest(TestInPlaceAdd3, "TestInPlaceAdd3");
    RunTest(TestSubtraction1, "TestSubtraction1");
    RunTest(TestSubtraction2, "TestSubtraction2");
    RunTest(TestSubtraction3, "TestSubtraction3");
    RunTest(TestInPlaceSub1, "TestInPlaceSub1");
    RunTest(TestInPlaceSub2, "TestInPlaceSub2");
    RunTest(TestInPlaceSub3, "TestInPlaceSub3");
    RunTest(TestInsertion1, "TestInsertion1");
    RunTest(TestInsertion2, "TestInsertion2");
    RunTest(TestExtraction1, "TestExtraction1");
    RunTest(TestExtraction2, "TestExtraction2");
    return result_;
  }

  void ResetGlobals() override {
    one_one_ = {1, 1};
    three_four_ = {3, 4};
    e_pi_ = {2.71828f, 3.14159f};
    fifth_root_of_unity_ = {0.30902f, 0.95106f};
    idk0_ = {-4.59643, 1.58321};
    idk1_ = {12.49582, -59.95378};
  }

  void TestAddition1() {
    AssertEqual(one_one_ + three_four_, {4, 5}, "(1, 1) + (3, 4)", "(4, 5)");
  }

  void TestAddition2() {
    AssertEqual(e_pi_ + fifth_root_of_unity_, {3.0273f, 4.09265f},
                "(e, pi) + (cos(2pi/5), sin(2pi/5))", "(3.0273, 4.09265)");
  }

  void TestAddition3() {
    AssertEqual(idk0_ + idk1_, {7.89939, -58.37057},
                "(-4.59643, 1.58321) + (12.49582, -59.95378)",
                "(7.89939, -58.37057)");
  }

  void TestInPlaceAdd1() {
    one_one_ += three_four_;
    AssertEqual(one_one_, {4, 5}, "(1, 1) += (3, 4)", "(4, 5)");
    ResetGlobals();
  }

  void TestInPlaceAdd2() {
    e_pi_ += fifth_root_of_unity_;
    AssertEqual(e_pi_, {3.0273f, 4.09265f},
                "(e, pi) += (cos(2pi/5), sin(2pi/5))", "(3.0273, 4.09265)");
    ResetGlobals();
  }

  void TestInPlaceAdd3() {
    idk0_ += idk1_;
    AssertEqual(idk0_, {7.89939, -58.37057},
                "(-4.59643, 1.58321) += (12.49582, -59.95378)",
                "(7.89939, -58.37057)");
    ResetGlobals();
  }

  void TestSubtraction1() {
    AssertEqual(one_one_ - three_four_, {-2, -3}, "(1, 1) - (3, 4)",
                "(-2, -3)");
  }

  void TestSubtraction2() {
    AssertEqual(e_pi_ - fifth_root_of_unity_, {2.40926f, 2.19053f},
                "(e, pi) - (cos(2pi/5), sin(2pi/5))", "(2.40926, 2.19053)");
  }

  void TestSubtraction3() {
    AssertEqual(idk0_ - idk1_, {-17.09225, 61.53699},
                "(-4.59643, 1.58321) - (12.49582, -59.95378)",
                "(-17.09225, 61.53699)");
  }

  void TestInPlaceSub1() {
    one_one_ -= three_four_;
    AssertEqual(one_one_, {-2, -3}, "(1, 1) -= (3, 4)", "(-2, -3)");
    ResetGlobals();
  }

  void TestInPlaceSub2() {
    e_pi_ -= fifth_root_of_unity_;
    AssertEqual(e_pi_, {2.40926f, 2.19053f},
                "(e, pi) -= (cos(2pi/5), sin(2pi/5))", "(2.40926, 2.19053)");
    ResetGlobals();
  }

  void TestInPlaceSub3() {
    idk0_ -= idk1_;
    AssertEqual(idk0_, {-17.09225, 61.53699},
                "(-4.59643, 1.58321) -= (12.49582, -59.95378)",
                "(-17.09225, 61.53699)");
    ResetGlobals();
  }

  void TestInsertion1() {
    std::stringstream sin;
    Point<int> p;
    sin << "3 4";
    sin >> p;

    AssertEqual(p, {3, 4}, "Inserted (3, 4)", "(3, 4)");
  }

  void TestInsertion2() {
    std::stringstream sin;
    Point<float> p;
    sin << "2.71828 3.14159";
    sin >> p;

    AssertEqual(p, {2.71828f, 3.14159f}, "Inserted (e, pi)", "(e, pi)");
  }

  void TestExtraction1() {
    std::stringstream sout;
    sout << one_one_;

    AssertEqual(sout.str(), std::string("(1, 1)"), "Extracted (1, 1)",
                "(1, 1)");
  }

  void TestExtraction2() {
    std::stringstream sout;
    sout << fifth_root_of_unity_;

    AssertEqual(sout.str(), std::string("(0.30902, 0.95106)"),
                "Extracted Point(cos(2pi/5), sin(2pi/5))",
                "(0.30902, 0.95106)");
  }

 private:
  Point<int> one_one_ = {1, 1};
  Point<int> three_four_ = {3, 4};
  Point<float> e_pi_ = {2.71828f, 3.14159f};
  Point<float> fifth_root_of_unity_ = {0.30902f, 0.95106f};
  Point<double> idk0_ = {-4.59643, 1.58321};
  Point<double> idk1_ = {12.49582, -59.95378};
};

int main() {
  PointTest test;
  TestResult results = test.Run();
  results.Report();

  return 0;
}
