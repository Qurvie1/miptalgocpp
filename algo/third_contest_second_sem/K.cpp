#include <iostream>
#include <vector>
#include <tuple>
#include <deque>

const int64_t kWMAX = 10;
const int64_t kEMAX = 3 * 10e6;

bool Ford(std::vector<std::tuple<int64_t, int64_t, int64_t>>& edges, std::vector<int64_t>& dists,
          std::vector<int64_t>& parents, int64_t s) {
  dists[s] = 0;
  int64_t x = -1;
  for (size_t i = 0; i < dists.size(); ++i) {
    x = -1;
    for (auto&& [v, u, w] : edges) {
      if (dists[u] > dists[v] + w && dists[v] != kWMAX * kEMAX + 1) {
        dists[u] = dists[v] + w;
        parents[u] = v;
        x = u;
      }
    }
  }
  if (x == -1) {
    return false;
  }
  if (x != -1) {
    int64_t y = x;
    std::deque<int64_t> path;
    for (size_t i = 0; i < dists.size(); ++i) {
      y = parents[y];
    }
    for (int64_t current = y;; current = parents[current]) {
      path.push_front(current);
      if (current == y && path.size() > 1) {
        break;
      }
    }
    std::cout << "YES\n";
    std::cout << path.size() << '\n';
    for (auto u : path) {
      std::cout << u << ' ';
    }
    std::cout << '\n';
    return true;
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::cin >> n;
  std::vector<int64_t> dist(n + 1, kWMAX * kEMAX + 1);
  std::vector<int64_t> parent(n + 1, -1);
  std::vector<std::tuple<int64_t, int64_t, int64_t>> edges;
  int64_t v = 0;
  for (int64_t i = 1; i < n + 1; ++i) {
    for (int64_t j = 1; j < n + 1; ++j) {
      std::cin >> v;
      if (v == 1'000'00) {
        continue;
      }
      edges.emplace_back(i, j, v);
    }
  }
  for (int i = 1; i < n + 1; ++i) {
    if (Ford(edges, dist, parent, i)) {
      return 0;
    }
    std::fill(dist.begin(), dist.end(), kEMAX * kWMAX + 1);
    std::fill(parent.begin(), parent.end(), -1);
  }
  std::cout << "NO\n";
  return 0;
}