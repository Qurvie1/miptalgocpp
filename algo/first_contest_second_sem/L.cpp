#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>

struct Point {
  int64_t x;
  int64_t y;
  int64_t NonSclalar(const Point& second, const Point& third) const {
    return (second.x - x) * (third.y - y) - (second.y - y) * (third.x - x);
  }
  bool operator!=(const Point& other) const {
    return x != other.x || y != other.y;
  }
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

bool OnSegment(const Point& p1, const Point& p2, const Point& p3) {
  return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x)) &&
         (std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
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

  void CovexHull(std::vector<Point>& convex_hull) const {
    size_t first = 0;
    for (size_t i = 0; i < points.size(); ++i) {
      if ((points[i].x < points[first].x) || ((points[i].x == points[first].x) && (points[i].y < points[first].y))) {
        first = i;
      }
    }
    convex_hull.push_back(points[first]);

    Point base = points[first];
    Point curr = base;
    size_t curr_index = first;
    do {
      Point next = points[(curr_index + 1) % points.size()];
      for (size_t i = 0; i < points.size(); ++i) {
        int64_t sign = curr.NonSclalar(next, points[i]);
        if (sign < 0 || (sign == 0 && OnSegment(curr, points[i], next))) {
          next = points[i];
          curr_index = i;
        }
      }
      curr = next;
      convex_hull.push_back(next);
    } while (curr != base);
    convex_hull.pop_back();
  }

  void Printing() const {
    std::cout << points.size() << '\n';
    for (size_t i = points.size(); i > 0; --i) {
      std::cout << points[i % points.size()].x << ' ' << points[i % points.size()].y << '\n';
    }
    std::cout.precision(1);
    std::cout << std::fixed << Area() << '\n';
  }
};

int main() {
  int size = 0;
  std::cin >> size;
  std::istream_iterator<Point> it(std::cin);
  std::vector<Point> points(it, std::istream_iterator<Point>());
  Polygon poly(std::move(points));
  std::vector<Point> convex_hull;
  poly.CovexHull(convex_hull);
  Polygon(std::move(convex_hull)).Printing();
  return 0;
}