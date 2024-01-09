#include <iostream>

#include "point.h"

using std::cout, std::cin;

int main() {
  rose::Point p1;
  cout << "Point 1\n";
  cin >> p1;
  rose::Point p2;
  cout << "Point 2\n";
  cin >> p2;

  rose::Point p3 = p1 + p2;
  cout << p1 << " + " << p2 << " = " << p3 << '\n';

  rose::Point p4 = p1 - p2;
  cout << p1 << " - " << p2 << " = " << p4 << '\n';

  p1 += p2;
  cout << "Increment p1 by p2 to get " << p1 << '\n';

  p1 -= p2;
  cout << "Decrement p1 by p2 to get " << p1 << '\n';

  return 0;
}
