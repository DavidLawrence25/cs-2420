#include "custom_libraries/number_utils.h"

#include <unordered_map>
#include <unordered_set>

namespace rose {

// Calculates the square root of `x`, rounded down to the nearest integer.
// If `x < 0`, returns `x`.
int FloorSqrt(const int x) noexcept {
  if (x == 0 || x == 1) return x;

  int left_bound = 1;
  int right_bound = x;
  while (left_bound <= right_bound) {
    // This roundabout way of calculating the arithmetic mean
    // helps prevent an integer overflow.
    int middle_value = left_bound + ((right_bound - left_bound) >> 1);

    if (middle_value == x / middle_value) {
      return middle_value;
    } else if (middle_value > x / middle_value) {
      right_bound = middle_value - 1;
    } else {
      left_bound = middle_value + 1;
    }
  }

  return right_bound;
}

// Returns an unordered set containing the factors of `x`.
// If `x < 1`, returns `{1, x}`.
std::unordered_set<int> FactorsOf(const int x) noexcept {
  if (x == 1) return std::unordered_set<int>{1};

  std::unordered_set<int> factors = {1, x};
  const int kUpperBound = FloorSqrt(x);
  for (int i = 2; i <= kUpperBound; ++i) {
    div_t division = div(x, i);
    if (division.rem == 0) {
      factors.insert(i);
      factors.insert(division.quot);
    }
  }

  return factors;
}

// Returns true when `x` is a prime number.
// An integer is prime if it has exactly two factors.
bool IsPrime(const int x) noexcept {
  if (x <= 1) return false;

  const int kUpperBound = FloorSqrt(x);
  for (int i = 2; i <= kUpperBound; ++i) {
    if (x % i == 0) return false;
  }

  return true;
}

// Returns the smallest prime number greater than or equal to `x`.
int NextPrime(const int x) noexcept {
  if (x <= 2) return 2;
  if (IsPrime(x)) return x;
  // Ensures `y` is always odd to avoid pointlessly searching even numbers.
  int y = (x % 2) ? x + 2 : x + 1;
  // Guaranteed to terminate within `ceil((x-3)/2)` iterations.
  for (; !IsPrime(y); y += 2)
    ;
  return y;
}

// Returns true if `str` represents the number 0.
bool IsZero(const std::string &str) noexcept { return kZeros.contains(str); }

// Returns true if `c` represents a digit from 0-9.
bool IsDigit(const char c) noexcept { return (c >= '0') && (c <= '9'); }

// Returns the numeric value of the given base-10 digit `digit`.
int DigitToInt(const char digit) noexcept { return digit - '0'; }

// Returns the value of a string `str`, interpreted as an integer in base 10.
// If no suitable conversion can be made, returns 0.
int StringToInt(const std::string &str) noexcept {
  bool seen_sign = false;
  bool seen_digit = false;
  bool is_negative = false;
  int x = 0;

  for (char c : str) {
    if (c == '-') {
      if (seen_sign || seen_digit) return 0;
      is_negative = true;
      seen_sign = true;
    } else if (c == '+') {
      if (seen_sign || seen_digit) return 0;
      seen_sign = true;
    } else {
      if (!IsDigit(c)) return 0;
      x = 10 * x + DigitToInt(c);
      seen_digit = true;
    }
  }

  return is_negative ? -x : x;
}

// Returns the value of a string `str`, interpreted as a float in base 10.
// If no suitable conversion can be made, returns 0.0f.
float StringToFloat(const std::string &str) noexcept {
  bool seen_digit = false;
  bool seen_radix_point = false;
  bool seen_sign = false;
  bool is_negative = false;
  float x = 0.0f;
  auto radix_point_index = static_cast<int>(str.length() - 1);

  // Note that the index is necessary to properly process the radix point.
  for (size_t i = 0; i < str.length(); ++i) {
    const char c = str[i];
    if (c == '-') {
      if (seen_digit || seen_radix_point || seen_sign) return 0.0f;
      is_negative = true;
      seen_sign = true;
    } else if (c == '+') {
      if (seen_digit || seen_radix_point || seen_sign) return 0.0f;
      seen_sign = true;
    } else if (c == '.') {
      if (seen_radix_point) return 0.0f;
      radix_point_index = static_cast<int>(i);
      seen_radix_point = true;
    } else {
      if (seen_sign || !IsDigit(c)) return 0.0f;
      x = 10.0f * x + static_cast<float>(DigitToInt(c));
      seen_digit = true;
    }
  }

  x *= pow(10.0f, static_cast<float>(1 + radix_point_index - str.length()));

  return is_negative ? -x : x;
}

// Returns the value of a string `str`, interpreted as a double in base 10.
// If no suitable conversion can be made, returns 0.0.
double StringToDouble(const std::string &str) noexcept {
  bool seen_digit = false;
  bool seen_radix_point = false;
  bool seen_sign = false;
  bool is_negative = false;
  double x = 0.0;
  auto radix_point_index = static_cast<int>(str.length() - 1);

  // Note that the index is necessary to properly process the radix point.
  for (size_t i = 0; i < str.length(); ++i) {
    const char c = str[i];
    if (c == '-') {
      if (seen_digit || seen_radix_point || seen_sign) return 0.0;
      is_negative = true;
      seen_sign = true;
    } else if (c == '+') {
      if (seen_digit || seen_radix_point || seen_sign) return 0.0;
      seen_sign = true;
    } else if (c == '.') {
      if (seen_radix_point) return 0.0;
      radix_point_index = static_cast<int>(i);
      seen_radix_point = true;
    } else {
      if (seen_sign || !IsDigit(c)) return 0.0;
      x = 10.0 * x + DigitToInt(c);
      seen_digit = true;
    }
  }

  x *= pow(10.0, 1 + radix_point_index - str.length());

  return is_negative ? -x : x;
}

// Returns true if `x == y`. (Please don't use unless absolutely necessary.)
bool ApproxEqual(const int x, const int y) noexcept { return x == y; }

// Returns true if `x` and `y` represent approximately the same value.
bool ApproxEqual(const float x, const float y) noexcept {
  static const float kBaseEpsilon = 1.0e-5f;
  const float kDistance = fabsf(x - y);
  if (kDistance <= kBaseEpsilon) return true;
  return kDistance <= (kBaseEpsilon * __max(fabsf(x), fabsf(y)));
}

// Returns true if `x` and `y` represent approximately the same value.
bool ApproxEqual(const double x, const double y) noexcept {
  static const double kBaseEpsilon = 1.0e-5;
  const double kDistance = fabs(x - y);
  if (kDistance <= kBaseEpsilon) return true;
  return kDistance <= (kBaseEpsilon * __max(fabs(x), fabs(y)));
}

}  // namespace rose
