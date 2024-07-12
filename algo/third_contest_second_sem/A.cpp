#include <iostream>
#include <set>
#include <vector>
#include <tuple>
#include <algorithm>

const int kMAX = 1'000'000;
using Graph = std::vector<std::vector<std::tuple<int, int, int>>>;

int Prim(Graph& adj_list, int first) {
  std::set<std::pair<int, int>> queue;
  std::vector<int> d(adj_list.size(), kMAX);
  std::vector<int> edges(adj_list.size());
  std::vector<bool> in_ostov(adj_list.size(), false);
  in_ostov[first] = true;
  d[first] = 0;
  for (auto&& [u, w, count] : adj_list[first]) {
    if (w < d[u] || (w == d[u] && count < edges[u])) {
      queue.erase({d[u], u});
      edges[u] = count;
      d[u] = w;
      queue.emplace(d[u], u);
    }
  }
  while (!queue.empty()) {
    auto v = queue.begin()->second;
    in_ostov[v] = true;
    queue.erase(queue.begin());
    for (auto&& [u, w, count] : adj_list[v]) {
      if ((w < d[u] || (w == d[u] && count < edges[u])) && !in_ostov[u]) {
        queue.erase({d[u], u});
        edges[u] = count;
        d[u] = w;
        queue.emplace(d[u], u);
      }
      if ((w < d[u] || (w == d[u] && count < edges[u])) && v != u) {
        edges[u] = count;
      }
    }
  }
  return *std::max_element(edges.begin(), edges.end());
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph adj_list(n);
  int v1 = 0;
  int v2 = 0;
  int counter = 1;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    adj_list[v1].emplace_back(v2, 1, counter);
    adj_list[v2].emplace_back(v1, 1, counter);
    ++counter;
  }
  std::cout << Prim(adj_list, 0) << '\n';
  return 0;
}