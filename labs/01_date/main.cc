#include <functional>
#include <sstream>

#include "custom_libraries/test.h"
#include "labs/01_date/date.h"

using rose::Date, rose::TestCase, rose::TestResult;
using rose::GlobalTag, rose::Global;
using rose::Step, rose::Assertion, rose::FuncCall, rose::ValueSet;

class DateTest : public TestCase<Date> {
 public:
  DateTest() {
    AddGlobal("jul10", {&jul10_, Date(2018, 7, 10), "Date(2018, 7, 10)"});
    AddGlobal("sep10", {&sep10_, Date(2018, 9, 10), "Date(2018, 9, 10)"});
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

  void TestConstructor1() {
    auto date = Date(/*year=*/2018);
    AddValueSet(/*relevant_locals=*/{"date"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"date",
                /*value=*/"Date(2018)");
    AssertEqual(date.hash(), 0xfc421, /*repr0=*/"date",
                /*repr1=*/"Jan 1, 2018", /*relevant_locals=*/{"date"},
                /*relevant_globals=*/{});
  }

  void TestConstructor2() {
    auto date = Date(/*year=*/2018, /*month=*/7);
    AddValueSet(/*relevant_locals=*/{"date"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"date",
                /*value=*/"Date(2018, 7)");
    AssertEqual(date.hash(), 0xfc4e1, /*repr0=*/"date", /*repr1=*/"Jul 1, 2018",
                /*relevant_locals=*/{"date"}, /*relevant_globals=*/{});
  }

  void TestConstructor3() {
    auto date = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
    AddValueSet(/*relevant_locals=*/{"date"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"date",
                /*value=*/"Date(2018, 7, 10)");
    AssertEqual(date.hash(), 0xfc4ea, /*repr0=*/"date",
                /*repr1=*/"Jul 10, 2018", /*relevant_locals=*/{"date"},
                /*relevant_globals=*/{});
  }

  void TestAddMonths1() {
    jul10_.AddMonths(4);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"jul10"},
                /*repr=*/"jul10.AddMonths(4)");
    AssertEqual(jul10_.hash(), 0xfc56a, /*repr0=*/"jul10",
                /*repr1=*/"Nov 10, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"jul10"});
    ResetGlobal("jul10");
  }

  void TestAddMonths2() {
    jul10_.AddMonths(5);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"jul10"},
                /*repr=*/"jul10.AddMonths(5)");
    AssertEqual(jul10_.hash(), 0xfc58a, /*repr0=*/"jul10",
                /*repr1=*/"Dec 10, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"jul10"});
    ResetGlobal("jul10");
  }

  void TestAddMonths3() {
    jul10_.AddMonths(6);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"jul10"},
                /*repr=*/"jul10.AddMonths(6)");
    AssertEqual(jul10_.hash(), 0xfc62a, /*repr0=*/"jul10",
                /*repr1=*/"Jan 10, 2019", /*relevant_locals=*/{},
                /*relevant_globals=*/{"jul10"});
    ResetGlobal("jul10");
  }

  void TestAddDays1() {
    jul10_.AddDays(16);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"jul10"},
                /*repr=*/"jul10.AddDays(16)");
    AssertEqual(jul10_.hash(), 0xfc4fa, /*repr0=*/"jul10",
                /*repr1=*/"Jul 26, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"jul10"});
    ResetGlobal("jul10");
  }

  void TestAddDays2() {
    jul10_.AddDays(21);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"jul10"},
                /*repr=*/"jul10.AddDays(21)");
    AssertEqual(jul10_.hash(), 0xfc4ff, /*repr0=*/"jul10",
                /*repr1=*/"Jul 31, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"jul10"});
    ResetGlobal("jul10");
  }

  void TestAddDays3() {
    jul10_.AddDays(31);
    AddFuncCall(/*relevant_locals=*/{}, /*relevant_globals=*/{"jul10"},
                /*repr=*/"jul10.AddDays(31)");
    AssertEqual(jul10_.hash(), 0xfc50a, /*repr0=*/"jul10",
                /*repr1=*/"Aug 10, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"jul10"});
    ResetGlobal("jul10");
  }

  void TestIsLeapYear1() {
    AssertFalse(Date::IsLeapYear(1995), /*repr=*/"IsLeapYear(1995)",
                /*relevant_locals=*/{}, /*relevant_globals=*/{});
  }

  void TestIsLeapYear2() {
    AssertTrue(Date::IsLeapYear(1996), /*repr=*/"IsLeapYear(1996)",
               /*relevant_locals=*/{}, /*relevant_globals=*/{});
  }

  void TestIsLeapYear3() {
    AssertTrue(Date::IsLeapYear(2000), /*repr=*/"IsLeapYear(2000)",
               /*relevant_locals=*/{}, /*relevant_globals=*/{});
  }

  void TestIsLeapYear4() {
    AssertFalse(Date::IsLeapYear(1900), /*repr=*/"IsLeapYear(1900)",
                /*relevant_locals=*/{}, /*relevant_globals=*/{});
  }

  void TestDayOfYear1() {
    auto date = Date(/*year=*/1970, /*month=*/1, /*day=*/1);
    AddValueSet(/*relevant_locals=*/{"date"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"date",
                /*value=*/"Date(1970, 1, 1)");
    AssertEqual(date.DayOfYear(), 1, /*repr0=*/"date.DayOfYear()",
                /*repr1=*/"1", /*relevant_locals=*/{"date"},
                /*relevant_globals=*/{});
  }

  void TestDayOfYear2() {
    auto date = Date(/*year=*/2007, /*month=*/2, /*day=*/22);
    AddValueSet(/*relevant_locals=*/{"date"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"date",
                /*value=*/"Date(2007, 2, 22)");
    AssertEqual(date.DayOfYear(), 53, /*repr0=*/"date.DayOfYear()",
                /*repr1=*/"53", /*relevant_locals=*/{"date"},
                /*relevant_globals=*/{});
  }

  void TestAddOperator1() {
    AssertEqual((sep10_ + 23).hash(), 0xfc543, /*repr0=*/"sep10 + 23",
                /*repr1=*/"Oct 3, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"sep10"});
  }

  void TestAddOperator2() {
    AssertEqual((sep10_ + 38).hash(), 0xfc552, /*repr0=*/"sep10 + 38",
                /*repr1=*/"Oct 18, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"sep10"});
  }

  void TestAddOperator3() {
    AssertEqual((sep10_ + 56).hash(), 0xfc565, /*repr0=*/"sep10 + 56",
                /*repr1=*/"Nov 5, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"sep10"});
  }

  void TestAddOperator4() {
    AssertEqual((sep10_ + 91).hash(), 0xfc58a, /*repr0=*/"sep10 + 91",
                /*repr1=*/"Dec 10, 2018", /*relevant_locals=*/{},
                /*relevant_globals=*/{"sep10"});
  }

  void TestAddOperator5() {
    AssertEqual((sep10_ + 134).hash(), 0xfc636, /*repr0=*/"sep10 + 134",
                /*repr1=*/"Jan 22, 2019", /*relevant_locals=*/{},
                /*relevant_globals=*/{"sep10"});
  }

  void TestExtractionOperator() {
    std::stringstream sout;
    AddValueSet(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{},
                /*is_init=*/true, /*is_global=*/false, /*value_name=*/"sout",
                /*value=*/"std::stringstream()");
    sout << sep10_;
    AddFuncCall(/*relevant_locals=*/{"sout"}, /*relevant_globals=*/{"sep10"},
                /*repr=*/"operator<<(sout, sep10)");

    AssertEqual(sout.str(), std::string("Sep 10, 2018"),
                /*repr0=*/"sout.str()", /*repr1=*/"\"Sep 10, 2018\"",
                /*relevant_locals=*/{"sout"}, /*relevant_globals=*/{"sep10"});
  }

 private:
  Date jul10_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
  Date sep10_ = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
};

int main() {
  DateTest test;
  TestResult results = test.Run();
  results.LogJson("date_test_log");

  return 0;
}
