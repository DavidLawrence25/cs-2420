#include <ostream>
#include <string>

#ifndef CS2420_LABS_01DATE_DATE_H_
#define CS2420_LABS_01DATE_DATE_H_

namespace rose {

// Represents a calendar date.
class Date {
 public:
  // Initializes Date to Jan 1, 1970.
  Date() noexcept;
  // Initializes Date with `year`, sets month and day to `1`.
  Date(int year) noexcept;
  // Initializes Date with `year` and `month`, sets day to `1`.
  Date(int year, int month) noexcept;
  Date(int year, int month, int day) noexcept;
  Date(const Date &other) noexcept;

  // Returns a number uniquely identifying the Date.
  // Example: Date(2007, 2, 22).hash()
  //        = 0b00000000000011111010111001010110
  //            \_____________________/\__/\___/
  //                      2007           2   22
  int hash() const noexcept;

  void AddMonths(int n) noexcept;
  void AddDays(int n) noexcept;
  static bool IsLeapYear(int year) noexcept;
  // Returns a string representation in the format "Mon Day, Year".
  // Example: Date(2007, 2, 22).ToString()
  //        = "Feb 22, 2007"
  std::string ToString() const noexcept;
  static int DaysInMonth(int year, int month) noexcept;
  // Returns the day number.
  // Example: Date(2007, 2, 22).DayOfYear()
  //        = 31 + 22 = 53
  int DayOfYear() const noexcept;

  Date operator+(int days) const noexcept;
  bool operator==(const Date &other) const noexcept;
  bool operator!=(const Date &other) const noexcept;
  friend std::ostream &operator<<(std::ostream &out, const Date &date) noexcept;

 private:
  int year_, month_, day_;
};

}  // namespace rose

#endif  // CS2420_LABS_01DATE_DATE_H_
