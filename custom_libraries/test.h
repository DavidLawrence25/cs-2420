#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifndef CS1410_CUSTOMLIBRARIES_TEST_H_
#define CS1410_CUSTOMLIBRARIES_TEST_H_

namespace rose {

enum AssertionType {
  kEqual,
  kNotEqual,
  kGreater,
  kGreaterEqual,
  kLess,
  kLessEqual,
  kTrue,
  kFalse
};

struct AssertionFail {
  AssertionType type;
  std::string test_name;
  std::string value_a;
  std::string value_b;
  std::string repr_a;
  std::string repr_b;
};

class TestResult {
 public:
  size_t tests_ran();
  bool was_successful();

  void AddFailure(AssertionType type, std::string test_name,
                  std::string value_a, std::string value_b, std::string repr_a,
                  std::string repr_b);
  void IncrementTestCounter();
  void Report();

 private:
  std::vector<AssertionFail> failures_;
  size_t tests_ran_ = 0;
  bool was_successful_ = true;
};

class TestCase {
 public:
  TestResult Run();
  void RunTest(void (TestCase::*test_func)(), std::string test_name);

  template <typename T>
  void AssertEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a != b)
      result_.AddFailure(kEqual, test_name_, value_a.str(), value_b.str(),
                         repr_a, repr_b);
  }

  template <typename T>
  void AssertNotEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a == b)
      result_.AddFailure(kNotEqual, test_name_, value_a.str(), value_b.str(),
                         repr_a, repr_b);
  }

  template <typename T>
  void AssertGreater(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a <= b)
      result_.AddFailure(kGreater, test_name_, value_a.str(), value_b.str(),
                         repr_a, repr_b);
  }

  template <typename T>
  void AssertGreaterEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a < b)
      result_.AddFailure(kGreaterEqual, test_name_, value_a.str(),
                         value_b.str(), repr_a, repr_b);
  }

  template <typename T>
  void AssertLess(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a >= b)
      result_.AddFailure(kLess, test_name_, value_a.str(), value_b.str(),
                         repr_a, repr_b);
  }

  template <typename T>
  void AssertLessEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a > b)
      result_.AddFailure(kLessEqual, test_name_, value_a.str(), value_b.str(),
                         repr_a, repr_b);
  }

  void AssertTrue(bool expression, std::string repr);
  void AssertFalse(bool expression, std::string repr);

 protected:
  std::string name_;
  std::string test_name_;
  TestResult result_;
};

}  // namespace rose

#endif  // CS1410_CUSTOMLIBRARIES_TEST_H_
