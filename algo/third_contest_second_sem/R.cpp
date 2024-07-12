#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>
#include <cstddef>

using Edge = std::tuple<int64_t, int64_t, int64_t, int64_t>;

void Ford(std::vector<Edge>& edges, std::vector<int64_t>& dists, int64_t s) {
  dists[s] = 0;
  std::sort(edges.begin(), edges.end(),
            [](const Edge& first, const Edge& second) { return std::get<2>(first) > std::get<2>(second); });
  for (size_t i = 0; i < dists.size() - 1; ++i) {
    for (auto&& [v, u, in, out] : edges) {
      if ((in >= dists[v]) && dists[v] != std::numeric_limits<int64_t>::max() && (out < dists[u])) {
        dists[u] = out;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n;
  int64_t start = 0;
  int64_t finish = 0;
  std::cin >> start >> finish;
  std::cin >> m;
  std::vector<int64_t> dist(n + 1, std::numeric_limits<int64_t>::max());
  std::vector<Edge> edges;
  int64_t v1 = 0;
  int64_t v2 = 0;
  int64_t in = 0;
  int64_t out = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v1 >> in >> v2 >> out;
    edges.emplace_back(v1, v2, in, out);
  }
  Ford(edges, dist, start);
  std::cout << dist[finish] << '\n';
  return 0;
}