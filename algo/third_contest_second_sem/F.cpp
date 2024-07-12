#include <iostream>
#include <set>
#include <vector>

const int kMAX = 1'000'000;
using Graph = std::vector<std::vector<size_t>>;

size_t Prim(Graph& adj_list, size_t first) {
  std::set<std::pair<size_t, size_t>> queue;
  std::vector<size_t> d(adj_list.size(), kMAX);
  std::vector<bool> in_ostov(adj_list.size(), false);
  in_ostov[first] = true;
  d[first] = 0;
  for (size_t i = 1; i < adj_list.size(); ++i) {
    if (adj_list[first][i] < d[i]) {
      queue.erase({d[i], i});
      d[i] = adj_list[first][i];
      queue.emplace(d[i], i);
    }
  }
  while (!queue.empty()) {
    auto v = queue.begin()->second;
    in_ostov[v] = true;
    queue.erase(queue.begin());
    for (size_t i = 1; i < adj_list.size(); ++i) {
      if (adj_list[v][i] < d[i] && !in_ostov[i] && i != v) {
        queue.erase({d[i], i});
        d[i] = adj_list[v][i];
        queue.emplace(d[i], i);
      }
    }
  }
  size_t weight = 0;
  for (size_t i = 1; i < d.size(); ++i) {
    weight += d[i];
  }
  return weight;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n = 0;
  std::cin >> n;
  Graph adj_list(n + 2, std::vector<size_t>(n + 2, 100));
  size_t v = 0;
  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < n + 1; ++j) {
      std::cin >> v;
      adj_list[i][j] = v;
    }
  }
  for (size_t i = 1; i < n + 1; ++i) {
    std::cin >> v;
    adj_list[n + 1][i] = v;
    adj_list[i][n + 1] = v;
  }
  std::cout << Prim(adj_list, 1) << '\n';
  return 0;
}