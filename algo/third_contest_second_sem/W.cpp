#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>
#include <algorithm>
#include <map>

struct Vertex {
  int64_t dist = std::numeric_limits<int64_t>::max();
  std::vector<std::pair<int64_t, int64_t>> list_;
};

class DSU {
 public:
  explicit DSU(int64_t vertex) : parent_(std::vector<int64_t>(vertex + 1)), rank_(std::vector<int64_t>(vertex + 1, 1)) {
    for (int64_t i = 1; i < vertex; ++i) {
      parent_[i] = i;
    }
  }

  int64_t Leader(int64_t v) {
    return (parent_[v] == v) ? v : parent_[v] = Leader(parent_[v]);
  }

  void Unite(int64_t a, int64_t b) {
    int64_t l1 = Leader(a);
    int64_t l2 = Leader(b);
    if (l1 == l2) {
      return;
    }
    if (rank_[l1] > rank_[l2]) {
      std::swap(l1, l2);
    }
    rank_[l2] = std::max(rank_[l2], rank_[l1] + 1);
    parent_[l1] = l2;
  }

 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
};

std::vector<bool> Dijkstra(std::vector<Vertex>& vec, DSU& dsu,
                           std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>>& bids,
                           std::vector<int64_t>& stations) {
  int64_t radius = -1;
  int64_t counter = 0;
  std::vector<bool> ans(bids.size());
  std::multimap<int64_t, std::pair<int64_t, int64_t>> waiting;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  for (auto&& v : stations) {
    queue.emplace(0, v);
    vec[v].dist = 0;
  }
  while (!queue.empty()) {
    auto [cur, v] = queue.top();
    if (cur > radius) {
      while (true) {
        auto& [start, end, cap, number] = bids[counter];
        if (2 * cur >= cap) {
          auto it = waiting.begin();
          while (it != waiting.end()) {
            if (2 * it->first > cap) {
              break;
            }
            dsu.Unite(it->second.first, it->second.second);
            it = waiting.erase(it);
          }
          ans[number] = (dsu.Leader(start) == dsu.Leader(end));
          ++counter;
          if (counter == static_cast<int64_t>(bids.size())) {
            break;
          }
        } else {
          break;
        }
      }
    }
    queue.pop();
    if (queue.empty()) {
      queue.emplace(cur + 1, 1);
    }
    if (counter >= static_cast<int64_t>(bids.size())) {
      break;
    }
    if (cur > vec[v].dist) {
      continue;
    }
    for (auto& [u, w] : vec[v].list_) {
      if (vec[u].dist > vec[v].dist + w) {
        vec[u].dist = vec[v].dist + w;
        queue.emplace(vec[u].dist, u);
        waiting.emplace(std::piecewise_construct, std::forward_as_tuple(vec[v].dist + w), std::forward_as_tuple(u, v));
      } else {
        waiting.emplace(std::piecewise_construct, std::forward_as_tuple((vec[u].dist + vec[v].dist + w) / 2),
                        std::forward_as_tuple(u, v));
      }
    }
    radius = cur;
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t s = 0;
  int64_t m = 0;
  std::cin >> n >> s >> m;
  std::vector<int64_t> stations(s);
  for (int64_t i = 0; i < s; ++i) {
    std::cin >> stations[i];
  }
  std::vector<Vertex> graph(n + 1);
  int64_t v1 = 0;
  int64_t v2 = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    graph[v1].list_.emplace_back(v2, 2 * w);
    graph[v2].list_.emplace_back(v1, 2 * w);
  }
  int64_t q = 0;
  std::cin >> q;
  std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> asks;
  for (int64_t i = 0; i < q; ++i) {
    std::cin >> v1 >> v2 >> w;
    asks.emplace_back(v1, v2, 2 * w, i);
  }
  std::sort(asks.begin(), asks.end(),
            [](const std::tuple<int64_t, int64_t, int64_t, int64_t>& first,
               std::tuple<int64_t, int64_t, int64_t, int64_t>& sec) { return std::get<2>(first) < std::get<2>(sec); });
  DSU dsu(n);
  auto answer = Dijkstra(graph, dsu, asks, stations);
  for (auto&& v : answer) {
    std::cout << (v ? "YES\n" : "NO\n");
  }
  return 0;
}