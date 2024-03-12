#include <stdlib.h>

#include <optional>
#include <ostream>
#include <regex>
#include <source_location>
#include <string>

#ifndef CS2420_CUSTOMLIBRARIES_UNITTEST_SOURCEINFO_H_
#define CS2420_CUSTOMLIBRARIES_UNITTEST_SOURCEINFO_H_

namespace rose {

// Contains info about the source code at the location of the object's creation.
// Acts as a convenience wrapper around std::source_location that discards some
// data for clarity.
struct SourceInfo {
  std::string file_name;
  std::optional<std::string> class_name;
  std::string func_name;
  size_t line;
  size_t column;

  explicit SourceInfo(
      const std::source_location location = std::source_location::current())
      : file_name(location.file_name()),
        line(location.line()),
        column(location.column()) {
    // Copy may prevent weird bugs?
    const std::string pretty_func = location.function_name();
    std::smatch parsed_func_name = ParseFuncName(pretty_func);
    if (parsed_func_name.size() == 2) {
      class_name = std::nullopt;
      func_name = parsed_func_name[1].str();
    } else if (parsed_func_name.size() == 3) {
      class_name = parsed_func_name[1].str();
      func_name = parsed_func_name[2].str();
    }
  }

  // Extracts the function/method name from `pretty_func`.
  // Also extracts the name of the class that owns the method if present.
  static std::smatch ParseFuncName(const std::string &pretty_func) {
    std::regex regex(
        "[a-zA-Z_][a-zA-Z_0-9]*\\s(?:([a-zA-Z_][a-zA-Z_0-9]*)::)*([a-zA-Z_][a-z"
        "A-Z_0-9]*)\\([^\\)]*\\)(?:\\s\\[[^\\]]*\\])?");
    std::smatch match;
    std::regex_search(pretty_func, match, regex);
    return match;
  }
};

}  // namespace rose

#endif  // CS2420_CUSTOMLIBRARIES_UNITTEST_SOURCEINFO_H_
