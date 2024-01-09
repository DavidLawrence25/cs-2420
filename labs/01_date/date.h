#include <ostream>
#include <string>

#ifndef CS2420_LABS_01DATE_DATE_H_
#define CS2420_LABS_01DATE_DATE_H_

namespace rose {

class Date {
 public:
  Date(int year) noexcept;
  Date(int year, int month) noexcept;
  Date(int year, int month, int day) noexcept;
  Date(const Date &other) noexcept;

  int hash() const noexcept;

  void AddMonths(int n) noexcept;
  void AddDays(int n) noexcept;
  static bool IsLeapYear(int year) noexcept;
  std::string ToString() const noexcept;
  static int DaysInMonth(int year, int month) noexcept;
  int DayOfYear() const noexcept;

  Date operator+(int n) const noexcept;
  friend std::ostream &operator<<(std::ostream &out, const Date &date) noexcept;

 private:
  int year_, month_, day_;
};

}  // namespace rose

#endif  // CS2420_LABS_01DATE_DATE_H_
