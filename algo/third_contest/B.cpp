#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int a = 3;
  int b = 8;
  for (int i = 2; i < n; ++i) {
    int temp = b;
    b = 2 * a + 2 * b;
    a = temp;
  }
  std::cout << (n == 1 ? 3 : (n == 2 ? 8 : b)) << '\n';
  return 0;
}