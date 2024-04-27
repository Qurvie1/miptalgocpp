#include <iostream>
#include <vector>
#include <algorithm>

struct Vertex {
  int color = 0;
  std::vector<int> list_;
};

bool DFS(std::vector<Vertex>& vec, std::vector<int>& ans, int v) {
  vec[v].color = 1;
  for (auto u : vec[v].list_) {
    if (vec[u].color == 0) {
      vec[u].color = 1;
      if (DFS(vec, ans, u)) {
        return true;
      }
    } else if (vec[u].color == 1) {
      return true;
    }
  }
  ans.push_back(v);
  vec[v].color = 2;
  return false;
}

void TopologicalSort(std::vector<Vertex>& vec, std::vector<int>& ans) {
  for (size_t i = 0; i < vec.size(); ++i) {
    vec[i].color = 0;
  }
  ans.clear();
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i].color == 0) {
      if (DFS(vec, ans, static_cast<int>(i))) {
        std::cout << -1 << '\n';
        ans.clear();
        return;
      }
    }
  }
  std::reverse(ans.begin(), ans.end());
  ans.pop_back();
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> vertex(n + 1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2;
    vertex[v1].list_.push_back(v2);
  }
  std::vector<int> ans;
  TopologicalSort(vertex, ans);
  for (const auto& v : ans) {
    std::cout << v << ' ';
  }
}