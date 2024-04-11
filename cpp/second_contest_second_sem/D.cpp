#include <vector>
#include <iostream>

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> vertex(n + 1);
  int operation = 0;
  int v1 = 0;
  int v2 = 0;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> operation;
    if (operation == 1) {
      std::cin >> v1 >> v2;
      vertex[v1].push_back(v2);
      vertex[v2].push_back(v1);
    }
    if (operation == 2) {
      std::cin >> v1;
      for (const auto& v : vertex[v1]) {
        std::cout << v << ' ';
      }
      std::cout << '\n';
    }
  }
  return 0;
}