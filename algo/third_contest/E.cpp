#include <iostream>

int Min(int a, int b, int c) {
  return (a <= b ? (c <= a ? c : a) : (b <= c ? b : c));
}

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n + 1]{};
  array[1] = 0;
  if (n > 1) {
    array[2] = 1;
  }
  if (n > 2) {
    array[3] = 1;
  }
  for (int i = 4; i < n + 1; ++i) {
    array[i] = 1 + Min((i % 2 == 0 ? array[i / 2] : 1000001), (i % 3 == 0 ? array[i / 3] : 1000001), array[i - 1]);
  }
  std::cout << array[n] << '\n';
  delete[] array;
  return 0;
}