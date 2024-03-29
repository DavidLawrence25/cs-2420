#include <stdlib.h>

#include <memory>
#include <string>

#include "custom_libraries/unit_test/source_info.h"

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_CASE_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_CASE_H_

namespace rose {

class TestResult;  // Defined in "custom_libraries/unit_test/result.h"

// Runs a series of related test functions defined by the user.
class TestCase {
 public:
  virtual ~TestCase() = default;

  std::shared_ptr<TestResult> result() const { return result_; }
  void set_result(std::shared_ptr<TestResult> result) { result_ = result; }

  // Resets any member variables to their default values.
  // A derived definition may look something like this:
  //     void Repair() override {
  //       foo_ = 8;
  //       bar_ = 3.14159f;
  //       baz_ = "Hello, World!";
  //     }
  virtual void Repair() = 0;

  // Runs the test functions given in its definition and returns the result.
  // A derived definition may look like this:
  //     void Run() override {
  //       TestFoo();
  //       TestBar();
  //       TestBaz();
  //     }
  virtual void Run() = 0;

  template <typename T>
  void AssertEqual(T arg0, T arg1, const std::string &repr0,
                   const std::string &repr1, const SourceInfo &info);
  void AssertAlmostEqual(float arg0, float arg1, const std::string &repr0,
                         const std::string &repr1, const SourceInfo &info);
  void AssertAlmostEqual(double arg0, double arg1, const std::string &repr0,
                         const std::string &repr1, const SourceInfo &info);
  template <typename T>
  void AssertNotEqual(T arg0, T arg1, const std::string &repr0,
                      const std::string &repr1, const SourceInfo &info);
  void AssertNotAlmostEqual(float arg0, float arg1, const std::string &repr0,
                            const std::string &repr1, const SourceInfo &info);
  void AssertNotAlmostEqual(double arg0, double arg1, const std::string &repr0,
                            const std::string &repr1, const SourceInfo &info);
  template <typename T>
  void AssertGreater(T arg0, T arg1, const std::string &repr0,
                     const std::string &repr1, const SourceInfo &info);
  template <typename T>
  void AssertGreaterEqual(T arg0, T arg1, const std::string &repr0,
                          const std::string &repr1, const SourceInfo &info);
  template <typename T>
  void AssertLess(T arg0, T arg1, const std::string &repr0,
                  const std::string &repr1, const SourceInfo &info);
  template <typename T>
  void AssertLessEqual(T arg0, T arg1, const std::string &repr0,
                       const std::string &repr1, const SourceInfo &info);
  void AssertTrue(bool expression, const std::string &repr,
                  const SourceInfo &info);
  void AssertFalse(bool expression, const std::string &repr,
                   const SourceInfo &info);

 private:
  std::shared_ptr<TestResult> result_;
};

}  // namespace rose

#include "custom_libraries/unit_test/case.cc"

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_CASE_H_
