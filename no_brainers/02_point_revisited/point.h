#include <iostream>

#ifndef CS2420_NOBRAINERS_02POINTREVISITED_POINT_H_
#define CS2420_NOBRAINERS_02POINTREVISITED_POINT_H_

namespace rose {

// Represents a point in a 2D Cartesian coordinate system.
template <typename N>
class Point {
 public:
  // Constructs a point at the origin (0, 0).
  Point();
  // Constructs a point at (x, y).
  Point(N x, N y);
  // Constructs a point identical to `other`.
  Point(const Point &other);

  Point operator+(const Point &other);
  void operator+=(const Point &other);
  Point operator-(const Point &other);
  void operator-=(const Point &other);
  bool operator==(const Point &other);
  bool operator!=(const Point &other);

  template <typename _N>
  friend std::istream &operator>>(std::istream &in, Point<_N> &point);
  template <typename _N>
  friend std::ostream &operator<<(std::ostream &out, const Point<_N> &point);

 private:
  N x_, y_;

  // Returns true if `n0 == n1`. Don't use.
  static bool _ApproxEqual(const int n0, const int n1);
  // Returns true if `f0` and `f1` are close enough to the same value.
  static bool _ApproxEqual(const float f0, const float f1);
  // Returns true if `f0` and `f1` are close enough to the same value.
  static bool _ApproxEqual(const double f0, const double f1);
};

}  // namespace rose

#include "point.cc"

#endif  // CS2420_NOBRAINERS_02POINTREVISITED_POINT_H_
