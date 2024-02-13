#include <stdlib.h>

#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/02_range/range.h"

using rose::Range, rose::TestCase, rose::TestResult;

class PlainIntRangeTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestLength();
    TestSum();
    TestAverage();
    TestMin();
    TestMax();
    TestStreamExtraction();
  }

  void TestLength() { ASSERT_EQUAL(range_.length(), size_t{9}); }
  void TestSum() { ASSERT_EQUAL(range_.sum(), 63); }
  void TestAverage() { ASSERT_EQUAL(range_.average(), 7); }
  void TestMin() { ASSERT_EQUAL(range_.min(), 3); }
  void TestMax() { ASSERT_EQUAL(range_.max(), 11); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << range_;
    ASSERT_EQUAL(sout.str(), std::string("3, 4, 5, 6, 7, 8, 9, 10, 11"));
  }

 private:
  Range<int> range_ = {/*start=*/3, /*stop=*/11};
};

class IntRangeStepTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestLength();
    TestSum();
    TestAverage();
    TestMin();
    TestMax();
    TestStreamExtraction();
  }

  void TestLength() { ASSERT_EQUAL(range_.length(), size_t{5}); }
  void TestSum() { ASSERT_EQUAL(range_.sum(), 35); }
  void TestAverage() { ASSERT_EQUAL(range_.average(), 7); }
  void TestMin() { ASSERT_EQUAL(range_.min(), 3); }
  void TestMax() { ASSERT_EQUAL(range_.max(), 11); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << range_;
    ASSERT_EQUAL(sout.str(), std::string("3, 5, 7, 9, 11"));
  }

 private:
  Range<int> range_ = {/*start=*/3, /*stop=*/12, /*step=*/2};
};

class DoubleRangeStepTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestLength();
    TestSum();
    TestAverage();
    TestMin();
    TestMax();
    TestStreamExtraction();
  }

  void TestLength() { ASSERT_EQUAL(range_.length(), size_t{6}); }
  void TestSum() { ASSERT_EQUAL(range_.sum(), 82.5); }
  void TestAverage() { ASSERT_EQUAL(range_.average(), 13.75); }
  void TestMin() { ASSERT_EQUAL(range_.min(), 7.5); }
  void TestMax() { ASSERT_EQUAL(range_.max(), 20.0); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << range_;
    ASSERT_EQUAL(sout.str(), std::string("7.5, 10, 12.5, 15, 17.5, 20"));
  }

 private:
  Range<double> range_ = {/*start=*/7.5, /*stop=*/20.3, /*step=*/2.5};
};

class BackwardsIntRangeTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestLength();
    TestSum();
    TestAverage();
    TestMin();
    TestMax();
    TestStreamExtraction();
  }

  void TestLength() { ASSERT_EQUAL(range_.length(), size_t{5}); }
  void TestSum() { ASSERT_EQUAL(range_.sum(), 40); }
  void TestAverage() { ASSERT_EQUAL(range_.average(), 8); }
  void TestMin() { ASSERT_EQUAL(range_.min(), 4); }
  void TestMax() { ASSERT_EQUAL(range_.max(), 12); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << range_;
    ASSERT_EQUAL(sout.str(), std::string("12, 10, 8, 6, 4"));
  }

 private:
  Range<int> range_ = {/*start=*/12, /*stop=*/3, /*step=*/-2};
};

class BackwardsDoubleRangeTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestLength();
    TestSum();
    TestAverage();
    TestMin();
    TestMax();
    TestStreamExtraction();
  }

  void TestLength() { ASSERT_EQUAL(range_.length(), size_t{7}); }
  void TestSum() { ASSERT_EQUAL(range_.sum(), 87.5); }
  void TestAverage() { ASSERT_EQUAL(range_.average(), 12.5); }
  void TestMin() { ASSERT_EQUAL(range_.min(), 5.0); }
  void TestMax() { ASSERT_EQUAL(range_.max(), 20.0); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << range_;
    ASSERT_EQUAL(sout.str(), std::string("20, 17.5, 15, 12.5, 10, 7.5, 5"));
  }

 private:
  Range<double> range_ = {/*start=*/20.0, /*stop=*/4.0, /*step=*/-2.5};
};
