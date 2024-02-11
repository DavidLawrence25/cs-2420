#include <iostream>
#include <memory>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/05_fifth_element/test_cases.h"
#include "no_brainers/05_linked_list/test_cases.h"  // Previous tests for completeness.

using rose::CommandLineFlags, rose::TestResult, rose::TestSuite;

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<EmptyLinkedListTest>());
  suite.Add(std::make_unique<IntLinkedListTest>());
  suite.Add(std::make_unique<StringLinkedListTest>());
  suite.Add(std::make_unique<FifthElementTest>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
