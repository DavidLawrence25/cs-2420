#include <math.h>

#include <string>
#include <unordered_set>

#ifndef CS1410_CUSTOMLIBRARIES_NUMBERUTILS_H_
#define CS1410_CUSTOMLIBRARIES_NUMBERUTILS_H_

namespace rose {

// A set of various string representations of the number 0.
// Useful for checking whether or not a string conversion was successful.
const std::unordered_set<std::string> kZeros = {
    "0",
    "0.",
    "0.0",
    "0.00",
    "0.000",
    "0.0000",
    "0.00000",
    "0.000000",
    "0.0000000",
    "0.00000000",
    "0.000000000",
    "0.0000000000",
    "0.00000000000",
    "0.000000000000",
    "0.0000000000000",
    "0.00000000000000",
    "0.000000000000000",
    "+0",
    "+0.",
    "+0.0",
    "+0.00",
    "+0.000",
    "+0.0000",
    "+0.00000",
    "+0.000000",
    "+0.0000000",
    "+0.00000000",
    "+0.000000000",
    "+0.0000000000",
    "+0.00000000000",
    "+0.000000000000",
    "+0.0000000000000",
    "+0.00000000000000",
    "+0.000000000000000",
    "-0",
    "-0.",
    "-0.0",
    "-0.00",
    "-0.000",
    "-0.0000",
    "-0.00000",
    "-0.000000",
    "-0.0000000",
    "-0.00000000",
    "-0.000000000",
    "-0.0000000000",
    "-0.00000000000",
    "-0.000000000000",
    "-0.0000000000000",
    "-0.00000000000000",
    "-0.000000000000000",
};

// Calculates the square root of `x`, rounded down to the nearest integer.
int FloorSqrt(const int x) noexcept;

// Returns an unordered set containing the factors of `x`.
std::unordered_set<int> FactorsOf(const int x) noexcept;

// Returns true when `x` is a prime number.
bool IsPrime(const int x) noexcept;

// Returns true if `str` represents the number 0.
inline bool IsZero(const std::string str) noexcept;

// Returns true if `c` represents a digit from 0-9.
inline bool IsDigit(const char c) noexcept;

// Returns the numeric value of the given base-10 digit `digit`.
inline int DigitToInt(const char digit) noexcept;

// Returns the value of a string `str`, interpreted as an integer in base 10.
int StringToInt(const std::string str) noexcept;

// Returns the value of a string `str`, interpreted as a float in base 10.
float StringToFloat(const std::string str) noexcept;

// Returns the value of a string `str`, interpreted as a double in base 10.
double StringToDouble(const std::string str) noexcept;

// Returns true if `x == y`. (Please don't use unless absolutely necessary.)
bool ApproxEqual(const int x, const int y) noexcept;

// Returns true if `x` and `y` represent approximately the same value.
bool ApproxEqual(const float x, const float y) noexcept;

// Returns true if `x` and `y` represent approximately the same value.
bool ApproxEqual(const double x, const double y) noexcept;

}  // namespace rose

#endif  // CS1410_CUSTOMLIBRARIES_NUMBERUTILS_H_