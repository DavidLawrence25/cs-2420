#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/01_date/date.h"

using rose::CommandLineFlags;
using rose::Date, rose::TestCase, rose::TestResult, rose::TestSuite;

class DateTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestDefaultConstructor();
    TestYearConstructor();
    TestYearMonthConstructor();
    TestFullConstructor();
    TestIs1900LeapYear();
    TestIs1995LeapYear();
    TestIs1996LeapYear();
    TestIs2000LeapYear();
  }

  void TestDefaultConstructor() { ASSERT_EQUAL(Date().hash(), 0xf6421); }
  void TestYearConstructor() { ASSERT_EQUAL(Date(2018).hash(), 0xfc421); }

  void TestYearMonthConstructor() {
    ASSERT_EQUAL(Date(2018, 7).hash(), 0xfc4e1);
  }

  void TestFullConstructor() {
    ASSERT_EQUAL(Date(2018, 7, 10).hash(), 0xfc4ea);
  }

  void TestIs1900LeapYear() { ASSERT_FALSE(Date::IsLeapYear(1900)); }
  void TestIs1995LeapYear() { ASSERT_FALSE(Date::IsLeapYear(1995)); }
  void TestIs1996LeapYear() { ASSERT_TRUE(Date::IsLeapYear(1996)); }
  void TestIs2000LeapYear() { ASSERT_TRUE(Date::IsLeapYear(2000)); }
};

class Jul10Test : public TestCase {
 public:
  void Repair() override {
    date_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
  }

  void Run() override {
    TestIAdd4Months();
    TestIAdd5Months();
    TestIAdd6Months();
    TestIAdd16Days();
    TestIAdd21Days();
    TestIAdd31Days();
    TestDayOfYear();
    TestAdd18Days();
    TestAdd21Days();
    TestAdd22Days();
    TestAdd91Days();
    TestAdd234Days();
    TestStreamExtraction();
  }

  void TestIAdd4Months() {
    date_.AddMonths(4);
    ASSERT_EQUAL(date_, Date(2018, 11, 10));
    Repair();
  }

  void TestIAdd5Months() {
    date_.AddMonths(5);
    ASSERT_EQUAL(date_, Date(2018, 12, 10));
    Repair();
  }

  void TestIAdd6Months() {
    date_.AddMonths(6);
    ASSERT_EQUAL(date_, Date(2019, 1, 10));
    Repair();
  }

  void TestIAdd16Days() {
    date_.AddDays(16);
    ASSERT_EQUAL(date_, Date(2018, 7, 26));
    Repair();
  }

  void TestIAdd21Days() {
    date_.AddDays(21);
    ASSERT_EQUAL(date_, Date(2018, 7, 31));
    Repair();
  }

  void TestIAdd31Days() {
    date_.AddDays(31);
    ASSERT_EQUAL(date_, Date(2018, 8, 10));
    Repair();
  }

  void TestDayOfYear() { ASSERT_EQUAL(date_.DayOfYear(), 191); }
  void TestAdd18Days() { ASSERT_EQUAL(date_ + 18, Date(2018, 7, 28)); }
  void TestAdd21Days() { ASSERT_EQUAL(date_ + 21, Date(2018, 7, 31)); }
  void TestAdd22Days() { ASSERT_EQUAL(date_ + 22, Date(2018, 8, 1)); }
  void TestAdd91Days() { ASSERT_EQUAL(date_ + 91, Date(2018, 10, 9)); }
  void TestAdd234Days() { ASSERT_EQUAL(date_ + 234, Date(2019, 3, 1)); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << date_;
    ASSERT_EQUAL(sout.str(), std::string("Jul 10, 2018"));
  }

 private:
  Date date_ = Date(/*year=*/2018, /*month=*/7, /*day=*/10);
};

class Sep10Test : public TestCase {
 public:
  void Repair() override {
    date_ = Date(/*year=*/2018, /*month=*/9, /*day=*/10);
  }

  void Run() override {
    TestIAdd2Months();
    TestIAdd3Months();
    TestIAdd4Months();
    TestIAdd16Days();
    TestIAdd20Days();
    TestIAdd30Days();
    TestDayOfYear();
    TestAdd16Days();
    TestAdd20Days();
    TestAdd21Days();
    TestAdd75Days();
    TestAdd117Days();
    TestStreamExtraction();
  }

  void TestIAdd2Months() {
    date_.AddMonths(2);
    ASSERT_EQUAL(date_, Date(2018, 11, 10));
    Repair();
  }

  void TestIAdd3Months() {
    date_.AddMonths(3);
    ASSERT_EQUAL(date_, Date(2018, 12, 10));
    Repair();
  }

  void TestIAdd4Months() {
    date_.AddMonths(4);
    ASSERT_EQUAL(date_, Date(2019, 1, 10));
    Repair();
  }

  void TestIAdd16Days() {
    date_.AddDays(16);
    ASSERT_EQUAL(date_, Date(2018, 9, 26));
    Repair();
  }

  void TestIAdd20Days() {
    date_.AddDays(20);
    ASSERT_EQUAL(date_, Date(2018, 9, 30));
    Repair();
  }

  void TestIAdd30Days() {
    date_.AddDays(30);
    ASSERT_EQUAL(date_, Date(2018, 10, 10));
    Repair();
  }

  void TestDayOfYear() { ASSERT_EQUAL(date_.DayOfYear(), 253); }
  void TestAdd16Days() { ASSERT_EQUAL(date_ + 16, Date(2018, 9, 26)); }
  void TestAdd20Days() { ASSERT_EQUAL(date_ + 20, Date(2018, 9, 30)); }
  void TestAdd21Days() { ASSERT_EQUAL(date_ + 21, Date(2018, 10, 1)); }
  void TestAdd75Days() { ASSERT_EQUAL(date_ + 75, Date(2018, 11, 24)); }
  void TestAdd117Days() { ASSERT_EQUAL(date_ + 117, Date(2019, 1, 5)); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << date_;
    ASSERT_EQUAL(sout.str(), std::string("Sep 10, 2018"));
  }

 private:
  Date date_ = {/*year=*/2018, /*month=*/9, /*day=*/10};
};

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<DateTest>());
  suite.Add(std::make_unique<Jul10Test>());
  suite.Add(std::make_unique<Sep10Test>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
