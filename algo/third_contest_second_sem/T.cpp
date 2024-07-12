#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>

struct Vertex {
  int64_t dist = std::numeric_limits<int64_t>::max();
  std::vector<std::pair<int64_t, int64_t>> list_;
};

void Dijkstra(std::vector<Vertex>& vec, int64_t s) {
  vec[s].dist = 0;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
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
  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  std::cin >> n >> m >> k;
  std::vector<int64_t> infections(k + 1);
  for (int64_t i = 1; i < k + 1; ++i) {
    std::cin >> infections[i];
  }
  std::vector<Vertex> graph(n + 1);
  int64_t v1 = 0;
  int64_t v2 = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    graph[v1].list_.emplace_back(v2, w);
    graph[v2].list_.emplace_back(v1, w);
  }
  int64_t start = 0;
  int64_t finish = 0;
  std::cin >> start >> finish;
  Dijkstra(graph, finish);
  for (int64_t i = 1; i < k + 1; ++i) {
    if (graph[infections[i]].dist <= graph[start].dist) {
      std::cout << -1 << '\n';
      return 0;
    }
  }
  std::cout << graph[start].dist << '\n';
  return 0;
}