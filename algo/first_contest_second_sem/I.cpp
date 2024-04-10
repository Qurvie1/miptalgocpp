#include <vector>
#include <iostream>
#include <iterator>

struct Point {
  int64_t x;
  int64_t y;
};

struct Vector {
  int64_t x;
  int64_t y;

  Vector(const Point& p1, const Point& p2) : x(p2.x - p1.x), y(p2.y - p1.y){};

  int64_t NonScalar(const Vector& a) const {
    return (a.y * x - a.x * y);
  }
};

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x;
  in >> p.y;
  return in;
}

struct Polygon {
  std::vector<Point> points;
  Polygon(std::vector<Point>&& p) : points(std::move(p)){};  // NOLINT

  int64_t OrientedArea() const {
    Point a = points[0];
    int64_t area = 0;
    for (size_t i = 1; i < points.size(); ++i) {
      area += Vector(a, points[i - 1]).NonScalar(Vector(a, points[i]));
    }
    area -= Vector(a, points[points.size() - 1]).NonScalar(Vector(a, points[0]));
    return area;
  }

  long double Area() const {
    int64_t area = OrientedArea();
    return (static_cast<long double>((area > 0 ? area : -area))) / 2;
  }
};

int main() {
  int size = 0;
  std::cin >> size;
  std::istream_iterator<Point> it(std::cin);
  std::vector<Point> points(it, std::istream_iterator<Point>());
  Polygon poly(std::move(points));
  std::cout.precision(1);
  std::cout << std::fixed << poly.Area() << '\n';
  return 0;
}