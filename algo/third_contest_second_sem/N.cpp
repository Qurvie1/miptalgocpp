#include <vector>
#include <map>
#include <iostream>
#include <tuple>

struct Vertex {
  bool used = false;
  std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> adj_list;
};

int64_t DFS(std::vector<Vertex>& vec, int64_t u, int64_t c, int64_t t) {
  if (u == t) {
    return c;
  }
  vec[u].used = true;
  for (auto&& [v, cap, f, back] : vec[u].adj_list) {
    if (!vec[v].used && f < cap) {
      int64_t delta = DFS(vec, v, std::min(c, cap - f), t);
      if (delta > 0) {
        f += delta;
        std::get<2>(vec[v].adj_list[back]) -= delta;
        return delta;
      }
    }
  }
  return 0;
}

int64_t FordFulkerson(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  int64_t delta = DFS(vec, s, 1'000'000, t);
  int64_t ans = 0;
  while (delta) {
    ans += delta;
    for (auto&& [used, vect] : vec) {
      used = false;
    }
    delta = DFS(vec, s, 1'000'000, t);
  }
  return ans;
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> vec(n + 1);
  int64_t v1 = 0;
  int64_t v2 = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    vec[v1].adj_list.emplace_back(v2, w, 0, vec[v2].adj_list.size());
    vec[v2].adj_list.emplace_back(v1, 0, 0, vec[v1].adj_list.size() - 1);
  }
  std::cout << FordFulkerson(vec, 1, n) << '\n';
  return 0;
}