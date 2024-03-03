#include "custom_libraries/unit_test/assertion.h"

#include <stdlib.h>

#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "custom_libraries/json_writer.h"

namespace rose {

Assertion::Assertion(AssertionType type, bool expression,
                     const std::string &repr, const std::string &case_name,
                     const std::string &func_name, size_t line) {
  type_ = type;
  arg0_ = expression ? "true" : "false";
  repr0_ = repr;
  if (type == AssertionType::kTrue) {
    passed_ = expression;
    arg1_ = repr1_ = "true";
  } else if (type == AssertionType::kFalse) {
    passed_ = !expression;
    arg1_ = repr1_ = "false";
  }
  case_name_ = case_name;
  func_name_ = func_name;
  line_ = line;
}

Assertion::Assertion(AssertionType type, const std::string &expression_repr,
                     std::optional<std::string> exception_repr,
                     const std::string &case_name, const std::string &func_name,
                     size_t line) {
  type_ = type;
  passed_ = !(exception_repr.has_value() ^ (type == AssertionType::kThrows));
  arg0_ = exception_repr.value_or("null");
  repr0_ = expression_repr;
  arg1_ = repr1_ = "std::exception";
  case_name_ = case_name;
  func_name_ = func_name;
  line_ = line;
}

template <typename T>
Assertion::Assertion(AssertionType type, T arg0, T arg1, bool passed,
                     const std::string &repr0, const std::string &repr1,
                     const std::string &case_name, const std::string &func_name,
                     size_t line) {
  type_ = type;
  passed_ = passed;

  std::stringstream out0;
  out0 << arg0;
  arg0_ = out0.str();

  std::stringstream out1;
  out1 << arg1;
  arg1_ = out1.str();

  repr0_ = repr0;
  repr1_ = repr1;
  case_name_ = case_name;
  func_name_ = func_name;
  line_ = line;
}

AssertionType Assertion::type() const { return type_; }
bool Assertion::passed() const { return passed_; }
std::string Assertion::arg0() const { return arg0_; }
std::string Assertion::arg1() const { return arg1_; }
std::string Assertion::repr0() const { return repr0_; }
std::string Assertion::repr1() const { return repr1_; }
std::string Assertion::case_name() const { return case_name_; }
std::string Assertion::func_name() const { return func_name_; }
size_t Assertion::line() const { return line_; }

AssertionType Assertion::GetOpposite(AssertionType type) {
  switch (type) {
    case AssertionType::kEqual:
      return AssertionType::kNotEqual;
    case AssertionType::kAlmostEqual:
      return AssertionType::kNotAlmostEqual;
    case AssertionType::kNotEqual:
      return AssertionType::kEqual;
    case AssertionType::kNotAlmostEqual:
      return AssertionType::kAlmostEqual;
    case AssertionType::kGreater:
      return AssertionType::kLessEqual;
    case AssertionType::kGreaterEqual:
      return AssertionType::kLess;
    case AssertionType::kLess:
      return AssertionType::kGreaterEqual;
    case AssertionType::kLessEqual:
      return AssertionType::kGreater;
    case AssertionType::kTrue:
      return AssertionType::kFalse;
    case AssertionType::kFalse:
      return AssertionType::kTrue;
    case AssertionType::kThrows:
      return AssertionType::kDoesntThrow;
    case AssertionType::kDoesntThrow:
      return AssertionType::kThrows;
    case AssertionType::kThrowsAs:
      return AssertionType::kDoesntThrowAs;
    case AssertionType::kDoesntThrowAs:
      return AssertionType::kThrowsAs;
    default:
      return AssertionType::kNull;  // Should never be reachable.
  }
}

std::string Assertion::GetWordRepr(AssertionType type) {
  switch (type) {
    case AssertionType::kEqual:
      return "equal";
    case AssertionType::kAlmostEqual:
      return "almost_equal";
    case AssertionType::kNotEqual:
      return "not_equal";
    case AssertionType::kNotAlmostEqual:
      return "not_almost_equal";
    case AssertionType::kGreater:
      return "greater";
    case AssertionType::kGreaterEqual:
      return "greater_equal";
    case AssertionType::kLess:
      return "less";
    case AssertionType::kLessEqual:
      return "less_equal";
    case AssertionType::kTrue:
      return "true";
    case AssertionType::kFalse:
      return "false";
    case AssertionType::kThrows:
      return "throws";
    case AssertionType::kDoesntThrow:
      return "doesnt_throw";
    case AssertionType::kThrowsAs:
      return "throws_as";
    case AssertionType::kDoesntThrowAs:
      return "doesnt_throw_as";
    default:
      return "";  // Should never be reachable.
  }
}

std::string Assertion::GetOperationRepr(AssertionType type) {
  switch (type) {
    case AssertionType::kEqual:
      return " == ";
    case AssertionType::kAlmostEqual:
      return " \u2248\u2248 ";
    case AssertionType::kNotEqual:
      return " != ";
    case AssertionType::kNotAlmostEqual:
      return " !\u2248 ";
    case AssertionType::kGreater:
      return " > ";
    case AssertionType::kGreaterEqual:
      return " >= ";
    case AssertionType::kLess:
      return " < ";
    case AssertionType::kLessEqual:
      return " <= ";
    case AssertionType::kTrue:
      return " == ";  // expression == true
    case AssertionType::kFalse:
      return " == ";  // expression == false
    case AssertionType::kThrows:
      return " \u2192 ";
    case AssertionType::kDoesntThrow:
      return " \u219B ";
    case AssertionType::kThrowsAs:
      return " \u2192 ";
    case AssertionType::kDoesntThrowAs:
      return " \u219B ";
    default:
      return "";  // Should never be reachable.
  }
}

void Assertion::WriteTo(JsonWriter &writer) const {
  writer.BeginObject();

  writer.CreateString("name", func_name_);
  writer.CreateInt("line", line_);
  writer.CreateString("assertion_type", GetWordRepr(type_));
  writer.CreateBool("passed", passed_);
  if (type_ == AssertionType::kTrue || type_ == AssertionType::kFalse) {
    writer.CreateString("expression", repr0_);
    writer.CreateString("value", arg0_);
  } else {
    writer.BeginObject("arg0");

    writer.CreateString("repr", repr0_);
    writer.CreateString("value", arg0_);

    writer.EndObject();

    writer.BeginObject("arg1");

    writer.CreateString("repr", repr1_);
    writer.CreateString("value", arg1_);

    writer.EndObject();
  }

  writer.EndObject();
}

std::ostream &operator<<(std::ostream &out, const Assertion &assertion) {
  out << std::string(80, '=') << '\n';
  out << (assertion.passed() ? "PASS: " : "FAIL: ") << assertion.case_name()
      << "::" << assertion.func_name() << " (at line " << assertion.line()
      << ")\n";
  out << std::string(80, '-') << '\n';
  out << "\tassert " << assertion.repr0()
      << Assertion::GetOperationRepr(assertion.type()) << assertion.repr1()
      << '\n';
  out << "\t==> " << assertion.arg0();
  if (assertion.passed()) {
    out << Assertion::GetOperationRepr(assertion.type());
  } else {
    out << Assertion::GetOperationRepr(
        Assertion::GetOpposite(assertion.type()));
  }
  out << assertion.arg1() << '\n';

  return out;
}

}  // namespace rose
