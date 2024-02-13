#include <iostream>
#include <memory>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/02_point_revisited/test_cases.h"

using rose::CommandLineFlags, rose::TestResult, rose::TestSuite;

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<PointIntTest>());
  suite.Add(std::make_unique<PointFloatTest>());
  suite.Add(std::make_unique<PointDoubleTest>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
