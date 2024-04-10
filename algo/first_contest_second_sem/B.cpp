#include <iostream>
#include <cmath>

struct Line {
  int a;
  int b;
  int c;
};

std::istream& operator>>(std::istream& in, Line& line) {
  in >> line.a;
  in >> line.b;
  in >> line.c;
  return in;
}

int main() {
  Line first;
  Line second;
  std::cin >> first;
  std::cin >> second;
  std::cout.precision(7);
  std::cout << first.b << ' ' << -first.a << '\n';
  std::cout << second.b << ' ' << -second.a << '\n';
  int det = second.b * first.a - first.b * second.a;
  if (det) {
    double det1 = -first.c * second.b + second.c * first.b;
    double det2 = -second.c * first.a + second.a * first.c;
    std::cout << det1 / det << ' ' << det2 / det << '\n';
  } else {
    double x = 0;
    double y = 0;
    x = (first.b == 0 ? -first.c : 0);
    y = (first.b == 0 ? 0.0 : static_cast<double>(-first.c) / first.b);
    double mean = second.a * x + second.b * y + second.c;
    std::cout << (mean > 0 ? mean : -mean) / sqrt(second.a * second.a + second.b * second.b);
  }
  return 0;
}