#include <memory>
#include <vector>

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_SUITE_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_SUITE_H_

namespace rose {

class TestCase;    // Defined in "custom_libraries/unit_test/case.h"
class TestResult;  // Defined in "custom_libraries/unit_test/result.h"

// Runs a series of related test cases defined by the user.
// Example:
//     TestSuite suite;
//     suite.Add(std::make_unique<TestCaseA>());
//     suite.Add(std::make_unique<TestCaseB>());
//     suite.Add(std::make_unique<TestCaseC>());
//
//     auto result = std::make_shared<TestResult>();
//     suite.Run(result);
//     result->Log(std::cout);
class TestSuite {
 public:
  // Adds `test_case` to the suite, taking ownership of it in the process.
  void Add(std::unique_ptr<TestCase> test_case);
  // Runs all test cases and updates `result`.
  void Run(std::shared_ptr<TestResult> result);

 private:
  std::vector<std::unique_ptr<TestCase>> test_cases_;
};

}  // namespace rose

#include "custom_libraries/unit_test/suite.cc"

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_SUITE_H_
