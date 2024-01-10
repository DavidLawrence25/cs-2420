#include <functional>
#include <sstream>

#include "../../custom_libraries/test.h"
#include "date.h"

using rose::Date, rose::TestCase, rose::TestResult;

class DateTest : public TestCase {
 public:
  TestResult Run() {
    RunTest(TestConstructor1, "TestConstructor1");
    RunTest(TestConstructor2, "TestConstructor2");
    RunTest(TestConstructor3, "TestConstructor3");
    RunTest(TestAddMonths1, "TestAddMonths1");
    RunTest(TestAddMonths2, "TestAddMonths2");
    RunTest(TestAddMonths3, "TestAddMonths3");
    RunTest(TestAddDays1, "TestAddDays1");
    RunTest(TestAddDays2, "TestAddDays2");
    RunTest(TestAddDays3, "TestAddDays3");
    RunTest(TestIsLeapYear1, "TestIsLeapYear1");
    RunTest(TestIsLeapYear2, "TestIsLeapYear2");
    RunTest(TestIsLeapYear3, "TestIsLeapYear3");
    RunTest(TestIsLeapYear4, "TestIsLeapYear4");
    RunTest(TestDayOfYear1, "TestDayOfYear1");
    RunTest(TestDayOfYear2, "TestDayOfYear2");
    RunTest(TestAddOperator1, "TestAddOperator1");
    RunTest(TestAddOperator2, "TestAddOperator2");
    RunTest(TestAddOperator3, "TestAddOperator3");
    RunTest(TestAddOperator4, "TestAddOperator4");
    RunTest(TestAddOperator5, "TestAddOperator5");
    RunTest(TestExtractionOperator, "TestExtractionOperator");
    return result_;
  }

  void ResetGlobals() override {
    jul10_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    sep10_ = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
  }

  void TestConstructor1() {
    auto date = Date(/*year=*/2018);
    AssertEqual(date.hash(), 0xfc421, "Date(2018)", "Jan 1, 2018");
  }

  void TestConstructor2() {
    auto date = Date(/*year=*/2018, /*month=*/7);
    AssertEqual(date.hash(), 0xfc4e1, "Date(2018, 7)", "Jul 1, 2018");
  }

  void TestConstructor3() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    AssertEqual(date.hash(), 0xfc4ea, "Date(2018, 7, 10)", "Jul 10, 2018");
  }

  void TestAddMonths1() {
    jul10_.AddMonths(4);
    AssertEqual(jul10_.hash(), 0xfc56a, "Date(2018, 7, 10) + 4 Months",
                "Nov 10, 2018");
    ResetGlobals();
  }

  void TestAddMonths2() {
    jul10_.AddMonths(5);
    AssertEqual(jul10_.hash(), 0xfc58a, "Date(2018, 7, 10) + 5 Months",
                "Dec 10, 2018");
    ResetGlobals();
  }

  void TestAddMonths3() {
    jul10_.AddMonths(6);
    AssertEqual(jul10_.hash(), 0xfc62a, "Date(2018, 7, 10) + 6 Months",
                "Jan 10, 2019");
    ResetGlobals();
  }

  void TestAddDays1() {
    jul10_.AddDays(16);
    AssertEqual(jul10_.hash(), 0xfc4fa, "Date(2018, 7, 10) + 16 Days",
                "Jul 26, 2018");
    ResetGlobals();
  }

  void TestAddDays2() {
    jul10_.AddDays(21);
    AssertEqual(jul10_.hash(), 0xfc4ff, "Date(2018, 7, 10) + 21 Days",
                "Jul 31, 2018");
    ResetGlobals();
  }

  void TestAddDays3() {
    jul10_.AddDays(31);
    AssertEqual(jul10_.hash(), 0xfc50a, "Date(2018, 7, 10) + 31 Days",
                "Aug 10, 2018");
    ResetGlobals();
  }

  void TestIsLeapYear1() {
    AssertFalse(Date::IsLeapYear(1995), "IsLeapYear(1995)");
  }

  void TestIsLeapYear2() {
    AssertTrue(Date::IsLeapYear(1996), "IsLeapYear(1996)");
  }

  void TestIsLeapYear3() {
    AssertTrue(Date::IsLeapYear(2000), "IsLeapYear(2000)");
  }

  void TestIsLeapYear4() {
    AssertFalse(Date::IsLeapYear(1900), "IsLeapYear(1900)");
  }

  void TestDayOfYear1() {
    auto date = Date(/*year=*/1970, /*month=*/1, /*day=*/1);
    AssertEqual(date.DayOfYear(), 1, "Date(1970, 1, 1).DayOfYear()", "1");
  }

  void TestDayOfYear2() {
    auto date = Date(/*year=*/2007, /*month=*/2, /*day=*/22);
    AssertEqual(date.DayOfYear(), 53, "Date(2007, 2, 22).DayOfYear()", "53");
  }

  void TestAddOperator1() {
    AssertEqual((sep10_ + 23).hash(), 0xfc543, "Date(2018, 9, 10) + 23",
                "Oct 3, 2018");
  }

  void TestAddOperator2() {
    AssertEqual((sep10_ + 38).hash(), 0xfc552, "Date(2018, 9, 10) + 38",
                "Oct 18, 2018");
  }

  void TestAddOperator3() {
    AssertEqual((sep10_ + 56).hash(), 0xfc565, "Date(2018, 9, 10) + 56",
                "Nov 5, 2018");
  }

  void TestAddOperator4() {
    AssertEqual((sep10_ + 91).hash(), 0xfc58a, "Date(2018, 9, 10) + 91",
                "Dec 10, 2018");
  }

  void TestAddOperator5() {
    AssertEqual((sep10_ + 134).hash(), 0xfc636, "Date(2018, 9, 10) + 134",
                "Jan 22, 2019");
  }

  void TestExtractionOperator() {
    std::stringstream sout;
    sout << sep10_;

    AssertEqual(sout.str(), std::string("Sep 10, 2018"),
                "Date(2018, 9, 10).ToString()", "Sep 10, 2018");
  }

 private:
  Date jul10_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
  Date sep10_ = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
};

int main() {
  DateTest test;
  TestResult results = test.Run();
  results.Report();

  return 0;
}
