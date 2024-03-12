#ifndef CS2420_CUSTOMLIBRARIES_CYCLICINT_H_
#define CS2420_CUSTOMLIBRARIES_CYCLICINT_H_

namespace rose {

// Represents an integer bound between a minimum and maximum value.
// When incremented or decremented, the integer will behave as normal unless
// it steps outside the bounds, at which point it will wrap around to the other
// bound (i.e., going under the min will underflow to the max and going over the
// max will overflow to the min).
class CyclicInt {
 public:
  CyclicInt(int min, int max) {
    if (min <= max) {
      min_ = min;
      max_ = max;
    } else {
      min_ = max;
      max_ = min;
    }
    value_ = min_;
  }

  CyclicInt(const CyclicInt &other) = default;

  int value() const { return value_; }

  // Increments `value_` by one, overflowing to the minimum value if necessary.
  CyclicInt &operator++() {
    ++value_;
    if (value_ > max_) value_ = min_;
    return *this;
  }

  // Decrements `value_` by one, underflowing to the maximum value if necessary.
  CyclicInt &operator--() {
    --value_;
    if (value_ < min_) value_ = max_;
    return *this;
  }

 private:
  int min_;
  int max_;
  int value_;
};

}  // namespace rose

#endif  // CS2420_CUSTOMLIBRARIES_CYCLICINT_H_