#include "custom_libraries/unit_test/assertion.h"

#include <stdlib.h>

#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "custom_libraries/json_writer.h"
#include "custom_libraries/unit_test/source_info.h"

namespace rose {

Assertion::Assertion(AssertionType type, bool expression,
                     const std::string &repr, const SourceInfo &info)
    : type_(type),
      arg0_(expression ? "true" : "false"),
      repr0_(repr),
      info_(info) {
  if (type == AssertionType::kTrue) {
    passed_ = expression;
    arg1_ = repr1_ = "true";
  } else if (type == AssertionType::kFalse) {
    passed_ = !expression;
    arg1_ = repr1_ = "false";
  }
}

Assertion::Assertion(AssertionType type, const std::string &expression_repr,
                     std::optional<std::string> exception_repr,
                     const SourceInfo &info)
    : type_(type),
      arg0_(exception_repr.value_or("null")),
      repr0_(expression_repr),
      info_(info) {
  passed_ = !(exception_repr.has_value() ^ (type == AssertionType::kThrows));
  arg1_ = repr1_ = "std::exception";
}

template <typename T>
Assertion::Assertion(AssertionType type, T arg0, T arg1, bool passed,
                     const std::string &repr0, const std::string &repr1,
                     const SourceInfo &info)
    : type_(type), passed_(passed), repr0_(repr0), repr1_(repr1), info_(info) {
  std::stringstream out0;
  out0 << arg0;
  arg0_ = out0.str();

  std::stringstream out1;
  out1 << arg1;
  arg1_ = out1.str();
}

AssertionType Assertion::GetOpposite(AssertionType type) {
  using enum AssertionType;
  switch (type) {
    case kEqual:
      return kNotEqual;
    case kAlmostEqual:
      return kNotAlmostEqual;
    case kNotEqual:
      return kEqual;
    case kNotAlmostEqual:
      return kAlmostEqual;
    case kGreater:
      return kLessEqual;
    case kGreaterEqual:
      return kLess;
    case kLess:
      return kGreaterEqual;
    case kLessEqual:
      return kGreater;
    case kTrue:
      return kFalse;
    case kFalse:
      return kTrue;
    case kThrows:
      return kDoesntThrow;
    case kDoesntThrow:
      return kThrows;
    case kThrowsAs:
      return kDoesntThrowAs;
    case kDoesntThrowAs:
      return kThrowsAs;
    default:
      return kNull;  // Should never be reachable.
  }
}

std::string Assertion::GetWordRepr(AssertionType type) {
  using enum AssertionType;
  switch (type) {
    case kEqual:
      return "equal";
    case kAlmostEqual:
      return "almost_equal";
    case kNotEqual:
      return "not_equal";
    case kNotAlmostEqual:
      return "not_almost_equal";
    case kGreater:
      return "greater";
    case kGreaterEqual:
      return "greater_equal";
    case kLess:
      return "less";
    case kLessEqual:
      return "less_equal";
    case kTrue:
      return "true";
    case kFalse:
      return "false";
    case kThrows:
      return "throws";
    case kDoesntThrow:
      return "doesnt_throw";
    case kThrowsAs:
      return "throws_as";
    case kDoesntThrowAs:
      return "doesnt_throw_as";
    default:
      return "";  // Should never be reachable.
  }
}

std::string Assertion::GetOperationRepr(AssertionType type) {
  using enum AssertionType;
  switch (type) {
    case kEqual:
      return " == ";
    case kAlmostEqual:
      return " \u2248\u2248 ";
    case kNotEqual:
      return " != ";
    case kNotAlmostEqual:
      return " !\u2248 ";
    case kGreater:
      return " > ";
    case kGreaterEqual:
      return " >= ";
    case kLess:
      return " < ";
    case kLessEqual:
      return " <= ";
    case kTrue:
      return " == ";  // expression == true
    case kFalse:
      return " == ";  // expression == false
    case kThrows:
      return " \u2192 ";
    case kDoesntThrow:
      return " \u219B ";
    case kThrowsAs:
      return " \u2192 ";
    case kDoesntThrowAs:
      return " \u219B ";
    default:
      return "";  // Should never be reachable.
  }
}

void Assertion::WriteTo(JsonWriter &writer) const {
  writer.BeginObject();

  writer.CreateString("name", func_name());
  writer.CreateString("file", source_file_name());
  writer.CreateInt("line", static_cast<int>(line()));
  writer.CreateInt("column", static_cast<int>(column()));
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
  static constexpr size_t out_width = 100;

  out << std::string(out_width, '=') << '\n';
  out << (assertion.passed() ? "PASS: " : "FAIL: ") << assertion.case_name()
      << "::" << assertion.func_name() << " (in "
      << assertion.source_file_name() << " at " << assertion.line() << ':'
      << assertion.column() << ")\n";
  out << std::string(out_width, '-') << '\n';
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
