#include <ostream>
#include <string>
#include <string_view>

#ifndef CS2420_LABS_06RECURSION_SUBSEQUENCE_H_
#define CS2420_LABS_06RECURSION_SUBSEQUENCE_H_

namespace rose {

// Wraps a method that checks if one string is a subsequence of another.
// A subsequence is defined as a sequence of characters that is attainable
// solely by deleting characters in the original sequence.
// Examples:
//   "ace" is a subsequence of "abcde".
//   "bad" is not a subsequence of "abcde".
//   "pin" is a subsequence of "programming".
class Subsequence {
 public:
  Subsequence() = default;
  Subsequence(const std::string &sequence) : sequence_(sequence) {}

  // Returns true if `s` is a subsequence of the stored sequence.
  bool IsSubsequence(std::string_view s) const;
  // Returns true if `s` is a subsequence of `remainder`.
  bool IsSubsequence(std::string_view s, std::string_view remainder) const;

  friend std::ostream &operator<<(std::ostream &out,
                                  const Subsequence &subsequence);

 private:
  std::string sequence_;
};

}  // namespace rose

#endif  // CS2420_LABS_06RECURSION_SUBSEQUENCE_H_
