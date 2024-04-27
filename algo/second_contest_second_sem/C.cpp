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
  int first = 0;
  int second = 0;
  std::cin >> first >> second;
  std::vector<Vertex> list(11001);
  for (int i = 1000; i < 10000; ++i) {
    if (i / 1000 != 9) {
      list[i].list_.push_back(((i / 1000) + 1) * 1000 + i % 1000);
    }
    if (i % 10 != 1) {
      list[i].list_.push_back(i - 1);
    }
    list[i].list_.push_back((i % 10) * 1000 + i / 10);
    list[i].list_.push_back((i % 1000) * 10 + i / 1000);
    list[i].number = i;
  }
  BFS(list, first);
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
  std::cout << list[second].shortest_path + 1 << '\n';
  while (!buffer.empty()) {
    std::cout << buffer.back() << '\n';
    buffer.pop_back();
  }
  return 0;
}