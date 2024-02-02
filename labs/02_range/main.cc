#include <sstream>

#include "custom_libraries/test.h"
#include "labs/02_range/range.h"

using rose::Range, rose::TestCase, rose::TestResult;

class RangeTest : public TestCase {
 public:
  TestResult Run() {
    RunTest(TestLength1, "TestLength1");
    RunTest(TestLength2, "TestLength2");
    RunTest(TestLength3, "TestLength3");
    RunTest(TestLength4, "TestLength4");
    RunTest(TestLength5, "TestLength5");
    RunTest(TestSum1, "TestSum1");
    RunTest(TestSum2, "TestSum2");
    RunTest(TestSum3, "TestSum3");
    RunTest(TestSum4, "TestSum4");
    RunTest(TestSum5, "TestSum5");
    RunTest(TestAverage1, "TestAverage1");
    RunTest(TestAverage2, "TestAverage2");
    RunTest(TestAverage3, "TestAverage3");
    RunTest(TestAverage4, "TestAverage4");
    RunTest(TestAverage5, "TestAverage5");
    RunTest(TestMin1, "TestMin1");
    RunTest(TestMin2, "TestMin2");
    RunTest(TestMin3, "TestMin3");
    RunTest(TestMin4, "TestMin4");
    RunTest(TestMin5, "TestMin5");
    RunTest(TestMax1, "TestMax1");
    RunTest(TestMax2, "TestMax2");
    RunTest(TestMax3, "TestMax3");
    RunTest(TestMax4, "TestMax4");
    RunTest(TestMax5, "TestMax5");
    RunTest(TestExtraction1, "TestExtraction1");
    RunTest(TestExtraction2, "TestExtraction2");
    RunTest(TestExtraction3, "TestExtraction3");
    RunTest(TestExtraction4, "TestExtraction4");
    RunTest(TestExtraction5, "TestExtraction5");
    return result_;
  }

  // Should never need to be used, but just in case...
  void ResetGlobals() override {
    r1_ = {/*start=*/3, /*stop=*/11};
    r2_ = {/*start=*/3, /*stop=*/12, /*step=*/2};
    r3_ = {/*start=*/7.5, /*stop=*/20.3, /*step=*/2.5};
    r4_ = {/*start=*/12, /*stop=*/3, /*step=*/-2};
    r5_ = {/*start=*/20.0, /*stop=*/4.0, /*step=*/-2.5};
  }

  void TestLength1() {
    AssertEqual(r1_.length(), size_t{9}, "Range(3, 11).length", "9");
  }

  void TestLength2() {
    AssertEqual(r2_.length(), size_t{5}, "Range(3, 12, 2).length", "5");
  }

  void TestLength3() {
    AssertEqual(r3_.length(), size_t{6}, "Range(7.5, 20.3, 2.5).length", "6");
  }

  void TestLength4() {
    AssertEqual(r4_.length(), size_t{5}, "Range(12, 3, -2).length", "5");
  }

  void TestLength5() {
    AssertEqual(r5_.length(), size_t{7}, "Range(20, 4, -2.5).length", "7");
  }

  void TestSum1() { AssertEqual(r1_.sum(), 63, "Range(3, 11).sum", "63"); }

  void TestSum2() { AssertEqual(r2_.sum(), 35, "Range(3, 12, 2).sum", "35"); }

  void TestSum3() {
    AssertEqual(r3_.sum(), 82.5, "Range(7.5, 20.3, 2.5).sum", "82.5");
  }

  void TestSum4() { AssertEqual(r4_.sum(), 40, "Range(12, 3, -2).sum", "40"); }

  void TestSum5() {
    AssertEqual(r5_.sum(), 87.5, "Range(20, 4, -2.5).sum", "87.5");
  }

  void TestAverage1() {
    AssertEqual(r1_.average(), 7, "Range(3, 11).average", "7");
  }

  void TestAverage2() {
    AssertEqual(r2_.average(), 7, "Range(3, 12, 2).average", "7");
  }

  void TestAverage3() {
    AssertEqual(r3_.average(), 13.75, "Range(7.5, 20.3, 2.5).average", "13.75");
  }

  void TestAverage4() {
    AssertEqual(r4_.average(), 8, "Range(12, 3, -2).average", "8");
  }

  void TestAverage5() {
    AssertEqual(r5_.average(), 12.5, "Range(20, 4, -2.5).average", "12.5");
  }

  void TestMin1() { AssertEqual(r1_.min(), 3, "Range(3, 11).min", "3"); }

  void TestMin2() { AssertEqual(r2_.min(), 3, "Range(3, 12).min", "3"); }

  void TestMin3() {
    AssertEqual(r3_.min(), 7.5, "Range(7.5, 20.3, 2.5).min", "7.5");
  }

  void TestMin4() { AssertEqual(r4_.min(), 4, "Range(12, 3, -2).min", "4"); }

  void TestMin5() {
    AssertEqual(r5_.min(), 5.0, "Range(20, 5, -2.5).min", "5");
  }

  void TestMax1() { AssertEqual(r1_.max(), 11, "Range(3, 11).max", "11"); }

  void TestMax2() { AssertEqual(r2_.max(), 11, "Range(3, 12).max", "11"); }

  void TestMax3() {
    AssertEqual(r3_.max(), 20.0, "Range(7.5, 20.3, 2.5).max", "20");
  }

  void TestMax4() { AssertEqual(r4_.max(), 12, "Range(12, 3, -2).max", "12"); }

  void TestMax5() {
    AssertEqual(r5_.max(), 20.0, "Range(20, 4, -2.5).max", "20");
  }

  void TestExtraction1() {
    std::stringstream sout;
    sout << r1_;

    AssertEqual(sout.str(), std::string("3, 4, 5, 6, 7, 8, 9, 10, 11"),
                "Range(3, 11)", "3, 4, 5, 6, 7, 8, 9, 10, 11");
  }

  void TestExtraction2() {
    std::stringstream sout;
    sout << r2_;

    AssertEqual(sout.str(), std::string("3, 5, 7, 9, 11"), "Range(3, 12, 2)",
                "3, 5, 7, 9, 11");
  }

  void TestExtraction3() {
    std::stringstream sout;
    sout << r3_;

    AssertEqual(sout.str(), std::string("7.5, 10, 12.5, 15, 17.5, 20"),
                "Range(7.5, 20.3, 2.5)", "7.5, 10, 12.5, 15, 17.5, 20");
  }

  void TestExtraction4() {
    std::stringstream sout;
    sout << r4_;

    AssertEqual(sout.str(), std::string("12, 10, 8, 6, 4"), "Range(12, 3, -2)",
                "12, 10, 8, 6, 4");
  }

  void TestExtraction5() {
    std::stringstream sout;
    sout << r5_;

    AssertEqual(sout.str(), std::string("20, 17.5, 15, 12.5, 10, 7.5, 5"),
                "Range(20, 4, -2.5)", "20, 17.5, 15, 12.5, 10, 7.5, 5");
  }

 private:
  Range<int> r1_ = {/*start=*/3, /*stop=*/11};
  Range<int> r2_ = {/*start=*/3, /*stop=*/12, /*step=*/2};
  Range<double> r3_ = {/*start=*/7.5, /*stop=*/20.3, /*step=*/2.5};
  Range<int> r4_ = {/*start=*/12, /*stop=*/3, /*step=*/-2};
  Range<double> r5_ = {/*start=*/20.0, /*stop=*/4.0, /*step=*/-2.5};
};

int main() {
  RangeTest test;
  TestResult results = test.Run();
  results.Report();

  return 0;
}
