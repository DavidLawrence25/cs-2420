#include "custom_libraries/unit_test/result.h"

#include <fstream>
#include <map>
#include <ostream>
#include <string>

#include "custom_libraries/json_writer.h"
#include "custom_libraries/unit_test/assertion.h"

namespace rose {

void TestResult::Add(Assertion assertion) {
  ++tests_;
  if (!assertion.passed()) ++fails_;
  assertions_.push_back(assertion);
}

std::map<std::string, std::vector<Assertion>, std::less<>>
TestResult::TestCaseGroups() const {
  using TestCaseGroup = std::vector<Assertion>;

  std::map<std::string, TestCaseGroup, std::less<>> groups;
  for (Assertion assertion : assertions_) {
    groups[assertion.case_name()].push_back(assertion);
  }
  return groups;
}

void TestResult::Log(std::ostream &out, bool verbose = false) const {
  for (Assertion assertion : assertions_) {
    if (!verbose && assertion.passed()) continue;
    out << assertion;
  }

  out << std::string(80, '-') << '\n';
  out << "Ran " << tests_ << " test" << ((tests_ == 1) ? " " : "s ") << "with "
      << fails_ << " fail" << ((fails_ == 1) ? ".\n" : "s.\n");
  out << '\n' << (fails_ ? "FAILED\n" : "PASSED\n");
}

void TestResult::LogTxt(const std::string &file_path) const {
  std::ofstream file(file_path);
  Log(/*out=*/file, /*verbose=*/true);
}

void TestResult::LogJson(JsonWriter &writer) const {
  using TestCaseGroup = std::vector<Assertion>;

  writer.BeginObject();

  writer.BeginObject("meta");

  writer.CreateInt("cases", cases_);
  writer.CreateInt("tests", tests_);
  writer.CreateInt("fails", fails_);

  writer.EndObject();

  writer.BeginObject("test_cases");

  std::map<std::string, TestCaseGroup, std::less<>> groups = TestCaseGroups();
  for (const auto &[case_name, group] : groups) {
    writer.BeginArray(case_name);

    for (const auto &assertion : group) assertion.WriteTo(writer);

    writer.EndArray();
  }

  writer.EndObject();

  writer.EndObject();
}

void TestResult::LogJson(const std::string &file_path) const {
  std::ofstream file(file_path);
  JsonWriter writer(file);
  LogJson(writer);
}

}  // namespace rose
