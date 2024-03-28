#include <stdlib.h>

#include <array>
#include <exception>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <typeinfo>

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_UNITTEST_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_UNITTEST_H_

#include "custom_libraries/unit_test/assertion.h"
#include "custom_libraries/unit_test/case.h"
#include "custom_libraries/unit_test/result.h"
#include "custom_libraries/unit_test/source_info.h"
#include "custom_libraries/unit_test/suite.h"

namespace rose {

const size_t kOutWidth = 100;

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

// Modified from a deleted user's answer to the following question:
// https://cplusplus.com/forum/beginner/273703/
inline std::string _Demangle(const std::string &mangled) {
  std::string cmd = "c++filt -t " + mangled;
  std::array<char, 128> buffer;
  std::stringstream result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                pclose);
  if (!pipe) return "";  // popen() failed.
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result << buffer.data();
  }
  const std::string str = result.str();
  const size_t length = str.size();
  return length ? str.substr(0, length - 1) : "";
}

// Forgive me for what I am about to do...

#define __TYPE_NAME__(arg) rose::_Demangle(typeid(arg).name())

#define ASSERT_EQUAL(arg0, arg1) \
  this->AssertEqual(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_ALMOST_EQUAL(arg0, arg1) \
  this->AssertAlmostEqual(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_NOT_EQUAL(arg0, arg1) \
  this->AssertNotEqual(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_NOT_ALMOST_EQUAL(arg0, arg1) \
  this->AssertNotAlmostEqual(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_GREATER(arg0, arg1) \
  this->AssertGreater(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_GREATER_EQUAL(arg0, arg1) \
  this->AssertGreaterEqual(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_LESS(arg0, arg1) \
  this->AssertLess(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_LESS_EQUAL(arg0, arg1) \
  this->AssertLessEqual(arg0, arg1, #arg0, #arg1, rose::SourceInfo())
#define ASSERT_TRUE(expression) \
  this->AssertTrue(expression, #expression, rose::SourceInfo())
#define ASSERT_FALSE(expression) \
  this->AssertFalse(expression, #expression, rose::SourceInfo())
#define ASSERT_THROWS(expression)                                    \
  std::optional<std::string> _exception_repr = std::nullopt;         \
  try {                                                              \
    static_cast<void>(expression);                                   \
  } catch (const std::exception &e) {                                \
    _exception_repr = __TYPE_NAME__(e);                              \
  } catch (...) {                                                    \
    _exception_repr = "non-standard exception";                      \
  }                                                                  \
  result()->Add(Assertion(rose::AssertionType::kThrows, #expression, \
                          _exception_repr, rose::SourceInfo()))
#define ASSERT_DOESNT_THROW(expression)                                   \
  std::optional<std::string> _exception_repr = std::nullopt;              \
  try {                                                                   \
    static_cast<void>(expression);                                        \
  } catch (const std::exception &e) {                                     \
    _exception_repr = __TYPE_NAME__(e);                                   \
  } catch (...) {                                                         \
    _exception_repr = "non-standard exception";                           \
  }                                                                       \
  result()->Add(Assertion(rose::AssertionType::kDoesntThrow, #expression, \
                          _exception_repr, rose::SourceInfo()))
#define ASSERT_THROWS_AS(exception_type, expression)                          \
  bool _passed = false;                                                       \
  std::optional<std::string> _exception_repr = std::nullopt;                  \
  try {                                                                       \
    static_cast<void>(expression);                                            \
  } catch (const exception_type &e) {                                         \
    _exception_repr = __TYPE_NAME__(e);                                       \
    _passed = true;                                                           \
  } catch (const std::exception &e) {                                         \
    _exception_repr = __TYPE_NAME__(e);                                       \
  } catch (...) {                                                             \
    _exception_repr = "non-standard exception";                               \
  }                                                                           \
  result()->Add(Assertion(rose::AssertionType::kThrowsAs,                     \
                          _exception_repr.value_or("null"),                   \
                          std::string(#exception_type), _passed, #expression, \
                          #exception_type, rose::SourceInfo()))
#define ASSERT_DOESNT_THROW_AS(exception_type, expression)                    \
  bool _passed = true;                                                        \
  std::optional<std::string> _exception_repr = std::nullopt;                  \
  try {                                                                       \
    static_cast<void>(expression);                                            \
  } catch (const exception_type &e) {                                         \
    _exception_repr = __TYPE_NAME__(e);                                       \
    _passed = false;                                                          \
  } catch (const std::exception &e) {                                         \
    _exception_repr = __TYPE_NAME__(e);                                       \
  } catch (...) {                                                             \
    _exception_repr = "non-standard exception";                               \
  }                                                                           \
  result()->Add(Assertion(rose::AssertionType::kDoesntThrowAs,                \
                          _exception_repr.value_or("null"),                   \
                          std::string(#exception_type), _passed, #expression, \
                          #exception_type, rose::SourceInfo()))

}  // namespace rose

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_UNITTEST_H_
