#include <stdlib.h>

#include <string>

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_UNITTEST_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_UNITTEST_H_

#include "custom_libraries/unit_test/assertion.h"
#include "custom_libraries/unit_test/case.h"
#include "custom_libraries/unit_test/result.h"
#include "custom_libraries/unit_test/suite.h"

namespace rose {

// Contains flags for various testing features.
struct CommandLineFlags {
  CommandLineFlags(int argc, const char *argv[]) {
    for (size_t i = 1; i < argc; ++i) {
      const std::string arg(argv[i]);
      if (arg == "-v") {
        verbose = true;
      } else if (arg == "-t") {
        log_txt = true;
      } else if (arg == "-j") {
        log_json = true;
      }
    }
  }

  bool verbose = false;
  bool log_txt = false;
  bool log_json = false;
};

// Modified from Andrew Prock's answer to the following question:
// https://stackoverflow.com/questions/1666802/is-there-a-class-macro-in-c
inline std::string _Class(const std::string &pretty_func) {
  size_t colons = pretty_func.find("::");
  if (colons == std::string::npos) return "";
  size_t begin = pretty_func.substr(0, colons).rfind(' ') + 1;
  size_t length = colons - begin;

  return pretty_func.substr(begin, length);
}

// Forgive me for what I am about to do...

#define __CLASS__ rose::_Class(__PRETTY_FUNCTION__)

#define ASSERT_EQUAL(arg0, arg1) \
  this->AssertEqual(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, __LINE__)
#define ASSERT_ALMOST_EQUAL(arg0, arg1)                                  \
  this->AssertAlmostEqual(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, \
                          __LINE__)
#define ASSERT_NOT_EQUAL(arg0, arg1) \
  this->AssertNotEqual(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, __LINE__)
#define ASSERT_NOT_ALMOST_EQUAL(arg0, arg1)                                 \
  this->AssertNotAlmostEqual(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, \
                             __LINE__)
#define ASSERT_GREATER(arg0, arg1) \
  this->AssertGreater(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, __LINE__)
#define ASSERT_GREATER_EQUAL(arg0, arg1)                                  \
  this->AssertGreaterEqual(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, \
                           __LINE__)
#define ASSERT_LESS(arg0, arg1) \
  this->AssertLess(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, __LINE__)
#define ASSERT_LESS_EQUAL(arg0, arg1) \
  this->AssertLessEqual(arg0, arg1, #arg0, #arg1, __CLASS__, __func__, __LINE__)
#define ASSERT_TRUE(expression) \
  this->AssertTrue(expression, #expression, __CLASS__, __func__, __LINE__)
#define ASSERT_FALSE(expression) \
  this->AssertFalse(expression, #expression, __CLASS__, __func__, __LINE__)

}  // namespace rose

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_UNITTEST_H_
