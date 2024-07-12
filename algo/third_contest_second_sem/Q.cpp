#include <vector>
#include <map>
#include <iostream>
#include <tuple>
#include <queue>
#include <limits>

struct Vertex {
  int shortest_path = std::numeric_limits<int>::max();
  std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> adj_list;
};

int64_t DFS(std::vector<Vertex>& vec, std::vector<size_t>& deleted, int64_t v, int64_t t, int64_t c) {
  if (v == t || c == 0) {
    return c;
  }
  for (size_t i = deleted[v]; i < vec[v].adj_list.size(); ++i) {
    auto&& [u, cap, f, back] = vec[v].adj_list[i];
    if (vec[v].shortest_path + 1 == vec[u].shortest_path) {
      if (f < cap) {
        int64_t delta = DFS(vec, deleted, u, t, std::min(c, cap - f));
        if (delta > 0) {
          f += delta;
          std::get<2>(vec[u].adj_list[back]) -= delta;
          return delta;
        }
      }
    }
    deleted[v]++;
  }
  return 0;
}

bool BFS(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  std::queue<int64_t> queue;
  int64_t currv = 0;
  for (auto&& [path, vect] : vec) {
    path = std::numeric_limits<int>::max();
  }
  vec[s].shortest_path = 0;
  queue.push(s);
  while (!queue.empty()) {
    currv = queue.front();
    queue.pop();
    for (auto&& [v, cap, f, back] : vec[currv].adj_list) {
      if (vec[v].shortest_path == std::numeric_limits<int>::max() && (f < cap)) {
        vec[v].shortest_path = vec[currv].shortest_path + 1;
        queue.push(v);
      }
    }
  }
  return vec[t].shortest_path != std::numeric_limits<int>::max();
}

int64_t Dinic(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  int64_t delta = 0;
  int64_t ans = 0;
  std::vector<size_t> deleted(vec.size());
  while (BFS(vec, s, t)) {
    std::fill(deleted.begin(), deleted.end(), 0);
    delta = DFS(vec, deleted, s, t, std::numeric_limits<int64_t>::max());
    while (delta != 0) {
      ans += delta;
      delta = DFS(vec, deleted, s, t, std::numeric_limits<int64_t>::max());
    }
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
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
  std::cout << Dinic(vec, 1, n) << '\n';
  return 0;
}