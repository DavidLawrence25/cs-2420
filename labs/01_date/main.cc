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
    july10_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    sept10_ = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
  }

  void TestConstructor1() {
    auto date = Date(/*year=*/2018);
    AssertEqual(date.hash(), 0xfc421, "Date(2018)", "January 1, 2018");
  }

  void TestConstructor2() {
    auto date = Date(/*year=*/2018, /*month=*/7);
    AssertEqual(date.hash(), 0xfc4e1, "Date(2018, 7)", "July 1, 2018");
  }

  void TestConstructor3() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    AssertEqual(date.hash(), 0xfc4ea, "Date(2018, 7, 10)", "July 10, 2018");
  }

  void TestAddMonths1() {
    july10_.AddMonths(4);
    AssertEqual(july10_.hash(), 0xfc56a, "Date(2018, 7, 10) + 4 Months",
                "November 10, 2018");
    ResetGlobals();
  }

  void TestAddMonths2() {
    july10_.AddMonths(5);
    AssertEqual(july10_.hash(), 0xfc58a, "Date(2018, 7, 10) + 5 Months",
                "December 10, 2018");
    ResetGlobals();
  }

  void TestAddMonths3() {
    july10_.AddMonths(6);
    AssertEqual(july10_.hash(), 0xfc62a, "Date(2018, 7, 10) + 6 Months",
                "January 10, 2019");
    ResetGlobals();
  }

  void TestAddDays1() {
    july10_.AddDays(16);
    AssertEqual(july10_.hash(), 0xfc4fa, "Date(2018, 7, 10) + 16 Days",
                "July 26, 2018");
    ResetGlobals();
  }

  void TestAddDays2() {
    july10_.AddDays(21);
    AssertEqual(july10_.hash(), 0xfc4ff, "Date(2018, 7, 10) + 21 Days",
                "July 31, 2018");
    ResetGlobals();
  }

  void TestAddDays3() {
    july10_.AddDays(31);
    AssertEqual(july10_.hash(), 0xfc50a, "Date(2018, 7, 10) + 31 Days",
                "August 10, 2018");
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
    AssertEqual((sept10_ + 23).hash(), 0xfc543, "Date(2018, 9, 10) + 23",
                "October 3, 2018");
  }

  void TestAddOperator2() {
    AssertEqual((sept10_ + 38).hash(), 0xfc552, "Date(2018, 9, 10) + 38",
                "October 18, 2018");
  }

  void TestAddOperator3() {
    AssertEqual((sept10_ + 56).hash(), 0xfc565, "Date(2018, 9, 10) + 56",
                "November 5, 2018");
  }

  void TestAddOperator4() {
    AssertEqual((sept10_ + 91).hash(), 0xfc58a, "Date(2018, 9, 10) + 91",
                "December 10, 2018");
  }

  void TestAddOperator5() {
    AssertEqual((sept10_ + 134).hash(), 0xfc636, "Date(2018, 9, 10) + 134",
                "January 22, 2019");
  }

  void TestExtractionOperator() {
    std::stringstream sout;
    sout << sept10_;

    AssertEqual(sout.str(), std::string("September 10, 2018"),
                "Date(2018, 9, 10).ToString()", "September 10, 2018");
  }

 private:
  Date july10_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
  Date sept10_ = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
};

int main() {
  DateTest test;
  TestResult results = test.Run();
  results.Report();

  return 0;
}
