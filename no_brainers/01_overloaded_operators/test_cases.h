#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/01_overloaded_operators/point.h"

using rose::Point, rose::TestCase, rose::TestResult;

class PointTest1 : public TestCase {
 public:
  void Repair() override { point_ = Point(3, 4); }
  void Run() override {
    TestAdd();
    TestIAdd();
    TestSub();
    TestISub();
    TestStreamInsertion();
    TestStreamExtraction();
  }

  void TestAdd() { ASSERT_EQUAL(point_ + Point(-5, 2), Point(-2, 6)); }

  void TestIAdd() {
    point_ += Point(-5, 1);
    ASSERT_EQUAL(point_, Point(-2, 5));
    Repair();
  }

  void TestSub() { ASSERT_EQUAL(point_ - Point(-9, -5), Point(12, 9)); }

  void TestISub() {
    point_ -= Point(7, -9);
    ASSERT_EQUAL(point_, Point(-4, 13));
    Repair();
  }

  void TestStreamInsertion() {
    std::stringstream sin;
    sin << "1 9";
    Point temp;
    sin >> temp;
    ASSERT_EQUAL(temp, Point(1, 9));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(3, 4)"));
  }

 private:
  Point point_ = {3, 4};
};

class PointTest2 : public TestCase {
 public:
  void Repair() override { point_ = Point(-10, 3); }
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
    Point temp;
    sin >> temp;
    ASSERT_EQUAL(temp, Point(-3, 5));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(-10, 3)"));
  }

 private:
  Point point_ = {-10, 3};
};

class PointTest3 : public TestCase {
 public:
  void Repair() override { point_ = Point(-5, -10); }
  void Run() override {
    TestAdd();
    TestIAdd();
    TestSub();
    TestISub();
    TestStreamInsertion();
    TestStreamExtraction();
  }

  void TestAdd() { ASSERT_EQUAL(point_ + Point(-3, -3), Point(-8, -13)); }

  void TestIAdd() {
    point_ += Point(1, -10);
    ASSERT_EQUAL(point_, Point(-4, -20));
    Repair();
  }

  void TestSub() { ASSERT_EQUAL(point_ - Point(-2, -9), Point(-3, -1)); }

  void TestISub() {
    point_ -= Point(0, -1);
    ASSERT_EQUAL(point_, Point(-5, -9));
    Repair();
  }

  void TestStreamInsertion() {
    std::stringstream sin;
    sin << "-4 -6";
    Point temp;
    sin >> temp;
    ASSERT_EQUAL(temp, Point(-4, -6));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(-5, -10)"));
  }

 private:
  Point point_ = {-5, -10};
};

class PointTest4 : public TestCase {
 public:
  void Repair() override { point_ = Point(2, -4); }
  void Run() override {
    TestAdd();
    TestIAdd();
    TestSub();
    TestISub();
    TestStreamInsertion();
    TestStreamExtraction();
  }

  void TestAdd() { ASSERT_EQUAL(point_ + Point(-3, 1), Point(-1, -3)); }

  void TestIAdd() {
    point_ += Point(-7, -4);
    ASSERT_EQUAL(point_, Point(-5, -8));
    Repair();
  }

  void TestSub() { ASSERT_EQUAL(point_ - Point(-6, -1), Point(8, -3)); }

  void TestISub() {
    point_ -= Point(9, -6);
    ASSERT_EQUAL(point_, Point(-7, 2));
    Repair();
  }

  void TestStreamInsertion() {
    std::stringstream sin;
    sin << "6 -7";
    Point temp;
    sin >> temp;
    ASSERT_EQUAL(temp, Point(6, -7));
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << point_;
    ASSERT_EQUAL(sout.str(), std::string("(2, -4)"));
  }

 private:
  Point point_ = {2, -4};
};
