#include "no_brainers/02_point_revisited/point.h"

#include <math.h>

#include "custom_libraries/number_utils.h"

namespace rose {

template <typename N>
Point<N>::Point() : x_(0), y_(0) {}

template <typename N>
Point<N>::Point(N x, N y) : x_(x), y_(y) {}

template <typename N>
Point<N>::Point(const Point &other) : x_(other.x_), y_(other.y_) {}

template <typename N>
N Point<N>::x() const {
  return x_;
}

template <typename N>
N Point<N>::y() const {
  return y_;
}

template <typename N>
Point<N> Point<N>::operator+(const Point &other) const {
  return {x_ + other.x_, y_ + other.y_};
}

template <typename N>
Point<N> &Point<N>::operator+=(const Point &other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

template <typename N>
Point<N> Point<N>::operator-(const Point &other) const {
  return {x_ - other.x_, y_ - other.y_};
}

template <typename N>
Point<N> &Point<N>::operator-=(const Point &other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

template <typename N>
bool Point<N>::operator==(const Point &other) const {
  return ApproxEqual(x_, other.x_) && ApproxEqual(y_, other.y_);
}

template <typename N>
bool Point<N>::operator!=(const Point &other) const {
  return !ApproxEqual(x_, other.x_) || !ApproxEqual(y_, other.y_);
}

template <typename _N>
std::istream &operator>>(std::istream &in, Point<_N> &point) {
  in >> point.x_ >> point.y_;
  return in;
}

template <typename _N>
std::ostream &operator<<(std::ostream &out, const Point<_N> &point) {
  out << '(' << point.x_ << ", " << point.y_ << ')';
  return out;
}

}  // namespace rose
