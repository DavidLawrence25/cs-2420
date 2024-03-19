#include <iostream>
#include <memory>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/08_dynamic_hash_table/test_cases.h"

using rose::CommandLineFlags, rose::TestResult, rose::TestSuite;

int main(int argc, const char *argv[]) {
  CommandLineFlags flags(argc, argv);

  TestSuite suite;
  suite.Add(std::make_unique<HashTableConstructorTest>());
  suite.Add(std::make_unique<HashTableInsertTest>());
  suite.Add(std::make_unique<HashTableRemoveTest>());
  suite.Add(std::make_unique<HashTableClearTest>());
  suite.Add(std::make_unique<HashTableResizeTest>());
  suite.Add(std::make_unique<HashTableIndexTest>());
  suite.Add(std::make_unique<HashTableQuadProbeTest>());
  suite.Add(std::make_unique<HashTableDeepCopyTest>());
  suite.Add(std::make_unique<HashTableErrorTest>());
  suite.Add(std::make_unique<PrimeFunctionsTest>());

  auto result = std::make_shared<TestResult>();
  suite.Run(result);
  result->Log(std::cout, flags.verbose);
  if (flags.log_txt) result->LogTxt("log.txt");
  if (flags.log_json) result->LogJson("log.json");

  return 0;
}
