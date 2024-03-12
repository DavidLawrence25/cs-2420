#include "custom_libraries/unit_test/case.h"

#include <math.h>

#include <any>
#include <memory>
#include <optional>

#include "custom_libraries/unit_test/assertion.h"
#include "custom_libraries/unit_test/result.h"

namespace rose {

template <typename T>
void TestCase::AssertEqual(T arg0, T arg1, const std::string &repr0,
                           const std::string &repr1, const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kEqual, arg0, arg1,
                         /*passed=*/(arg0 == arg1), repr0, repr1, info));
}

void TestCase::AssertAlmostEqual(float arg0, float arg1,
                                 const std::string &repr0,
                                 const std::string &repr1,
                                 const SourceInfo &info) {
  static const float kBaseEpsilon = 1.0e-5f;
  const float kDistance = fabsf(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = true;
  } else {
    passed = (kDistance <= (kBaseEpsilon * __max(fabsf(arg0), fabsf(arg1))));
  }
  result_->Add(Assertion(AssertionType::kAlmostEqual, arg0, arg1, passed, repr0,
                         repr1, info));
}

void TestCase::AssertAlmostEqual(double arg0, double arg1,
                                 const std::string &repr0,
                                 const std::string &repr1,
                                 const SourceInfo &info) {
  static const double kBaseEpsilon = 1.0e-5;
  const double kDistance = fabs(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = true;
  } else {
    passed = (kDistance <= (kBaseEpsilon * __max(fabs(arg0), fabs(arg1))));
  }
  result_->Add(Assertion(AssertionType::kAlmostEqual, arg0, arg1, passed, repr0,
                         repr1, info));
}

template <typename T>
void TestCase::AssertNotEqual(T arg0, T arg1, const std::string &repr0,
                              const std::string &repr1,
                              const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kNotEqual, arg0, arg1,
                         /*passed=*/(arg0 != arg1), repr0, repr1, info));
}

void TestCase::AssertNotAlmostEqual(float arg0, float arg1,
                                    const std::string &repr0,
                                    const std::string &repr1,
                                    const SourceInfo &info) {
  static const float kBaseEpsilon = 1.0e-5f;
  const float kDistance = fabsf(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = false;
  } else {
    passed = (kDistance > (kBaseEpsilon * __max(fabsf(arg0), fabsf(arg1))));
  }
  result_->Add(Assertion(AssertionType::kNotAlmostEqual, arg0, arg1, passed,
                         repr0, repr1, info));
}

void TestCase::AssertNotAlmostEqual(double arg0, double arg1,
                                    const std::string &repr0,
                                    const std::string &repr1,
                                    const SourceInfo &info) {
  static const double kBaseEpsilon = 1.0e-5;
  const double kDistance = fabs(arg0 - arg1);
  bool passed;
  if (kDistance <= kBaseEpsilon) {
    passed = false;
  } else {
    passed = (kDistance > (kBaseEpsilon * __max(fabs(arg0), fabs(arg1))));
  }
  result_->Add(Assertion(AssertionType::kNotAlmostEqual, arg0, arg1, passed,
                         repr0, repr1, info));
}

template <typename T>
void TestCase::AssertGreater(T arg0, T arg1, const std::string &repr0,
                             const std::string &repr1, const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kGreater, arg0, arg1, (arg0 > arg1),
                         repr0, repr1, info));
}

template <typename T>
void TestCase::AssertGreaterEqual(T arg0, T arg1, const std::string &repr0,
                                  const std::string &repr1,
                                  const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kGreaterEqual, arg0, arg1,
                         (arg0 >= arg1), repr0, repr1, info));
}

template <typename T>
void TestCase::AssertLess(T arg0, T arg1, const std::string &repr0,
                          const std::string &repr1, const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kLess, arg0, arg1, (arg0 < arg1), repr0,
                         repr1, info));
}

template <typename T>
void TestCase::AssertLessEqual(T arg0, T arg1, const std::string &repr0,
                               const std::string &repr1,
                               const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kLessEqual, arg0, arg1, (arg0 <= arg1),
                         repr0, repr1, info));
}

void TestCase::AssertTrue(bool expression, const std::string &repr,
                          const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kTrue, expression, repr, info));
}

void TestCase::AssertFalse(bool expression, const std::string &repr,
                           const SourceInfo &info) {
  result_->Add(Assertion(AssertionType::kFalse, expression, repr, info));
}

}  // namespace rose
