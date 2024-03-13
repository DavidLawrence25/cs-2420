#include <iostream>

#ifndef CS2420_NOBRAINERS_08LPHASHTABLE_OUTOFSPACEERROR_H_
#define CS2420_NOBRAINERS_08LPHASHTABLE_OUTOFSPACEERROR_H_

namespace rose {

class OutOfSpaceError : public std::exception {
 public:
  explicit OutOfSpaceError(const char *message) : message_(message) {}
  explicit OutOfSpaceError(const std::string &message)
      : message_(message.c_str()) {}
  explicit OutOfSpaceError(std::string_view message)
      : message_(message.data()) {}

  const char *what() const noexcept override { return message_; }

 private:
  const char *message_;
};

}  // namespace rose

#endif  // CS2420_NOBRAINERS_08LPHASHTABLE_OUTOFSPACEERROR_H_
