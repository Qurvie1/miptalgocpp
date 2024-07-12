#include <iostream>
#include <vector>
#include <tuple>

class DSU {
 public:
  explicit DSU(int vertex) : parent_(std::vector<int>(vertex + 1)), rank_(std::vector<int>(vertex + 1, 1)) {
    for (int i = 1; i < vertex; ++i) {
      parent_[i] = i;
    }
  }

  int Leader(int v) {
    return (parent_[v] == v) ? v : parent_[v] = Leader(parent_[v]);
  }

  void Unite(int a, int b) {
    int l1 = Leader(a);
    int l2 = Leader(b);
    if (rank_[l1] > rank_[l2]) {
      std::swap(l1, l2);
    }
    rank_[l2] = std::max(rank_[l2], rank_[l1] + 1);
    parent_[l1] = l2;
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU dsu(n);
  std::vector<std::tuple<int, int, int>> edges;
  edges.reserve(m);
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  int answer = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    edges.emplace_back(v1, v2, w);
  }
  for (auto&& [u, v, w] : edges) {
    if (dsu.Leader(u) != dsu.Leader(v)) {
      dsu.Unite(u, v);
      answer += w;
    }
  }
  std::cout << answer << '\n';
  return 0;
}