#include <stdlib.h>

#include <optional>
#include <ostream>
#include <string>

#include "custom_libraries/json_writer.h"

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_ASSERTION_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_ASSERTION_H_

namespace rose {

enum class AssertionType {
  kNull,  // Used to keep the compiler from complaining in switch statements.
  kEqual,
  kAlmostEqual,
  kNotEqual,
  kNotAlmostEqual,
  kGreater,
  kGreaterEqual,
  kLess,
  kLessEqual,
  kTrue,
  kFalse,
  kThrows,
  kDoesntThrow,
  kThrowsAs,
  kDoesntThrowAs
};

// Contains metadata about an assertion.
class Assertion {
 public:
  // Constructs a truthiness assertion.
  Assertion(AssertionType type, bool expression, const std::string &repr,
            const std::string &case_name, const std::string &func_name,
            size_t line);
  // Constructs a non-specific exception assertion.
  Assertion(AssertionType type, const std::string &expression_repr,
            std::optional<std::string> exception_repr,
            const std::string &case_name, const std::string &func_name,
            size_t line);
  // Constructs a binary assertion (e.g., equality).
  template <typename T>
  Assertion(AssertionType type, T arg0, T arg1, bool passed,
            const std::string &repr0, const std::string &repr1,
            const std::string &case_name, const std::string &func_name,
            size_t line);

  AssertionType type() const;
  bool passed() const;
  // Value of first argument converted to a string.
  std::string arg0() const;
  // Value of second argument converted to a string.
  std::string arg1() const;
  // Representation of first argument.
  std::string repr0() const;
  // Representation of second argument.
  std::string repr1() const;
  std::string case_name() const;
  std::string func_name() const;
  size_t line() const;

  static AssertionType GetOpposite(AssertionType type);
  static std::string GetWordRepr(AssertionType type);
  static std::string GetOperationRepr(AssertionType type);

  void WriteTo(JsonWriter &writer) const;

  friend std::ostream &operator<<(std::ostream &out,
                                  const Assertion &assertion);

 private:
  AssertionType type_;
  bool passed_;
  // Value of first argument converted to a string.
  std::string arg0_;
  // Value of second argument converted to a string.
  std::string arg1_;
  // Representation of first argument.
  std::string repr0_;
  // Representation of second argument.
  std::string repr1_;
  std::string case_name_;
  std::string func_name_;
  size_t line_;
};

}  // namespace rose

#include "custom_libraries/unit_test/assertion.cc"

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_ASSERTION_H_
