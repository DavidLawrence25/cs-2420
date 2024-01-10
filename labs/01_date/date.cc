#include "date.h"

#include <sstream>

namespace rose {

Date::Date(int year) noexcept {
  year_ = year;
  month_ = 1;
  day_ = 1;
}

Date::Date(int year, int month) noexcept {
  year_ = year;
  month_ = ((month - 1) % 12) + 1;  // Corrects `month`.
  day_ = 1;
}

Date::Date(int year, int month, int day) noexcept {
  year_ = year;
  month_ = ((month - 1) % 12) + 1;                      // Corrects `month`.
  day_ = ((day - 1) % DaysInMonth(year_, month_)) + 1;  // Corrects `day`.
}

Date::Date(const Date &other) noexcept {
  year_ = other.year_;
  month_ = other.month_;
  day_ = other.day_;
}

int Date::hash() const noexcept { return (year_ << 9) | (month_ << 5) | day_; }

void Date::AddMonths(int n) noexcept {
  auto [year, month] = div(month_ + n - 1, 12);
  year_ += year;
  month_ = month + 1;  // `month` is on the interval [0, 11].
}

void Date::AddDays(int n) noexcept { *this = *this + n; }

bool Date::IsLeapYear(int year) noexcept {
  // Leap years must be...
  // 1. Divisible by 4.
  // 2. Not divisible by 100 UNLESS also divisible by 400.
  return !(year % 4 || (year % 100 == 0 && year % 400));
}

std::string Date::ToString() const noexcept {
  static const std::string kMonthNames[] = {"Jan", "Feb", "Mar", "Apr",
                                            "May", "Jun", "Jul", "Aug",
                                            "Sep", "Oct", "Nov", "Dec"};
  std::stringstream output;
  output << kMonthNames[month_ - 1] << ' ' << day_ << ", " << year_;
  return output.str();
}

int Date::DaysInMonth(int year, int month) noexcept {
  static const int kDaysInMonth[] = {
      31, IsLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return kDaysInMonth[(month - 1) % 12];
}

int Date::DayOfYear() const noexcept {
  int days = 0;
  for (int month = 1; month < month_; ++month) {
    days += DaysInMonth(year_, month);
  }
  days += day_;
  return days;
}

Date Date::operator+(int days) const noexcept {
  int day = DayOfYear() + days;
  // Corrects the value of `day` and adjusts `year` and `month` accordingly.
  int year = year_;
  int month = 1;

  while (day > DaysInMonth(year, month)) {
    day -= DaysInMonth(year, month);
    ++month;
    if (month > 12) {
      month = 1;
      ++year;
    }
  }

  return {year, month, day};
}

std::ostream &operator<<(std::ostream &out, const Date &date) noexcept {
  out << date.ToString();
  return out;
}

}  // namespace rose
