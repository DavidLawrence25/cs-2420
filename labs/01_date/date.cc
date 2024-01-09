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
  month_ = month % 13;
  day_ = 1;
}

Date::Date(int year, int month, int day) noexcept {
  year_ = year;
  month_ = month % 13;
  day_ = day % (DaysInMonth(year_, month_) + 1);
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
  month_ = month + 1;
}

void Date::AddDays(int n) noexcept { *this = *this + n; }

bool Date::IsLeapYear(int year) noexcept {
  return !(year % 4 || (year % 100 == 0 && year % 400));
}

std::string Date::ToString() const noexcept {
  static const std::string kMonthNames[] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};
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

Date Date::operator+(int n) const noexcept {
  int day = DayOfYear() + n;
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
