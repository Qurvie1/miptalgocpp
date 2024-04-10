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

double DistanceRay(const Vector& first, const Vector& second, const Vector& third) {
  return (first.Scalar(second) >= 0 ? DistanceLine(first, second)
                                    : std::min(DistancePoint(first), DistancePoint(third)));
};

int main() {
  Point<int> x1;
  Point<int> x2;
  Point<int> x3;
  std::cin >> x1 >> x2 >> x3;
  Vector v1(x2, x1);
  Vector v2(x3, x1);
  Vector v3(x2, x3);
  std::cout.precision(6);
  std::cout << std::fixed << DistanceLine(v1, v3) << '\n';
  std::cout << std::fixed << DistanceRay(v1, v3, v2) << '\n';
  std::cout << std::fixed << DistanceSegment(v1, v3, v2) << '\n';
  return 0;
}