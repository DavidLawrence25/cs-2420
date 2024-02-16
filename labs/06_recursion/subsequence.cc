#include "labs/06_recursion/subsequence.h"

#include <ostream>
#include <string>
#include <string_view>

namespace rose {

bool Subsequence::IsSubsequence(std::string_view s) const {
  return IsSubsequence(s, /*remainder=*/sequence_);
}

bool Subsequence::IsSubsequence(std::string_view s,
                                std::string_view remainder) const {
  if (s.empty()) return true;
  if (remainder.empty()) return false;

  if (s[0] == remainder[0]) s.remove_prefix(1);
  remainder.remove_prefix(1);
  return IsSubsequence(s, remainder);
}

std::ostream &operator<<(std::ostream &out, const Subsequence &subsequence) {
  out << "Subsequence(" << subsequence.sequence_ << ')';
  return out;
}

}  // namespace rose
