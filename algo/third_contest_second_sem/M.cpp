#include <iostream>
#include <vector>

void FloydWarshall(std::vector<std::vector<int>>& d) {
  for (size_t k = 0; k < d.size(); ++k) {
    for (size_t i = 0; i < d.size(); ++i) {
      for (size_t j = 0; j < d.size(); ++j) {
        if (d[i][j] > d[i][k] + d[k][j]) {
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int>> d(n, std::vector<int>(n));
  int v = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> v;
      d[i][j] = v;
    }
  }
  FloydWarshall(d);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << d[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}