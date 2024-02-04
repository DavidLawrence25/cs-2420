#include "custom_libraries/unit_test/assertion.h"

#include <stdlib.h>

#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "custom_libraries/json_writer.h"

namespace rose {

Assertion::Assertion(AssertionType type, bool expression, bool passed,
                     const std::string &repr, const std::string &case_name,
                     const std::string &func_name, size_t line) {
  type_ = type;
  passed_ = passed;
  arg0_ = expression ? "true" : "false";
  repr0_ = repr;
  // If another unary AssertionType were to be made, the following switch block
  // should be updated to include it.
  switch (type) {
    case kTrue:
      arg1_ = repr1_ = "true";
      break;
    case kFalse:
      arg1_ = repr1_ = "false";
      break;
    default:
      break;
  }
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

void Assertion::WriteTo(JsonWriter &writer) const {
  static const std::unordered_map<AssertionType, std::string> kAssertionReprs =
      {{kEqual, "equal"},        {kAlmostEqual, "almost_equal"},
       {kNotEqual, "not_equal"}, {kNotAlmostEqual, "not_almost_equal"},
       {kGreater, "greater"},    {kGreaterEqual, "greater_equal"},
       {kLess, "less"},          {kLessEqual, "less_equal"},
       {kTrue, "true"},          {kFalse, "false"}};

  writer.BeginObject();

  writer.CreateString("name", func_name_);
  writer.CreateInt("line", line_);
  writer.CreateString("assertion_type", kAssertionReprs.at(type_));
  writer.CreateBool("passed", passed_);
  if (type_ == kTrue || type_ == kFalse) {
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
  static const char kLine[82] =
      "------------------------------------------------------------------------"
      "--------\n";
  static const char kDoubleLine[82] =
      "========================================================================"
      "========\n";
  static const std::unordered_map<AssertionType, std::string> kOps = {
      {kEqual, " == "},    {kAlmostEqual, " ≈≈ "},
      {kNotEqual, " != "}, {kNotAlmostEqual, " !≈ "},
      {kGreater, " > "},   {kGreaterEqual, " >= "},
      {kLess, " < "},      {kLessEqual, " <= "},
      {kTrue, " == "},     {kFalse, " == "}};
  static const std::unordered_map<AssertionType, std::string> kOppositeOps = {
      {kEqual, " != "},          {kAlmostEqual, " !≈ "}, {kNotEqual, " == "},
      {kNotAlmostEqual, " ≈≈ "}, {kGreater, " <= "},     {kGreaterEqual, " < "},
      {kLess, " >= "},           {kLessEqual, " > "},    {kTrue, " != "},
      {kFalse, " != "}};

  out << kDoubleLine;
  out << (assertion.passed() ? "PASS: " : "FAIL: ") << assertion.case_name()
      << "::" << assertion.func_name() << " (at line " << assertion.line()
      << ")\n";
  out << kLine;
  out << "\tassert " << assertion.repr0() << kOps.at(assertion.type())
      << assertion.repr1() << '\n';
  out << "\t==> " << assertion.arg0()
      << (assertion.passed() ? kOps : kOppositeOps).at(assertion.type())
      << assertion.arg1() << '\n';

  return out;
}

}  // namespace rose
