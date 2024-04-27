#include <iostream>
#include <vector>
#include <queue>

const int kWMAX = 10;
const int kEMAX = 3 * 10e6;

struct Vertex {
  int number = 0;
  int dist = kWMAX * kEMAX + 1;
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
  int m = 0;
  std::cin >> n >> m;
  int first = 0;
  int second = 0;
  std::cin >> first >> second;
  std::vector<Vertex> vertex(n + 1);
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2 >> w;
    vertex[v1].list_.emplace_back(v2, w);
  }
  Dijkstra(vertex, first);
  std::cout << (vertex[second].dist == kWMAX * kEMAX + 1 ? -1 : vertex[second].dist) << '\n';
  return 0;
}