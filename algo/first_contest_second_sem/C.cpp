#include <iostream>
#include <cmath>

const double kEPS = 1e-9;

struct Point {
  int x;
  int y;
  double Distance(const Point& b) const {
    return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
  }
  bool OnSegment(const Point& other, const Point& check) const {
    double inf = check.Distance(other) + check.Distance({x, y}) - other.Distance({x, y});
    return (inf > 0.0 ? inf : -inf) < kEPS;
  }
  bool OnLine(const Point& other, const Point& check) const {
    return (other.y - y) * (check.x - x) == (check.y - y) * (other.x - x);
  }
  bool OnRay(const Point& other, const Point& check) const {
    bool fl1 = (other.x - x > 0 ? (check.x - x) >= 0 : (x - check.x) >= 0) && (other.x - x != 0);
    bool fl2 = (other.y - y > 0 ? (check.y - y) >= 0 : (y - check.y) >= 0) && (other.y - y != 0);
    return OnLine(other, check) && (fl1 || fl2);
  }
};

std::istream& operator>>(std::istream& in, Point& a) {
  in >> a.x;
  in >> a.y;
  return in;
}

int main() {
  Point x1;
  Point x2;
  Point x3;
  std::cin >> x1;
  std::cin >> x2;
  std::cin >> x3;
  std::cout << (x2.OnLine(x3, x1) ? "YES" : "NO") << '\n';
  std::cout << (x2.OnRay(x3, x1) ? "YES" : "NO") << '\n';
  std::cout << (x2.OnSegment(x3, x1) ? "YES" : "NO") << '\n';
  return 0;
}