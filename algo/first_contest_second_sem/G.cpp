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
  Vector(const Point& first, const Point& second) : x(second.x - first.x), y(second.y - first.y){};
  int64_t NonScalar(const Vector& other) const {
    return other.y * x - y * other.x;
  }
};

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x;
  in >> p.y;
  return in;
}

bool IsVip(std::vector<Point>& point) {
  Vector first(point[point.size() - 1], point[0]);
  int64_t sign = 0;
  for (size_t i = 0; i < point.size(); ++i) {
    if (first.NonScalar(Vector(point[i], point[(i + 1) % point.size()])) != 0) {
      sign = (first.NonScalar(Vector(point[i], point[i + 1])) > 0 ? 1 : -1);
      break;
    }
    first = Vector(point[i], point[(i + 1) % point.size()]);
  }
  first = Vector(point[point.size() - 1], point[0]);
  for (size_t i = 0; i < point.size(); ++i) {
    if (first.NonScalar(Vector(point[i], point[(i + 1) % point.size()])) * sign < 0) {
      return false;
    }
    first = Vector(point[i], point[(i + 1) % point.size()]);
  }
  return true;
}

int main() {
  int size = 0;
  std::cin >> size;
  std::istream_iterator<Point> it(std::cin);
  std::vector<Point> points(it, std::istream_iterator<Point>());
  std::cout << (IsVip(points) ? "YES" : "NO") << '\n';
  return 0;
}