#include <vector>
#include <iostream>
#include <iterator>

struct Point {
  int x;
  int y;
  int NonSclalar(const Point& second, const Point& third) const {
    return (second.x - x) * (third.y - y) - (second.y - y) * (third.x - x);
  }
};

struct Vector {
  int x;
  int y;

  Vector(const Point& p1, const Point& p2) : x(p2.x - p1.x), y(p2.y - p1.y){};

  int NonScalar(const Vector& a) const {
    return (a.y * x - a.x * y);
  }
};

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x;
  in >> p.y;
  return in;
}

bool OnSegment(const Point& p1, const Point& p2, const Point& p3) {
  return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x)) &&
         (std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
}

bool SegmentIntersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
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

bool IsInside(const std::vector<Point>& polygon, const Point& point) {
  int min_x = 0;
  for (const Point& p : polygon) {
    if (p.x < min_x) {
      min_x = p.x;
    }
  }
  min_x -= 10;
  Point other{min_x, point.y + 1};
  Point first = polygon[0];
  Point second = polygon[1];
  int intersections = 0;
  for (size_t i = 1; i < polygon.size() + 1; ++i) {
    if (OnSegment(first, second, point) && (point.NonSclalar(first, second) == 0)) {
      return true;
    }
    intersections += SegmentIntersect(point, other, first, second);
    first = second;
    second = polygon[(i + 1) % polygon.size()];
  }
  return intersections % 2;
}

int main() {
  Point p;
  int size = 0;
  std::cin >> size >> p;
  std::istream_iterator<Point> it(std::cin);
  std::vector<Point> polygon(it, std::istream_iterator<Point>());
  std::cout << (IsInside(polygon, p) ? "YES" : "NO") << '\n';
  return 0;
}