#include "custom_libraries/unit_test/suite.h"

#include <memory>

#include "custom_libraries/unit_test/case.h"
#include "custom_libraries/unit_test/result.h"

namespace rose {

void TestSuite::Add(std::unique_ptr<TestCase> test_case) {
  test_cases_.push_back(std::move(test_case));
}

void TestSuite::Run(std::shared_ptr<TestResult> result) {
  for (auto &&test_case : test_cases_) {
    test_case->set_result(result);
    result->IncrementCaseCounter();
    test_case->Run();
  }
}

}  // namespace rose
