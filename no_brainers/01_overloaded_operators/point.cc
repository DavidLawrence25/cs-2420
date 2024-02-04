#include "no_brainers/01_overloaded_operators/point.h"

namespace rose {

Point::Point() : x_(0), y_(0) {}
Point::Point(int x, int y) : x_(x), y_(y) {}
Point::Point(const Point &other) : x_(other.x_), y_(other.y_) {}

int Point::x() const { return x_; }
int Point::y() const { return y_; }

Point Point::operator+(const Point &other) const {
  return {x_ + other.x_, y_ + other.y_};
}

Point &Point::operator+=(const Point &other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Point Point::operator-(const Point &other) const {
  return {x_ - other.x_, y_ - other.y_};
}

Point &Point::operator-=(const Point &other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

bool Point::operator==(const Point &other) const {
  return (x_ == other.x_) && (y_ == other.y_);
}

bool Point::operator!=(const Point &other) const {
  return (x_ != other.x_) || (y_ != other.y_);
}

std::istream &operator>>(std::istream &in, Point &point) {
  in >> point.x_ >> point.y_;
  return in;
}

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << '(' << point.x_ << ", " << point.y_ << ')';
  return out;
}

}  // namespace rose
