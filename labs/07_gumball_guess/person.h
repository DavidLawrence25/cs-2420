#include <ostream>
#include <string>

#include "labs/07_gumball_guess/queue.h"

#ifndef CS2420_LABS_07GUMBALLGUESS_PERSON_H_
#define CS2420_LABS_07GUMBALLGUESS_PERSON_H_

namespace rose {

// Represents a simple person who can play a game about guessing how many
// candies are in a jar.
class Person {
 public:
  Person() = default;
  Person(std::string name, int guess) : name_(name), guess_(guess) {}
  Person(const Person &other) = default;
  virtual ~Person() = default;

  std::string name() const { return name_; }
  int guess() const { return guess_; }

  // Returns a subset of `players` where every person's guess is the minimum
  // distance from `num_candies`.
  static Queue<Person> FindWinners(int num_candies, Queue<Person> players);

  // Returns true if both people had the same guess.
  bool operator==(const Person &other) const { return guess_ == other.guess_; }
  // Returns true if the person's guess was `value`.
  bool operator==(const int value) const { return guess_ == value; }
  // Returns true if `person`'s guess was `value`.
  friend bool operator==(const int value, const Person &person) {
    return value == person.guess_;
  }

  // Returns true if the people had different guesses.
  bool operator!=(const Person &other) const { return guess_ != other.guess_; }
  // Returns true if the person's guess wasn't `value`.
  bool operator!=(const int value) const { return guess_ != value; }
  // Returns true if `person`'s guess wasn't `value`.
  friend bool operator!=(const int value, const Person &person) {
    return value != person.guess_;
  }

  // Returns true if the person guessed higher than `other`.
  bool operator>(const Person &other) const { return guess_ > other.guess_; }
  // Returns true if the person's guess was above `value`.
  bool operator>(const int value) const { return guess_ > value; }
  // Returns true if `value` is higher than `person`'s guess.
  friend bool operator>(const int value, const Person &person) {
    return value > person.guess_;
  }

  // Returns true if the person guessed the same as or higher than `other`.
  bool operator>=(const Person &other) const { return guess_ >= other.guess_; }
  // Returns true if the person's guess was the same as or higher than `value`.
  bool operator>=(const int value) const { return guess_ >= value; }
  // Returns true if `value` is the same as or higher than `person`'s guess.
  friend bool operator>=(const int value, const Person &person) {
    return value >= person.guess_;
  }

  // Returns true if the person guessed lower than `other`.
  bool operator<(const Person &other) const { return guess_ < other.guess_; }
  // Returns true if the person's guess was below `value`.
  bool operator<(const int value) const { return guess_ < value; }
  // Returns true if `value` is lower than `person`'s guess.
  friend bool operator<(const int value, const Person &person) {
    return value < person.guess_;
  }

  // Returns true if the person guessed the same as or lower than `other`.
  bool operator<=(const Person &other) const { return guess_ <= other.guess_; }
  // Returns true if the person's guess was the same as or lower than `value`.
  bool operator<=(const int value) const { return guess_ <= value; }
  // Returns true if `value` is the same as or lower than `person`'s guess.
  friend bool operator<=(const int value, const Person &person) {
    return value <= person.guess_;
  }

  friend std::ostream &operator<<(std::ostream &out, const Person &person) {
    out << person.name_ << ": " << person.guess_;
    return out;
  }

 private:
  std::string name_;
  // How many candies the person thinks are in the jar.
  int guess_;
};

}  // namespace rose

#endif  // CS2420_LABS_07GUMBALLGUESS_PERSON_H_
