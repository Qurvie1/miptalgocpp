#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>

struct Vertex {
  int dist = std::numeric_limits<int>::max();
  std::vector<std::pair<int, int>> list_;
};

void Dijkstra(std::vector<Vertex>& vec, int s) {
  vec[s].dist = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
  queue.emplace(0, s);
  while (!queue.empty()) {
    auto [cur, v] = queue.top();
    queue.pop();
    if (cur > vec[v].dist) {
      continue;
    }
    for (auto [u, w] : vec[v].list_) {
      if (vec[u].dist > vec[v].dist + w) {
        vec[u].dist = vec[v].dist + w;
        queue.emplace(vec[u].dist, u);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int up = 0;
  int down = 0;
  int in = 0;
  int out = 0;
  int m = 0;
  const int k_max = 1'000'003;
  std::cin >> n >> up >> down >> in >> out >> m;
  std::vector<Vertex> edges(k_max + m);
  int counters = 0;
  edges[1].list_.emplace_back(2, up);
  int max_edges = 0;
  int v = 0;
  for (int i = k_max; i < k_max + m; ++i) {
    std::cin >> counters;
    for (int j = 0; j < counters; ++j) {
      std::cin >> v;
      max_edges = std::max(max_edges, v);
      edges[i].list_.emplace_back(v, out);
      edges[v].list_.emplace_back(i, in);
    }
  }
  for (int i = 2; i < std::max(max_edges, n + 1); ++i) {
    edges[i].list_.emplace_back(i - 1, down);
    edges[i].list_.emplace_back(i + 1, up);
  }
  Dijkstra(edges, 1);
  std::cout << edges[n].dist << '\n';
  return 0;
}