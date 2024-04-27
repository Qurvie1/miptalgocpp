#include <iostream>
#include <vector>
#include <algorithm>

struct Vertex {
  int color = 0;
  std::vector<int> list_;
};

bool DFS(std::vector<Vertex>& vec, std::vector<int>& stack, int v, int& start, int& end) {
  vec[v].color = 1;
  for (auto u : vec[v].list_) {
    if (vec[u].color == 0) {
      vec[u].color = 1;
      stack[u] = v;
      if (DFS(vec, stack, u, start, end)) {
        return true;
      }
    }
    if (vec[u].color == 1) {
      start = u;
      end = v;
      return true;
    }
  }
  vec[v].color = 2;
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int start = -1;
  int end = -1;
  std::cin >> n >> m;
  std::vector<Vertex> vertex(n + 1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    vertex[v1].list_.push_back(v2);
  }
  std::vector<int> stack(n + 1);
  for (int i = 1; i < n + 1; ++i) {
    if (vertex[i].color == 0) {
      if (DFS(vertex, stack, i, start, end)) {
        break;
      }
    }
  }
  if (start == -1) {
    std::cout << "NO" << '\n';
  } else {
    std::cout << "YES\n";
    std::vector<int> cycle;
    for (int i = end; i != start; i = stack[i]) {
      cycle.push_back(i);
    }
    cycle.push_back(start);
    while (!cycle.empty()) {
      std::cout << cycle.back() << ' ';
      cycle.pop_back();
    }
  }
  return 0;
}