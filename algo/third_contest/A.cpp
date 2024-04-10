#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  auto dynamic = new int64_t[n]{};
  dynamic[0] = 2;
  dynamic[1] = 3;
  for (int i = 2; i < n; ++i) {
    dynamic[i] = dynamic[i - 1] + dynamic[i - 2];
  }
  std::cout << dynamic[n - 1] << '\n';
  delete[] dynamic;
  return 0;
}