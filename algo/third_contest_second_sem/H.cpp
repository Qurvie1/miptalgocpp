#include <iostream>
#include <vector>
#include <tuple>

const int kWMAX = 10;
const int kEMAX = 3 * 10e6;

void Ford(std::vector<std::tuple<int, int, int>>& vec, std::vector<std::vector<int>>& d, int s, int k) {
  d[0][s] = 0;
  for (int p = 0; p <= k; ++p) {
    for (auto&& [u, v, w] : vec) {
      d[p + 1][v] = std::min(d[p + 1][v], d[p][u] + w);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;
  int first = 0;
  int second = 0;
  std::cin >> first >> second;
  std::vector<std::vector<int>> dist(1000, std::vector(1000, kWMAX * kEMAX + 1));
  std::vector<std::tuple<int, int, int>> edges;
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2 >> w;
    edges.emplace_back(v1, v2, w);
  }
  Ford(edges, dist, first, k);
  int minrun = kWMAX * kEMAX + 1;
  for (int i = 0; i <= k; ++i) {
    if (minrun > dist[i][second]) {
      minrun = dist[i][second];
    }
  }
  std::cout << (minrun == kWMAX * kEMAX + 1 ? -1 : minrun) << '\n';
  return 0;
}