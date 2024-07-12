#include <iostream>
#include <vector>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

class DSU {
 public:
  explicit DSU(size_t vertex)
      : parent_(std::vector<size_t>(vertex + 1)), rank_(std::vector<size_t>(vertex + 1, 1)), quantity_(vertex) {
    for (size_t i = 1; i < vertex; ++i) {
      parent_[i] = i;
    }
  }

  size_t Leader(size_t v) {
    return (parent_[v] == v) ? v : parent_[v] = Leader(parent_[v]);
  }

  void Unite(size_t a, size_t b) {
    size_t l1 = Leader(a);
    size_t l2 = Leader(b);
    if (rank_[l1] > rank_[l2]) {
      std::swap(l1, l2);
    }
    rank_[l2] = std::max(rank_[l2], rank_[l1] + 1);
    --quantity_;
    parent_[l1] = l2;
  }

  size_t Quantity() const noexcept {
    return quantity_;
  }

 private:
  std::vector<size_t> parent_;
  std::vector<size_t> rank_;
  size_t quantity_;
};

size_t Boruvka(DSU& dsu, std::vector<Edge>& edges) {
  size_t answer = 0;
  size_t n = dsu.Quantity();
  while (dsu.Quantity() > 1) {
    std::vector<Edge> mins(n, {0, 0, std::numeric_limits<int64_t>::max()});
    for (auto& edge : edges) {
      size_t leader1 = dsu.Leader(edge.from);
      size_t leader2 = dsu.Leader(edge.to);
      if (leader1 != leader2) {
        if (edge.weight < mins[leader2].weight) {
          mins[leader2] = edge;
        }
        if (edge.weight < mins[leader1].weight) {
          mins[leader1] = edge;
        }
      }
    }
    for (auto& edge : mins) {
      if (edge.from == 0) {
        continue;
      }
      size_t leader1 = dsu.Leader(edge.from);
      size_t leader2 = dsu.Leader(edge.to);
      if (leader1 != leader2) {
        dsu.Unite(edge.from, edge.to);
        answer += edge.weight;
      }
    }
  }
  return answer;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  DSU dsu(n);
  std::vector<Edge> edges;
  edges.reserve(m);
  size_t v1 = 0;
  size_t v2 = 0;
  size_t w = 0;
  for (size_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    edges.emplace_back(v1, v2, w);
  }
  std::cout << Boruvka(dsu, edges) << '\n';
  return 0;
}