#include <ostream>
#include <string>

#ifndef CS2420_NOBRAINERS_04PALINDROME_PALINDROME_H_
#define CS2420_NOBRAINERS_04PALINDROME_PALINDROME_H_

namespace rose {

// A slightly strange wrapper around a function that tests if a string is a
// palindrome or not.
class Palindrome {
 public:
  Palindrome(std::string sentence);

  bool is_palindrome() const;

  friend std::ostream &operator<<(std::ostream &out,
                                  const Palindrome &palindrome);

 private:
  // The raw sentence as given by the user.
  std::string sentence_;
  // The sentence reduced to lowercase letters a-z.
  std::string stripped_;
};

}  // namespace rose

#endif  // CS2420_NOBRAINERS_04PALINDROME_PALINDROME_H_
