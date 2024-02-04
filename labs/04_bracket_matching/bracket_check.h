#include <optional>
#include <ostream>
#include <string>

#ifndef CS2420_LABS_04BRACKETMATCHING_BRACKETCHECK_H_
#define CS2420_LABS_04BRACKETMATCHING_BRACKETCHECK_H_

namespace rose {

// Checks if a given string has a valid configuration of brackets.
// Brackets include the following characters: ()[]{}
class BracketCheck {
 public:
  // Runs the check upon construction, setting member variables as needed.
  // Does not store the input string past construction.
  BracketCheck(const std::string &str);

  std::optional<int> pairs() const;
  bool is_balanced() const;

  friend std::ostream &operator<<(std::ostream &out,
                                  const BracketCheck &bracket_check);

 private:
  bool is_balanced_;
  // Number of pairs. Not set if the brackets are unbalanced.
  std::optional<int> pairs_;
};

}  // namespace rose

#endif  // CS2420_LABS_04BRACKETMATCHING_BRACKETCHECK_H_
