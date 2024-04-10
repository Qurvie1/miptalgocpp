#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

struct Point {
  int64_t x;
  int64_t y;
};

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x >> p.y;
  return in;
}

struct Vector {
  int64_t x;
  int64_t y;
  Vector(const Point& first, const Point& second) : x(second.x - first.x), y(second.y - first.y){};

  int64_t NonScalar(const Vector& a) const {
    return (a.y * x - a.x * y);
  }

  int64_t Norm() const {
    return x * x + y * y;
  }
};

int64_t OuterProduct(const Vector& first, const Vector& other) {
  return first.x * other.y - first.y * other.x;
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

  std::vector<Point> Graham() {
    auto stack = new Point[points.size()];
    stack[0] = points[0];
    for (size_t i = 1; i < points.size(); ++i) {
      if (stack[0].x > points[i].x || (stack[0].x == points[i].x && stack[0].y > points[i].y)) {
        stack[0] = points[i];
      }
    }
    std::sort(points.begin(), points.end(), [&stack](const Point& pa, const Point& pb) {
      Vector a(stack[0], pa);
      Vector b(stack[0], pb);
      int64_t angle = OuterProduct(a, b);
      if (angle != 0) {
        return angle > 0;
      }
      return a.Norm() < b.Norm();
    });

    size_t stack_size = 1;
    for (size_t i = 0; i < points.size(); ++i) {
      while (stack_size >= 2) {
        Vector vec1(stack[stack_size - 2], stack[stack_size - 1]);
        Vector vec2(stack[stack_size - 1], points[i]);
        if (OuterProduct(vec1, vec2) > 0) {
          break;
        }
        --stack_size;
      }
      stack[stack_size++] = points[i];
    }
    std::vector<Point> convex_hull;
    for (size_t i = 0; i < stack_size; ++i) {
      convex_hull.push_back(stack[i]);
    }
    delete[] stack;
    return convex_hull;
  }
};

void Printing(std::vector<Point> points) {
  std::cout << points.size() << '\n';
  for (size_t i = points.size(); i > 0; --i) {
    std::cout << points[i % points.size()].x << ' ' << points[i % points.size()].y << '\n';
  }
  std::cout.precision(1);
  std::cout << std::fixed << Polygon(std::move(points)).Area() << '\n';
}

int main() {
  int size = 0;
  std::cin >> size;
  std::istream_iterator<Point> it(std::cin);
  std::vector<Point> points(it, std::istream_iterator<Point>());
  Printing(Polygon(std::move(points)).Graham());
  return 0;
}