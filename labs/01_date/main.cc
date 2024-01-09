#include <functional>
#include <sstream>

#include "../../custom_libraries/test.h"
#include "date.h"

using rose::Date, rose::TestCase, rose::TestResult;

class DateTest : public TestCase {
 public:
  DateTest() {
    name_ = "DateTest";
    result_ = {};
  }

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

  void RunTest(void (DateTest::*test_func)(), std::string test_name) {
    test_name_ = test_name;
    std::invoke(test_func, this);
    test_name_ = "";
    result_.IncrementTestCounter();
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
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    date.AddMonths(4);
    AssertEqual(date.hash(), 0xfc56a, "Date(2018, 7, 10) + 4 Months",
                "November 10, 2018");
  }

  void TestAddMonths2() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    date.AddMonths(5);
    AssertEqual(date.hash(), 0xfc58a, "Date(2018, 7, 10) + 5 Months",
                "December 10, 2018");
  }

  void TestAddMonths3() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    date.AddMonths(6);
    AssertEqual(date.hash(), 0xfc62a, "Date(2018, 7, 10) + 6 Months",
                "January 10, 2019");
  }

  void TestAddDays1() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    date.AddDays(16);
    AssertEqual(date.hash(), 0xfc4fa, "Date(2018, 7, 10) + 16 Days",
                "July 26, 2018");
  }

  void TestAddDays2() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    date.AddDays(21);
    AssertEqual(date.hash(), 0xfc4ff, "Date(2018, 7, 10) + 21 Days",
                "July 31, 2018");
  }

  void TestAddDays3() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    date.AddDays(31);
    AssertEqual(date.hash(), 0xfc50a, "Date(2018, 7, 10) + 31 Days",
                "August 10, 2018");
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
    auto date = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
    AssertEqual((date + 23).hash(), 0xfc543, "Date(2018, 9, 10) + 23",
                "October 3, 2018");
  }

  void TestAddOperator2() {
    auto date = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
    AssertEqual((date + 38).hash(), 0xfc552, "Date(2018, 9, 10) + 38",
                "October 18, 2018");
  }

  void TestAddOperator3() {
    auto date = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
    AssertEqual((date + 56).hash(), 0xfc565, "Date(2018, 9, 10) + 56",
                "November 5, 2018");
  }

  void TestAddOperator4() {
    auto date = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
    AssertEqual((date + 91).hash(), 0xfc58a, "Date(2018, 9, 10) + 91",
                "December 10, 2018");
  }

  void TestAddOperator5() {
    auto date = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
    AssertEqual((date + 134).hash(), 0xfc636, "Date(2018, 9, 10) + 134",
                "January 22, 2019");
  }

  void TestExtractionOperator() {
    auto date = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
    std::stringstream sout;
    sout << date;

    AssertEqual(sout.str(), std::string("September 10, 2018"),
                "Date(2018, 9, 10).ToString()", "September 10, 2018");
  }
};

int main() {
  DateTest test;
  TestResult results = test.Run();
  results.Report();

  return 0;
}
