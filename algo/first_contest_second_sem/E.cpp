#include <iostream>
#include <cmath>

template <class T>
struct Point {
  T x;
  T y;
};

template <class T>
std::istream& operator>>(std::istream& in, Point<T>& p) {
  in >> p.x;
  in >> p.y;
  return in;
}

struct Vector {
  int x;
  int y;

  Vector(const Point<int>& p1, const Point<int>& p2) : x(p2.x - p1.x), y(p2.y - p1.y){};

  int NonScalar(const Vector& a) const {
    return (a.y * x - a.x * y);
  }
};

bool OnSegment(const Point<int>& p1, const Point<int>& p2, const Point<int>& p3) {
  return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x)) &&
         (std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
}

bool SegmentIntersect(const Point<int>& p1, const Point<int>& p2, const Point<int>& p3, const Point<int>& p4) {
  Vector v1(p3, p1);
  Vector v2(p3, p4);
  Vector v3(p1, p2);
  Vector v4(p1, p3);
  Vector v5(p3, p2);
  Vector v6(p1, p4);
  int d1 = v1.NonScalar(v2);
  int d2 = v5.NonScalar(v2);
  int d3 = v4.NonScalar(v3);
  int d4 = v6.NonScalar(v3);
  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return true;
  }
  return ((d1 == 0 && OnSegment(p3, p4, p1)) || (d2 == 0 && OnSegment(p3, p4, p2)) ||
          (d3 == 0 && OnSegment(p1, p2, p3)) || (d4 == 0 && OnSegment(p1, p2, p4)));
}

int main() {
  Point<int> p1;
  Point<int> p2;
  Point<int> p3;
  Point<int> p4;
  std::cin >> p1 >> p2 >> p3 >> p4;
  std::cout << (SegmentIntersect(p1, p2, p3, p4) ? "YES" : "NO");
  return 0;
}