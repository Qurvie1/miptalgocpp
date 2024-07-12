#include <iostream>
#include <vector>
#include <tuple>

const int kWMAX = 10;
const int kEMAX = 3 * 10e6;

void Ford(std::vector<std::tuple<int, int, int>>& edges, std::vector<int>& dists, int s) {
  dists[s] = 0;
  for (size_t i = 0; i < dists.size() - 1; ++i) {
    for (auto&& [v, u, w] : edges) {
      if (dists[u] > dists[v] + w && dists[v] != kWMAX * kEMAX + 1) {
        dists[u] = dists[v] + w;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> dist(n + 1, kWMAX * kEMAX + 1);
  std::vector<std::tuple<int, int, int>> edges;
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    edges.emplace_back(v1, v2, w);
  }
  Ford(edges, dist, 1);
  for (size_t i = 1; i < dist.size(); ++i) {
    std::cout << (dist[i] == kWMAX * kEMAX + 1 ? 30000 : dist[i]) << ' ';
  }
  return 0;
}