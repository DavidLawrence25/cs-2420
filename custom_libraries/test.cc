#include "test.h"

#include <functional>
#include <iostream>
#include <sstream>

using std::string;

namespace rose {

TestResult TestCase::Run() { return result_; }

void TestCase::RunTest(void (TestCase::*test_func)(), std::string test_name) {
  test_name_ = test_name;
  std::invoke(test_func, this);
  test_name_ = "";
  result_.IncrementTestCounter();
}

void TestCase::AssertTrue(bool expression, std::string repr) {
  if (!expression) result_.AddFailure(kTrue, test_name_, "false", "", repr, "");
}

void TestCase::AssertFalse(bool expression, std::string repr) {
  if (expression) result_.AddFailure(kFalse, test_name_, "true", "", repr, "");
}

size_t TestResult::tests_ran() { return tests_ran_; }

bool TestResult::was_successful() { return was_successful_; }

void TestResult::AddFailure(AssertionType type, string test_name,
                            string value_a, string value_b, string repr_a,
                            string repr_b) {
  failures_.push_back({type, test_name, value_a, value_b, repr_a, repr_b});
}

void TestResult::IncrementTestCounter() { ++tests_ran_; }

void TestResult::Report() {
  string test_text = (tests_ran_ != 1) ? " tests " : " test ";
  string failure_text = (failures_.size() != 1) ? " failures" : " failure";
  std::cout << string(80, '-') << '\n';
  std::cout << "Ran " << tests_ran_ << test_text << "with " << failures_.size()
            << failure_text << ".\n";
  for (AssertionFail failure : failures_) {
    std::cout << std::string(80, '=') << '\n';
    std::cout << "FAIL: " << failure.test_name << '\n';
    std::cout << failure.repr_a;
    if (failure.type == kEqual) {
      std::cout << " != " << failure.repr_b << '\n';
      std::cout << failure.value_a << " != " << failure.value_b << '\n';
    } else if (failure.type == kNotEqual) {
      std::cout << " == " << failure.repr_b << '\n';
      std::cout << failure.value_a << " == " << failure.value_b << '\n';
    } else if (failure.type == kGreater) {
      std::cout << " <= " << failure.repr_b << '\n';
      std::cout << failure.value_a << " <= " << failure.value_b << '\n';
    } else if (failure.type == kGreaterEqual) {
      std::cout << " < " << failure.repr_b << '\n';
      std::cout << failure.value_a << " < " << failure.value_b << '\n';
    } else if (failure.type == kLess) {
      std::cout << " >= " << failure.repr_b << '\n';
      std::cout << failure.value_a << " >= " << failure.value_b << '\n';
    } else if (failure.type == kLessEqual) {
      std::cout << " > " << failure.repr_b << '\n';
      std::cout << failure.value_a << " > " << failure.value_b << '\n';
    } else if (failure.type == kTrue) {
      std::cout << " == false\n";
      std::cout << failure.value_a << " == false\n";
    } else if (failure.type == kFalse) {
      std::cout << " == true\n";
      std::cout << failure.value_a << " == true\n";
    }
  }
}

}  // namespace rose
