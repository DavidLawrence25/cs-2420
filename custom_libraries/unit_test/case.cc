#include "custom_libraries/unit_test/case.h"

#include <math.h>

#include <any>
#include <memory>
#include <optional>

#include "case.h"
#include "custom_libraries/unit_test/assertion.h"
#include "custom_libraries/unit_test/result.h"

namespace rose {

std::shared_ptr<TestResult> TestCase::result() /*const*/ { return result_; }

void TestCase::set_result(std::shared_ptr<TestResult> result) {
  result_ = result;
}

template <typename T>
void TestCase::AssertEqual(T arg0, T arg1, const std::string &repr0,
                           const std::string &repr1,
                           const std::string &case_name,
                           const std::string &func_name, size_t line) {
  result_->Add(Assertion(/*type=*/kEqual, arg0, arg1, /*passed=*/(arg0 == arg1),
                         repr0, repr1, case_name, func_name, line));
}

void TestCase::AssertAlmostEqual(float arg0, float arg1,
                                 const std::string &repr0,
                                 const std::string &repr1,
                                 const std::string &case_name,
                                 const std::string &func_name, size_t line) {
  static const float kBaseEpsilon = 1.0e-5f;
  const float kDistance = fabsf(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = true;
  } else {
    passed = (kDistance <= (kBaseEpsilon * __max(fabsf(arg0), fabsf(arg1))));
  }
  result_->Add(Assertion(/*type=*/kAlmostEqual, arg0, arg1, passed, repr0,
                         repr1, case_name, func_name, line));
}

void TestCase::AssertAlmostEqual(double arg0, double arg1,
                                 const std::string &repr0,
                                 const std::string &repr1,
                                 const std::string &case_name,
                                 const std::string &func_name, size_t line) {
  static const double kBaseEpsilon = 1.0e-5;
  const double kDistance = fabs(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = true;
  } else {
    passed = (kDistance <= (kBaseEpsilon * __max(fabs(arg0), fabs(arg1))));
  }
  result_->Add(Assertion(/*type=*/kAlmostEqual, arg0, arg1, passed, repr0,
                         repr1, case_name, func_name, line));
}

template <typename T>
void TestCase::AssertNotEqual(T arg0, T arg1, const std::string &repr0,
                              const std::string &repr1,
                              const std::string &case_name,
                              const std::string &func_name, size_t line) {
  result_->Add(Assertion(/*type=*/kNotEqual, arg0, arg1,
                         /*passed=*/(arg0 != arg1), repr0, repr1, case_name,
                         func_name, line));
}

void TestCase::AssertNotAlmostEqual(float arg0, float arg1,
                                    const std::string &repr0,
                                    const std::string &repr1,
                                    const std::string &case_name,
                                    const std::string &func_name, size_t line) {
  static const float kBaseEpsilon = 1.0e-5f;
  const float kDistance = fabsf(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = false;
  } else {
    passed = (kDistance > (kBaseEpsilon * __max(fabsf(arg0), fabsf(arg1))));
  }
  result_->Add(Assertion(/*type=*/kNotAlmostEqual, arg0, arg1, passed, repr0,
                         repr1, case_name, func_name, line));
}

void TestCase::AssertNotAlmostEqual(double arg0, double arg1,
                                    const std::string &repr0,
                                    const std::string &repr1,
                                    const std::string &case_name,
                                    const std::string &func_name, size_t line) {
  static const double kBaseEpsilon = 1.0e-5;
  const double kDistance = fabs(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = false;
  } else {
    passed = (kDistance > (kBaseEpsilon * __max(fabs(arg0), fabs(arg1))));
  }
  result_->Add(Assertion(/*type=*/kNotAlmostEqual, arg0, arg1, passed, repr0,
                         repr1, case_name, func_name, line));
}

template <typename T>
void TestCase::AssertGreater(T arg0, T arg1, const std::string &repr0,
                             const std::string &repr1,
                             const std::string &case_name,
                             const std::string &func_name, size_t line) {
  result_->Add(Assertion(/*type=*/kGreater, arg0, arg1, (arg0 > arg1), repr0,
                         repr1, case_name, func_name, line));
}

template <typename T>
void TestCase::AssertGreaterEqual(T arg0, T arg1, const std::string &repr0,
                                  const std::string &repr1,
                                  const std::string &case_name,
                                  const std::string &func_name, size_t line) {
  result_->Add(Assertion(/*type=*/kGreaterEqual, arg0, arg1, (arg0 >= arg1),
                         repr0, repr1, case_name, func_name, line));
}

template <typename T>
void TestCase::AssertLess(T arg0, T arg1, const std::string &repr0,
                          const std::string &repr1,
                          const std::string &case_name,
                          const std::string &func_name, size_t line) {
  result_->Add(Assertion(/*type=*/kLess, arg0, arg1, (arg0 < arg1), repr0,
                         repr1, case_name, func_name, line));
}

template <typename T>
void TestCase::AssertLessEqual(T arg0, T arg1, const std::string &repr0,
                               const std::string &repr1,
                               const std::string &case_name,
                               const std::string &func_name, size_t line) {
  result_->Add(Assertion(/*type=*/kLessEqual, arg0, arg1, (arg0 <= arg1), repr0,
                         repr1, case_name, func_name, line));
}

void TestCase::AssertTrue(bool expression, const std::string &repr,
                          const std::string &case_name,
                          const std::string &func_name, size_t line) {
  result_->Add(
      Assertion(/*type=*/kTrue, expression, repr, case_name, func_name, line));
}

void TestCase::AssertFalse(bool expression, const std::string &repr,
                           const std::string &case_name,
                           const std::string &func_name, size_t line) {
  result_->Add(
      Assertion(/*type=*/kFalse, expression, repr, case_name, func_name, line));
}

}  // namespace rose
