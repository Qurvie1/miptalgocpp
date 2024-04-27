#include <iostream>
#include <vector>
#include <queue>

struct Vertex {
  int number = 0;
  int shortest_path = -1;
  int color = 0;
  int pred = 0;
  std::vector<int> list_;
};

void BFS(std::vector<Vertex>& vertex, int first) {
  vertex[first].color = 1;
  vertex[first].shortest_path = 0;
  std::queue<int> queue;
  queue.push(first);
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto v : vertex[u].list_) {
      if (vertex[v].color == 0) {
        vertex[v].color = 1;
        vertex[v].shortest_path = vertex[u].shortest_path + 1;
        vertex[v].pred = vertex[u].number;
        queue.push(v);
      }
    }
    vertex[u].color = 2;
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  int first = 0;
  int second = 0;
  std::cin >> first >> second;
  std::vector<Vertex> list(n + 1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    list[v1].number = v1;
    list[v2].number = v2;
    list[v1].list_.push_back(v2);
    list[v2].list_.push_back(v1);
  }
  BFS(list, first);
  if (list[second].shortest_path == -1) {
    std::cout << -1;
    return 0;
  }
  if (second == first) {
    std::cout << 0 << '\n';
    std::cout << second << '\n';
    return 0;
  }
  std::vector<int> buffer;
  int start = second;
  buffer.push_back(start);
  while (true) {
    buffer.push_back(list[start].pred);
    start = list[start].pred;
    if (start == first || start == 0) {
      break;
    }
  }
  std::cout << list[second].shortest_path << '\n';
  while (!buffer.empty()) {
    std::cout << buffer.back() << ' ';
    buffer.pop_back();
  }
  return 0;
}