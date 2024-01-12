#include "range.h"

#include <math.h>
#include <stdlib.h>

#include <ostream>

namespace rose {

template <typename Num>
Range<Num>::Range(Num stop) {
  start_ = 0;
  stop_ = stop;
  step_ = 1;
  n_ = 0;
}

template <typename Num>
Range<Num>::Range(Num start, Num stop) {
  start_ = start;
  stop_ = stop;
  step_ = 1;
  n_ = start;
}

template <typename Num>
Range<Num>::Range(Num start, Num stop, Num step) {
  start_ = start;
  stop_ = stop;
  step_ = step;
  n_ = start;
}

template <typename Num>
size_t Range<Num>::length() const {
  return 1 + floor((stop_ - start_) / step_);
}

template <typename Num>
Num Range<Num>::sum() const {
  return length() * average();
}

template <typename Num>
Num Range<Num>::average() const {
  return (min() + max()) / 2;
}

template <typename Num>
Num Range<Num>::min() const {
  return step_ > 0 ? start_ : start_ + step_ * (length() - 1);
}

template <typename Num>
Num Range<Num>::max() const {
  return step_ < 0 ? start_ : start_ + step_ * (length() - 1);
}

template <typename Num>
void Range<Num>::Reset() {
  n_ = start_;
}

template <typename Num>
Range<Num>::operator bool() const {
  return (step_ > 0) ? n_ <= stop_ : n_ >= stop_;
}

template <typename Num>
Num const &Range<Num>::operator*() const {
  return n_;
}

template <typename Num>
Num const *Range<Num>::operator->() const {
  return &n_;
}

template <typename Num>
Range<Num> &Range<Num>::operator++() {
  n_ += step_;
  return *this;
}

template <typename _Num>
std::ostream &operator<<(std::ostream &out, Range<_Num> &range) {
  bool started = false;
  for (; range; ++range) {
    if (started) out << ", ";
    started |= true;

    out << *range;
  }

  if (started) range.Reset();
  return out;
}

}  // namespace rose
