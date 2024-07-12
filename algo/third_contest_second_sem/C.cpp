#include <iostream>
#include <set>
#include <vector>

const int kMAX = 1'000'000;
using Graph = std::vector<std::vector<std::pair<size_t, size_t>>>;

size_t Prim(Graph& adj_list, size_t first) {
  std::set<std::pair<size_t, size_t>> queue;
  std::vector<size_t> d(adj_list.size(), kMAX);
  std::vector<bool> in_ostov(adj_list.size(), false);
  in_ostov[first] = true;
  d[first] = 0;
  for (auto&& [u, w] : adj_list[first]) {
    if (w < d[u]) {
      queue.erase({d[u], u});
      d[u] = w;
      queue.emplace(d[u], u);
    }
  }
  while (!queue.empty()) {
    auto v = queue.begin()->second;
    in_ostov[v] = true;
    queue.erase(queue.begin());
    for (auto&& [u, w] : adj_list[v]) {
      if (w < d[u] && !in_ostov[u]) {
        queue.erase({d[u], u});
        d[u] = w;
        queue.emplace(d[u], u);
      }
    }
  }
  size_t weight = 0;
  for (size_t i = 1; i < d.size(); ++i) {
    weight += d[i];
  }
  std::cout << '\n';
  return weight;
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  Graph adj_list(n + 1);
  size_t v1 = 0;
  size_t v2 = 0;
  size_t w = 0;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    adj_list[v1].emplace_back(v2, w);
    adj_list[v2].emplace_back(v1, w);
  }
  std::cout << Prim(adj_list, 1) << '\n';
  return 0;
}