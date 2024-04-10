#include <iostream>
#include <cmath>

struct Vector {
  int x;
  int y;
  double Module() {
    return sqrt(x * x + y * y);
  }
  int Scalar(const Vector& a) {
    return (x * a.x + y * a.y);
  }
  double NonScalar(const Vector& a) {
    return (a.y * x - a.x * y);
  }
  double Square(const Vector& a) {
    return (NonScalar(a) >= 0 ? NonScalar(a) / 2 : -NonScalar(a) / 2);
  }
};

int main() {
  int vectors[8]{};
  for (int i = 0; i < 8; ++i) {
    std::cin >> vectors[i];
  }
  Vector a{vectors[2] - vectors[0], vectors[3] - vectors[1]};
  Vector b{vectors[6] - vectors[4], vectors[7] - vectors[5]};
  std::cout.precision(7);
  std::cout << a.Module() << ' ' << b.Module() << '\n';
  std::cout << a.x + b.x << ' ' << a.y + b.y << '\n';
  std::cout << a.Scalar(b) << ' ' << a.NonScalar(b) << '\n';
  std::cout << a.Square(b);
  return 0;
}