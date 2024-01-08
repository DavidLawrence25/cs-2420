#include "number_utils.h"

#include <unordered_map>

namespace rose {

// Calculates the square root of `x`, rounded down to the nearest integer.
// If `x < 0`, returns `x`.
int FloorSqrt(int x) {
  if (x == 0 || x == 1) return x;

  int left_bound = 1, right_bound = x;
  while (left_bound <= right_bound) {
    // This roundabout way of calculating the arithmetic mean
    // helps prevent an integer overflow.
    int middle_value = left_bound + (right_bound - left_bound) * 0.5;

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
std::unordered_set<int> FactorsOf(int x) {
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
bool IsPrime(int x) {
  if (x <= 1) return false;

  const int kUpperBound = FloorSqrt(x);
  for (int i = 2; i <= kUpperBound; ++i) {
    if (x % i == 0) return false;
  }

  return true;
}

// Returns true if `str` represents the number 0.
bool IsZero(std::string str) { return kZeros.find(str) != kZeros.end(); }

// Returns the value of a string `str`, interpreted as an integer in base 10.
// If no suitable conversion can be made, returns 0.
int StringToInt(std::string str) {
  const std::unordered_map<char, int> kDigits = {
      {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
      {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};
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
      if (kDigits.find(c) == kDigits.end()) return 0;
      x = 10 * x + kDigits.at(c);
      seen_digit = true;
    }
  }

  return is_negative ? -x : x;
}

// Returns the value of a string `str`, interpreted as an double in base 10.
// If no suitable conversion can be made, returns 0.0.
double StringToDouble(std::string str) {
  const std::unordered_map<char, int> kDigits = {
      {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
      {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};
  bool seen_digit = false;
  bool seen_radix_point = false;
  bool seen_sign = false;
  bool is_negative = false;
  double x = 0.0;
  int radix_point_index = str.length() - 1;

  // Note that the index is necessary to properly process the radix point.
  for (int i = 0; i < str.length(); ++i) {
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
      radix_point_index = i;
      seen_radix_point = true;
    } else {
      if (seen_sign || kDigits.find(c) == kDigits.end()) return 0.0;
      x = 10.0 * x + kDigits.at(c);
      seen_digit = true;
    }
  }

  int power = 1 + radix_point_index - str.length();
  x *= pow(10, power);

  return is_negative ? -x : x;
}

}  // namespace rose
