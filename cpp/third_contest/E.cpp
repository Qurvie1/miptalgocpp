#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n + 1]{};
  std::istream_iterator<int> it(std::cin);
  std::copy_n(it, n, array);
  int x = 0;
  std::cin >> x;
  std::cout << std::count(array, array + n, x);
  delete[] array;
  return 0;
}