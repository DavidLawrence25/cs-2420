#include <iostream>

#ifndef CS2420_NOBRAINERS_01OVERLOADEDOPERATORS_POINT_H_
#define CS2420_NOBRAINERS_01OVERLOADEDOPERATORS_POINT_H_

namespace rose {

// Represents a lattice point in a 2D Cartesian coordinate system.
class Point {
 public:
  Point();
  Point(int x, int y);
  Point(const Point &other);

  int x() const;
  int y() const;

  Point operator+(const Point &other) const;
  Point &operator+=(const Point &other);
  Point operator-(const Point &other) const;
  Point &operator-=(const Point &other);
  bool operator==(const Point &other) const;
  bool operator!=(const Point &other) const;
  friend std::istream &operator>>(std::istream &in, Point &point);
  friend std::ostream &operator<<(std::ostream &out, const Point &point);

 private:
  int x_, y_;
};

}  // namespace rose

#endif  // CS2420_NOBRAINERS_01OVERLOADEDOPERATORS_POINT_H_
