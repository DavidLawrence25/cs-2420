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
int FloorSqrt(int x);

// Returns an unordered set containing the factors of `x`.
std::unordered_set<int> FactorsOf(int x);

// Returns true when `x` is a prime number.
bool IsPrime(int x);

// Returns true if `str` represents the number 0.
bool IsZero(std::string str);

// Returns the value of a string `str`, interpreted as an integer in base 10.
int StringToInt(std::string str);

// Returns the value of a string `str`, interpreted as an double in base 10.
double StringToDouble(std::string str);

}  // namespace rose

#endif  // CS1410_CUSTOMLIBRARIES_NUMBERUTILS_H_