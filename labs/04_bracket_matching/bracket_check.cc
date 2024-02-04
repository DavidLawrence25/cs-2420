#include "labs/04_bracket_matching/bracket_check.h"

#include <optional>
#include <ostream>
#include <stack>
#include <string>

namespace rose {

BracketCheck::BracketCheck(const std::string &str)
    : pairs_(0), is_balanced_(true) {
  std::stack<char> open_brackets;
  for (const char c : str) {
    if (c == '(' || c == '[' || c == '{') {
      open_brackets.push(c);
    } else if (c == ')') {
      if (open_brackets.empty() || open_brackets.top() != '(') {
        is_balanced_ = false;
        pairs_ = std::nullopt;
        return;
      }
      open_brackets.pop();
      ++pairs_.value();
    } else if (c == ']') {
      if (open_brackets.empty() || open_brackets.top() != '[') {
        is_balanced_ = false;
        pairs_ = std::nullopt;
        return;
      }
      open_brackets.pop();
      ++pairs_.value();
    } else if (c == '}') {
      if (open_brackets.empty() || open_brackets.top() != '{') {
        is_balanced_ = false;
        pairs_ = std::nullopt;
        return;
      }
      open_brackets.pop();
      ++pairs_.value();
    }
  }
  if (!open_brackets.empty()) {
    is_balanced_ = false;
    pairs_ = std::nullopt;
  }
}

std::optional<int> BracketCheck::pairs() const { return pairs_; }
bool BracketCheck::is_balanced() const { return is_balanced_; }

std::ostream &operator<<(std::ostream &out, const BracketCheck &bracket_check) {
  if (!bracket_check.is_balanced_) out << "Not ";
  out << "Balanced";
  return out;
}

}  // namespace rose
