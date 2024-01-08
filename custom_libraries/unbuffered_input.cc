#include "unbuffered_input.h"

#include <conio.h>

namespace rose {

char MakeUppercase(char letter) {
  return (letter >= 'a' && letter <= 'z') ? letter - 32 : letter;
}

char MakeLowercase(char letter) {
  return (letter >= 'A' && letter <= 'Z') ? letter + 32 : letter;
}

bool IsAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool HasAlpha(std::string s) {
  bool seen = false;

  for (char c : s) {
    if (IsAlpha(c)) {
      seen = true;
      break;
    }
  }

  return seen;
}

bool IsNum(char c) { return (c >= '0' && c <= '9'); }

bool HasNum(std::string s) {
  bool seen = false;

  for (char c : s) {
    if (IsNum(c)) {
      seen = true;
      break;
    }
  }

  return seen;
}

bool IsSymbol(char c) {
  return (c >= ' ' && c <= '/') || (c >= ':' && c <= '@') ||
         (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

bool HasSymbol(std::string s) {
  bool seen = false;

  for (char c : s) {
    if (IsSymbol(c)) {
      seen = true;
      break;
    }
  }

  return seen;
}

char GetAsciiChar(bool allow_alpha, bool allow_num, bool allow_symbol,
                  LetterCase case_mode) {
  char this_char;

  while (true) {
    this_char = getch();

    if (allow_alpha && IsAlpha(this_char) || (allow_num && IsNum(this_char)) ||
        (allow_symbol && IsSymbol(this_char))) {
      if (case_mode == kUpper) this_char = MakeUppercase(this_char);
      if (case_mode == kLower) this_char = MakeLowercase(this_char);
      return this_char;
    }
  }
}

Direction GetDirection() {
  char this_char;

  while (true) {
    this_char = getch();

    if (this_char == 'w' || this_char == 'W') return kUp;
    if (this_char == 's' || this_char == 'S') return kDown;
    if (this_char == 'a' || this_char == 'A') return kLeft;
    if (this_char == 'd' || this_char == 'D') return kRight;
  }
}

}  // namespace rose
