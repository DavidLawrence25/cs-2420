#include <iostream>
#include <memory>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/06_recursion/test_cases.h"

using rose::CommandLineFlags, rose::TestResult, rose::TestSuite;

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<EmptySubsequenceTest>());
  suite.Add(std::make_unique<ProgrammingSubsequenceTest>());
  suite.Add(std::make_unique<AbcdeSubsequenceTest>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
