#include <functional>
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

// Holds information about an assertion failure to be reported to the user.
struct AssertionFail {
  AssertionType type;
  // The name of the test function that failed.
  std::string test_name;
  // A string representation of the first argument's value.
  std::string value_a;
  // A string representation of the second argument's value.
  std::string value_b;
  // A string representation of the first argument, usually as an expression.
  std::string repr_a;
  // A string representation of the second argument, usually as an expression.
  std::string repr_b;
};

// Holds information about the results of a TestCase.
class TestResult {
 public:
  size_t tests_ran() const noexcept;

  // Adds an AssertionFail to the list of fails.
  void AddFail(AssertionType type, std::string test_name, std::string value_a,
               std::string value_b, std::string repr_a,
               std::string repr_b) noexcept;
  void IncrementTestCounter() noexcept;
  // Prints data about the fails to the terminal.
  void Report() const noexcept;

 private:
  std::vector<AssertionFail> fails_;
  size_t tests_ran_ = 0;
};

// Runs a series of related test functions defined by the user.
class TestCase {
 public:
  // Runs the tests given in its definition and returns the result.
  // Default implementation simply returns the result.
  // A derived definition may look like this:
  // `TestResult Run() {`
  // `  RunTest(foo, "foo");`
  // `  RunTest(bar, "bar");`
  // `  RunTest(baz, "baz");`
  // `  return result_;`
  // `}`
  TestResult Run();

  // Runs a class method `test_func` and updates the results accordingly.
  template <typename T>
  void RunTest(void (T::*test_func)(), std::string test_name) {
    test_name_ = test_name;
    std::invoke(test_func, static_cast<T *>(this));
    test_name_ = "";
    result_.IncrementTestCounter();
  }

  // Resets member variables used across tests to their original values.
  virtual void ResetGlobals() = 0;

  // Asserts that `a == b`, adding a fail if `a != b`.
  template <typename T>
  void AssertEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a != b) {
      result_.AddFail(kEqual, test_name_, value_a.str(), value_b.str(), repr_a,
                      repr_b);
    }
  }

  // Asserts that `a != b`, adding a fail if `a == b`.
  template <typename T>
  void AssertNotEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a == b) {
      result_.AddFail(kNotEqual, test_name_, value_a.str(), value_b.str(),
                      repr_a, repr_b);
    }
  }

  // Asserts that `a > b`, adding a fail if `a <= b`.
  template <typename T>
  void AssertGreater(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a <= b) {
      result_.AddFail(kGreater, test_name_, value_a.str(), value_b.str(),
                      repr_a, repr_b);
    }
  }

  // Asserts that `a >= b`, adding a fail if `a < b`.
  template <typename T>
  void AssertGreaterEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a < b) {
      result_.AddFail(kGreaterEqual, test_name_, value_a.str(), value_b.str(),
                      repr_a, repr_b);
    }
  }

  // Asserts that `a < b`, adding a fail if `a >= b`.
  template <typename T>
  void AssertLess(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a >= b) {
      result_.AddFail(kLess, test_name_, value_a.str(), value_b.str(), repr_a,
                      repr_b);
    }
  }

  // Asserts that `a <= b`, adding a fail if `a > b`.
  template <typename T>
  void AssertLessEqual(T a, T b, std::string repr_a, std::string repr_b) {
    std::stringstream value_a;
    std::stringstream value_b;
    value_a << a;
    value_b << b;
    if (a > b) {
      result_.AddFail(kLessEqual, test_name_, value_a.str(), value_b.str(),
                      repr_a, repr_b);
    }
  }

  // Asserts that `expression` is truthy, adding a fail if it isn't.
  void AssertTrue(bool expression, std::string repr) noexcept;
  // Asserts that `expression` is falsy, adding a fail if it isn't.
  void AssertFalse(bool expression, std::string repr) noexcept;

 protected:
  // The name of the test currently being ran.
  // Handled automatically by implementation and should not be tampered with.
  std::string test_name_;
  TestResult result_;
};

}  // namespace rose

#endif  // CS1410_CUSTOMLIBRARIES_TEST_H_
