#include "point.h"

#include <math.h>

namespace rose {

template <typename N>
Point<N>::Point() {
  x_ = 0;
  y_ = 0;
}

template <typename N>
Point<N>::Point(N x, N y) {
  x_ = x;
  y_ = y;
}

template <typename N>
Point<N>::Point(const Point &other) {
  x_ = other.x_;
  y_ = other.y_;
}

template <typename N>
Point<N> Point<N>::operator+(const Point &other) {
  return {x_ + other.x_, y_ + other.y_};
}

template <typename N>
void Point<N>::operator+=(const Point &other) {
  x_ += other.x_;
  y_ += other.y_;
}

template <typename N>
Point<N> Point<N>::operator-(const Point &other) {
  return {x_ - other.x_, y_ - other.y_};
}

template <typename N>
void Point<N>::operator-=(const Point &other) {
  x_ -= other.x_;
  y_ -= other.y_;
}

template <typename N>
bool Point<N>::operator==(const Point &other) {
  if (std::is_integral_v<N>) return (x_ == other.x_) && (y_ == other.y_);
  return _ApproxEqual(x_, other.x_) && _ApproxEqual(y_, other.y_);
}

template <typename N>
bool Point<N>::operator!=(const Point &other) {
  if (std::is_integral_v<N>) return (x_ != other.x_) || (y_ != other.y_);
  return !_ApproxEqual(x_, other.x_) || !_ApproxEqual(y_, other.y_);
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

template <typename N>
bool Point<N>::_ApproxEqual(const int n0, const int n1) {
  return n0 == n1;
}

template <typename N>
bool Point<N>::_ApproxEqual(const float f0, const float f1) {
  static const float kBaseEpsilon = 1.0e-5f;
  const float kDistance = fabsf(f0 - f1);
  if (kDistance <= kBaseEpsilon) return true;
  return kDistance <= (kBaseEpsilon * __max(fabsf(f0), fabsf(f1)));
}

template <typename N>
bool Point<N>::_ApproxEqual(const double f0, const double f1) {
  static const double kBaseEpsilon = 1.0e-5;
  const double kDistance = fabs(f0 - f1);
  if (kDistance <= kBaseEpsilon) return true;
  return kDistance <= (kBaseEpsilon * __max(fabs(f0), fabs(f1)));
}

}  // namespace rose
