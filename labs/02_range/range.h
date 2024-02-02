#include <stdlib.h>

#include <iterator>
#include <ostream>

#ifndef CS2420_LABS_02RANGE_RANGE_H_
#define CS2420_LABS_02RANGE_RANGE_H_

namespace rose {

// Represents a set of equidistant numbers that lie between two other numbers.
// Includes the `stop` value (if possible), unlike Python's `range`.
template <typename Num>
class Range {
 public:
  Range() : start_(0), stop_(0), step_(1), n_(0) {}
  Range(Num stop) : start_(0), stop_(stop), step_(1), n_(0) {}
  Range(Num start, Num stop)
      : start_(start), stop_(stop), step_(1), n_(start) {}
  Range(Num start, Num stop, Num step)
      : start_(start), stop_(stop), step_(step), n_(start) {}

  // Returns the number of elements within the range.
  size_t length() const;
  // Returns the sum of all elements within the range.
  Num sum() const;
  // Returns the arithmetic mean of all elements within the range.
  Num average() const;
  // Returns the minimum possible element within the range.
  Num min() const;
  // Returns the maximum possible element within the range.
  Num max() const;

  // Sets `n` to the start of the range.
  // Must be called after iterating over the range to avoid future logic errors.
  void Reset();

  // Returns true if `n` is within the range.
  operator bool() const;
  // Returns `n`.
  Num const &operator*() const;
  // Returns the address of `n`.
  Num const *operator->() const;
  // Increments `n` by the step size.
  Range &operator++();
  // Extracts `range` into `out` as a string of numbers delimited by `, `.
  template <typename _Num>
  friend std::ostream &operator<<(std::ostream &out, Range<_Num> &range);

 private:
  Num start_;
  Num stop_;
  Num step_;

  Num n_;
};

}  // namespace rose

#include "labs/02_range/range.cc"

#endif  // CS2420_LABS_02RANGE_RANGE_H_
