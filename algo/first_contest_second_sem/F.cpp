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
  Vector(int x, int y) : x(x), y(y){};
  Vector(const Point<int>& p1, const Point<int>& p2) : x(p2.x - p1.x), y(p2.y - p1.y){};
  int Scalar(const Vector& a) const {
    return (x * a.x + y * a.y);
  }

  int NonScalar(const Vector& a) const {
    return (a.y * x - a.x * y);
  }

  double Module() const {
    return sqrt(x * x + y * y);
  }

  Vector operator-() {
    return {-x, -y};
  }
};

double DistanceLine(const Vector& first, const Vector& second) {
  return abs(first.NonScalar(second)) / second.Module();
}

double DistancePoint(const Vector& v) {
  return v.Module();
}

double DistanceSegment(const Vector& first, Vector& second, const Vector& third) {
  return (first.Scalar(second) >= 0 && third.Scalar(-second) >= 0
              ? DistanceLine(first, second)
              : std::min(DistancePoint(first), DistancePoint(third)));
}

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
  Vector v1(p1, p2);
  Vector v2(p1, p3);
  Vector v3(p2, p3);
  Vector v4(p1, p4);
  Vector v5(p2, p4);
  Vector v6(p3, p4);
  std::cout.precision(6);
  if (SegmentIntersect(p1, p2, p3, p4)) {
    std::cout << std::fixed << 0 << '\n';
  } else {
    std::cout << std::fixed
              << std::min(std::min(DistanceSegment(v2, v1, v3), DistanceSegment(v4, v1, v5)),
                          std::min(DistanceSegment(-v2, v6, -v4), DistanceSegment(-v3, v6, -v5)));
  }
}