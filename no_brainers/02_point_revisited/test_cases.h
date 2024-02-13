#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/02_point_revisited/point.h"

using rose::Point, rose::TestCase, rose::TestResult;

class PointIntTest : public TestCase {
 public:
  void Repair() override { point_ = Point<int>(-10, 3); }
  void Run() override {
    TestAdd();
    TestIAdd();
    TestSub();
    TestISub();
    TestStreamInsertion();
    TestStreamExtraction();
  }

  void TestAdd() { ASSERT_EQUAL(point_ + Point(-5, 2), Point(-15, 5)); }

  void TestIAdd() {
    point_ += Point(-5, 1);
    ASSERT_EQUAL(point_, Point(-15, 4));
    Repair();
  }

  void TestSub() { ASSERT_EQUAL(point_ - Point(-9, -5), Point(-1, 8)); }

  void TestISub() {
    point_ -= Point(7, -9);
    ASSERT_EQUAL(point_, Point(-17, 12));
    Repair();
  }

  void TestStreamInsertion() {
    std::stringstream sin;
    sin << "-3 5";
    Point<int> temp;
    sin >> temp;
    ASSERT_EQUAL(temp, Point(-3, 5));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(-10, 3)"));
  }

 private:
  Point<int> point_ = {-10, 3};
};

class PointFloatTest : public TestCase {
 public:
  void Repair() override { point_ = Point<float>(4.28872f, -2.85902f); }
  void Run() override {
    TestAdd();
    TestIAdd();
    TestSub();
    TestISub();
    TestStreamInsertion();
    TestStreamExtraction();
  }

  void TestAdd() {
    ASSERT_EQUAL(point_ + Point(-7.39939f, -9.96624f),
                 Point(-3.11067f, -12.82526f));
  }

  void TestIAdd() {
    point_ += Point(-1.146f, 8.24769f);
    ASSERT_EQUAL(point_, Point(3.14272f, 5.38867f));
    Repair();
  }

  void TestSub() {
    ASSERT_EQUAL(point_ - Point(-2.11476f, 4.44554f),
                 Point(6.40348f, -7.30456f));
  }

  void TestISub() {
    point_ -= Point(6.57337f, 0.12363f);
    ASSERT_EQUAL(point_, Point(-2.28465f, -2.98265f));
    Repair();
  }

  void TestStreamInsertion() {
    std::stringstream sin;
    Point<float> temp;
    sin << "6.87687 -2.87384";
    sin >> temp;
    ASSERT_EQUAL(temp, Point(6.87687f, -2.87384f));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(4.28872, -2.85902)"));
  }

 private:
  Point<float> point_ = {4.28872f, -2.85902f};
};

class PointDoubleTest : public TestCase {
 public:
  void Repair() override { point_ = Point(-0.59463, -2.93935); }
  void Run() override {
    TestAdd();
    TestIAdd();
    TestSub();
    TestISub();
    TestStreamInsertion();
    TestStreamExtraction();
  }

  void TestAdd() {
    ASSERT_EQUAL(point_ + Point(-7.62866, 7.13692), Point(-8.22329, 4.19757));
  }

  void TestIAdd() {
    point_ += Point(4.18262, -4.2021);
    ASSERT_EQUAL(point_, Point(3.58799, -7.14145));
    Repair();
  }

  void TestSub() {
    ASSERT_EQUAL(point_ - Point(4.26669, 9.23233), Point(-4.86132, -12.17168));
  }

  void TestISub() {
    point_ -= Point<double>(-8.99344, 6.36657);
    ASSERT_EQUAL(point_, Point(8.39881, -9.30592));
    Repair();
  }

  void TestStreamInsertion() {
    std::stringstream sin;
    Point<double> temp;
    sin << "6.75038 -6.85373";
    sin >> temp;
    ASSERT_EQUAL(temp, Point(6.75038, -6.85373));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(-0.59463, -2.93935)"));
  }

 private:
  Point<double> point_ = {-0.59463, -2.93935};
};
