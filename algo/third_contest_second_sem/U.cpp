#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

struct Hash {
  size_t operator()(const std::pair<int, int>& val) const noexcept {
    return (val.first * val.first + val.first + 2 * val.first * val.second + 3 * val.second + val.second * val.second) /
           2;
  }
};

void FloydWarshall(std::vector<std::vector<int>>& d, std::vector<std::vector<int>>& parents,
                   std::unordered_map<std::pair<int, int>, int, Hash>& edges, std::vector<int> voyage) {
  for (size_t k = 1; k < d.size() - 1; ++k) {
    for (size_t i = 1; i < d.size() - 1; ++i) {
      for (size_t j = 1; j < d.size() - 1; ++j) {
        if (d[i][j] > d[i][k] + d[k][j] && d[i][k] != std::numeric_limits<int>::max() &&
            d[k][j] != std::numeric_limits<int>::max()) {
          d[i][j] = d[i][k] + d[k][j];
          parents[i][j] = parents[i][k];
        }
      }
    }
  }
  for (size_t i = 0; i < voyage.size() - 1; ++i) {
    for (size_t j = 1; j < d.size() - 1; ++j) {
      if (d[j][j] < 0 && d[voyage[i]][j] < std::numeric_limits<int>::max() &&
          d[j][voyage[i + 1]] < std::numeric_limits<int>::max()) {
        std::cout << "infinitely kind\n";
        return;
      }
    }
  }
  std::vector<int> ans;
  for (size_t i = 0; i < voyage.size() - 1; ++i) {
    for (int v = voyage[i]; v != voyage[i + 1]; v = parents[v][voyage[i + 1]]) {
      ans.push_back(edges.find({v, parents[v][voyage[i + 1]]})->second);
    }
  }
  std::cout << ans.size() << '\n';
  for (auto&& v : ans) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;
  std::vector<int> voyage(k);
  std::vector<std::vector<int>> graph(n + 2, std::vector<int>(n + 2, std::numeric_limits<int>::max()));
  std::vector<std::vector<int>> parents(n + 2, std::vector<int>(n + 2, -1));
  std::unordered_map<std::pair<int, int>, int, Hash> edges;
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  int counter = 1;
  for (int i = 1; i < n + 1; ++i) {
    graph[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    graph[v1][v2] = -w;
    parents[v1][v2] = v2;
    edges.emplace(std::piecewise_construct, std::forward_as_tuple(v1, v2), std::forward_as_tuple(counter++));
  }
  for (int i = 0; i < k; ++i) {
    std::cin >> voyage[i];
  }
  FloydWarshall(graph, parents, edges, voyage);
  return 0;
}