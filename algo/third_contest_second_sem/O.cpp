#include <vector>
#include <map>
#include <iostream>
#include <tuple>
#include <queue>

struct Vertex {
  bool used = false;
  int shortest_path = -1;
  int64_t pred = -1;
  std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> adj_list;
};

int64_t BFS(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  vec[s].used = true;
  std::queue<int64_t> queue;
  std::vector<int64_t> flows(vec.size(), 0);
  int64_t currv = 0;
  queue.push(s);
  flows[s] = 1'000'000;
  while (!queue.empty()) {
    currv = queue.front();
    queue.pop();
    for (auto&& [v, cap, f, back] : vec[currv].adj_list) {
      if (!vec[v].used && f < cap) {
        if (std::min(cap - f, flows[currv]) > flows[v]) {
          flows[v] = std::min(cap - f, flows[currv]);
          vec[v].shortest_path = vec[currv].shortest_path + 1;
          vec[v].pred = back;
          vec[v].used = true;
          queue.push(v);
        }
      }
    }
  }
  return flows[t];
}

int64_t EdmondsCarp(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  int64_t delta = BFS(vec, s, t);
  int64_t ans = 0;
  while (delta) {
    ans += delta;
    int64_t start = t;
    int64_t next = 0;
    while (start != s) {
      std::get<2>(vec[start].adj_list[vec[start].pred]) -= delta;
      next = std::get<0>(vec[start].adj_list[vec[start].pred]);
      std::get<2>(vec[next].adj_list[std::get<3>(vec[start].adj_list[vec[start].pred])]) += delta;
      start = next;
    }
    for (auto&& [used, v1, v2, vect] : vec) {
      used = false;
    }
    delta = BFS(vec, s, t);
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
  std::cout << EdmondsCarp(vec, 1, n) << '\n';
  return 0;
}