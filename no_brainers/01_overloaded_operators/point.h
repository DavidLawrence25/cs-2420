#include <iostream>

#ifndef CS2420_NOBRAINERS_01OVERLOADEDOPERATORS_POINT_H_
#define CS2420_NOBRAINERS_01OVERLOADEDOPERATORS_POINT_H_

namespace rose {

class Point {
 public:
  Point();
  Point(int x, int y);
  Point(const Point &other);

  Point operator+(const Point &other);
  void operator+=(const Point &other);
  Point operator-(const Point &other);
  void operator-=(const Point &other);
  friend std::istream &operator>>(std::istream &in, Point &point);
  friend std::ostream &operator<<(std::ostream &out, const Point &point);

 private:
  int x_, y_;
};

}  // namespace rose

#endif  // CS2420_NOBRAINERS_01OVERLOADEDOPERATORS_POINT_H_
