#include <string>

#ifndef CS1410_CUSTOMLIBRARIES_UNBUFFEREDINPUT_H_
#define CS1410_CUSTOMLIBRARIES_UNBUFFEREDINPUT_H_

namespace rose {

// Represents a direction derived from the arrow keys or WASD.
enum Direction { kUp, kDown, kLeft, kRight };
// Represents the case mode for a string containing alphabetical characters.
enum LetterCase { kAuto, kLower, kUpper };

// Returns the uppercase version of the character `letter`.
char MakeUppercase(char letter);

// Returns the lowercase version of the character `letter`.
char MakeLowercase(char letter);

// Returns true if `c` is a letter in the English alphabet.
bool IsAlpha(char c);

// Returns true if there is >= 1 letter from the English alphabet in `s`.
bool HasAlpha(std::string s);

// Returns true if `c` is an Arabic numeral.
bool IsNum(char c);

// Returns true if there is >= 1 Arabic numeral in `s`.
bool HasNum(std::string s);

// Returns true if `c` is a non-alphanumeric symbol.
bool IsSymbol(char c);

// Returns true if there is >= 1 non-alphanumeric symbol in `s`.
bool HasSymbol(std::string s);

// Returns a character provided by the user based on the allowed character sets.
char GetAsciiChar(bool allow_alpha, bool allow_num, bool allow_symbol,
                  LetterCase case_mode);

// Returns a direction as specified by WASD.
Direction GetDirection();

// Returns a string of length `length` provided by the user based on the allowed
// character sets. Will wait until user confirms entry if `is_enter_required`.
std::string GetAsciiString(size_t length, bool is_enter_required,
                           bool allow_alpha, bool allow_num, bool allow_symbol,
                           LetterCase case_mode);

}  // namespace rose

#endif  // CS1410_CUSTOMLIBRARIES_UNBUFFEREDINPUT_H_
