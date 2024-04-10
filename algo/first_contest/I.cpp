#include <iostream>

void Hanoy(int n, int from, int sred, int to) {
  if (n == 1) {
    std::cout << 1 << ' ' << from << ' ' << to << '\n';
  } else {
    Hanoy(n - 1, from, sred, to);
    std::cout << n << ' ' << from << ' ' << sred << '\n';
    Hanoy(n - 1, to, sred, from);
    std::cout << n << ' ' << sred << ' ' << to << '\n';
    Hanoy(n - 1, from, sred, to);
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  Hanoy(n, 1, 2, 3);
  return 0;
}