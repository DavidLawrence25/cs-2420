#include "palindrome.h"

#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <stack>

namespace rose {

inline char __ToLower__(char c) {
  return (c >= 'A' && c <= 'Z') ? (c + 32) : c;
}

Palindrome::Palindrome(std::string sentence) : sentence_(sentence) {
  std::stringstream stripped;

  for (char c : sentence) {
    c = __ToLower__(c);
    if (c >= 'a' && c <= 'z') stripped << c;
  }

  stripped_ = stripped.str();
}

bool Palindrome::is_palindrome() const {
  std::stack<char> stack;
  std::queue<char> queue;

  for (const char c : stripped_) {
    stack.push(c);
    queue.push(c);
  }

  while (!stack.empty()) {
    if (stack.top() != queue.front()) return false;
    stack.pop();
    queue.pop();
  }

  return true;
}

std::ostream &operator<<(std::ostream &out, const Palindrome &palindrome) {
  out << '"' << palindrome.sentence_ << "\" is ";
  if (!palindrome.is_palindrome()) out << "not ";
  out << "a palindrome.";

  return out;
}

}  // namespace rose
