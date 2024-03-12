#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "custom_libraries/json_writer.h"

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_RESULT_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_RESULT_H_

namespace rose {

class Assertion;  // Defined in "custom_libraries/unit_test/assertion.h"

// Contains metadata about the results of a TestSuite.
class TestResult {
 public:
  int cases() const { return cases_; }
  int tests() const { return tests_; }
  int fails() const { return fails_; }

  void Add(Assertion assertion);
  void IncrementCaseCounter() { ++cases_; }

  std::map<std::string, std::vector<Assertion>, std::less<>> TestCaseGroups()
      const;

  // Logs information to the stream `out`. If `verbose` is true, all assertions
  // are logged, regardless of whether or not they passed.
  void Log(std::ostream &out, bool verbose) const;
  // Logs information to the file located at `file_path`, relative to the
  // current working directory.
  void LogTxt(const std::string &file_path) const;
  // Logs information to `writer`.
  void LogJson(JsonWriter &writer) const;
  // Logs information to the JSON file located at `file_path`, relative to the
  // current working directory.
  void LogJson(const std::string &file_path) const;

 private:
  int cases_ = 0;
  int tests_ = 0;
  int fails_ = 0;
  std::vector<Assertion> assertions_;
};

}  // namespace rose

#include "custom_libraries/unit_test/result.cc"

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_RESULT_H_
