#include <iostream>
#include <vector>

struct Vertex {
  int color = 0;
  std::vector<int> list_;
};

bool DFS(std::vector<Vertex>& vec, int v) {
  vec[v].color = 1;
  for (auto u : vec[v].list_) {
    if (vec[u].color == 0) {
      vec[u].color = 1;
      if (DFS(vec, u)) {
        return true;
      }
    }
    if (vec[u].color == 1) {
      return true;
    }
  }
  vec[v].color = 2;
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n = 0;
  std::cin >> n;
  std::vector<Vertex> vertex(n + 1);
  std::string str;
  for (size_t i = 1; i < n; ++i) {
    std::cin >> str;
    for (size_t j = 0; j < str.size(); ++j) {
      if (str[j] == 'R') {
        vertex[i + j + 1].list_.emplace_back(i);
      } else if (str[j] == 'B') {
        vertex[i].list_.emplace_back(i + j + 1);
      }
    }
  }
  for (size_t i = 1; i < n + 1; ++i) {
    if (vertex[i].color == 0) {
      if (DFS(vertex, static_cast<int>(i))) {
        std::cout << "NO" << '\n';
        return 0;
      }
    }
  }
  std::cout << "YES" << '\n';
  return 0;
}
