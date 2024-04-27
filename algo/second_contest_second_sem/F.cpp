#include <iostream>
#include <vector>
#include <queue>

const int kWMAX = 10;
const int kEMAX = 3 * 10e6;

struct Vertex {
  int dist = kWMAX * kEMAX + 1;
  std::vector<std::pair<int, int>> list_;
};

void BFS(std::vector<Vertex>& vertex, int first) {
  vertex[first].dist = 0;
  std::deque<int> deque;
  deque.push_back(first);
  while (!deque.empty()) {
    int v = deque.front();
    deque.pop_front();
    for (auto [u, w] : vertex[v].list_) {
      if (vertex[u].dist > vertex[v].dist + w) {
        vertex[u].dist = vertex[v].dist + w;
        if (w == 0) {
          deque.push_front(u);
        } else {
          deque.push_back(u);
        }
      }
    }
  }
}

void Set(std::vector<Vertex>& vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    vec[i].dist = kWMAX * kEMAX + 1;
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
  std::vector<Vertex> vertex(n + 1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2;
    vertex[v1].list_.emplace_back(v2, 0);
    vertex[v2].list_.emplace_back(v1, 1);
  }
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> first >> second;
    BFS(vertex, first);
    std::cout << (vertex[second].dist == kWMAX * kEMAX + 1 ? -1 : vertex[second].dist) << '\n';
    Set(vertex);
  }
  return 0;
}