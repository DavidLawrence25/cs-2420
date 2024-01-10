#include "test.h"

#include <iostream>
#include <unordered_map>

namespace rose {

TestResult TestCase::Run() { return result_; }

void TestCase::AssertTrue(bool expression, std::string repr) noexcept {
  if (!expression) result_.AddFail(kTrue, test_name_, "false", "", repr, "");
}

void TestCase::AssertFalse(bool expression, std::string repr) noexcept {
  if (expression) result_.AddFail(kFalse, test_name_, "true", "", repr, "");
}

size_t TestResult::tests_ran() const noexcept { return tests_ran_; }

void TestResult::AddFail(AssertionType type, std::string test_name,
                         std::string value_a, std::string value_b,
                         std::string repr_a, std::string repr_b) noexcept {
  fails_.push_back({type, test_name, value_a, value_b, repr_a, repr_b});
}

void TestResult::IncrementTestCounter() noexcept { ++tests_ran_; }

void TestResult::Report() const noexcept {
  using std::cout, std::string, std::unordered_map;

  // Maps binary comparison operators to the string representation
  // of their opposite operator flanked by spaces.
  static const unordered_map<AssertionType, string> kOppositeOp = {
      {kEqual, " != "},       {kNotEqual, " == "}, {kGreater, " <= "},
      {kGreaterEqual, " < "}, {kLess, " >= "},     {kLessEqual, " > "}};
  // The number of fails.
  const size_t kFails = fails_.size();

  cout << string(80, '-') << '\n';
  // Slightly complex cout statements that handle pluralization.
  cout << "Ran " << tests_ran_ << ((tests_ran_ != 1) ? " tests" : " test");
  cout << " with " << kFails << ((kFails != 1) ? " fails.\n" : " fail.\n");

  for (AssertionFail fail : fails_) {
    cout << string(80, '=') << '\n';
    cout << "FAIL: " << fail.test_name << '\n';

    cout << fail.repr_a;
    if (fail.type == kTrue) {
      cout << " == false\n";
    } else if (fail.type == kFalse) {
      cout << " == true\n";
    } else {
      cout << kOppositeOp.at(fail.type) << fail.repr_b << '\n';
      cout << fail.value_a << kOppositeOp.at(fail.type) << fail.value_b << '\n';
    }
  }
}

}  // namespace rose
