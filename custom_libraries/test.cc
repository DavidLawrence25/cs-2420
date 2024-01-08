#include "test.h"

namespace rose {

TestResult TestCase::Run() {
  // TODO: Implement this.
}

template <typename T>
void TestCase::AssertEqual(T a, T b, std::string repr_a, std::string repr_b) {
  if (a != b) result_.AddFailure(kEqual, repr_a, repr_b);
}

template <typename T>
void TestCase::AssertNotEqual(
    T a, T b, std::string repr_a, std::string repr_b) {
  if (a == b) result_.AddFailure(kNotEqual, repr_a, repr_b);
}

template <typename T>
void TestCase::AssertGreater(T a, T b, std::string repr_a, std::string repr_b) {
  if (a <= b) result_.AddFailure(kGreater, repr_a, repr_b);
}

template <typename T>
void TestCase::AssertGreaterEqual(
    T a, T b, std::string repr_a, std::string repr_b) {
  if (a < b) result_.AddFailure(kGreaterEqual, repr_a, repr_b);
}

template <typename T>
void TestCase::AssertLess(T a, T b, std::string repr_a, std::string repr_b) {
  if (a >= b) result_.AddFailure(kLess, repr_a, repr_b);
}

template <typename T>
void TestCase::AssertLessEqual(
    T a, T b, std::string repr_a, std::string repr_b) {
  if (a > b) result_.AddFailure(kLessEqual, repr_a, repr_b);
}

void TestCase::AssertTrue(bool expression, std::string repr) {
  if (!expression) result_.AddFailure(kTrue, repr, "");
}

void TestCase::AssertFalse(bool expression, std::string repr) {
  if (expression) result_.AddFailure(kFalse, repr, "");
}

size_t TestResult::tests_ran() {
  return tests_ran_;
}

bool TestResult::was_successful() {
  return was_successful_;
}

void TestResult::AddFailure(
    AssertionType type, std::string repr_a, std::string repr_b) {
  failures_.push_back({type, repr_a, repr_b});
}

void TestResult::IncrementTestCounter() {
  ++tests_ran_;
}

}  // namespace rose
