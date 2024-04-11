#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<size_t> animals(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> animals[i];
  }
  size_t m = 0;
  std::cin >> m;
  for (size_t i = 0; i < m; ++i) {
    size_t color = 0;
    std::cin >> color;
    std::cout << (std::distance(std::lower_bound(animals.begin(), animals.end(), color),
                                std::upper_bound(animals.begin(), animals.end(), color)))
              << '\n';
  }
  return 0;
}