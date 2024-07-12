#include <iostream>
#include <vector>

class DSU {
 public:
  explicit DSU(int vertex)
      : parent_(std::vector<int>(vertex + 1))
      , rank_(std::vector<int>(vertex + 1, 1))
      , weights_(std::vector<int>(vertex + 1, 0)) {
    for (int i = 1; i < vertex; ++i) {
      parent_[i] = i;
    }
  }

  int Leader(int v) {
    return (parent_[v] == v) ? v : parent_[v] = Leader(parent_[v]);
  }

  void Unite(int a, int b, int w) {
    int l1 = Leader(a);
    int l2 = Leader(b);
    if (rank_[l1] > rank_[l2]) {
      std::swap(l1, l2);
    }
    rank_[l2] = std::max(rank_[l2], rank_[l1] + 1);
    weights_[l2] += (l1 == l2 ? w : weights_[l1] + w);
    parent_[l1] = l2;
  }

  int Weight(int v) const {
    return weights_[v];
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> weights_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  int action = 0;
  DSU dsu(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> action;
    if (action == 1) {
      int v1 = 0;
      int v2 = 0;
      int w = 0;
      std::cin >> v1 >> v2 >> w;
      dsu.Unite(v1, v2, w);
    } else if (action == 2) {
      int v = 0;
      std::cin >> v;
      std::cout << dsu.Weight(dsu.Leader(v)) << '\n';
    }
  }
  return 0;
}