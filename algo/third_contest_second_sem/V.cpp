#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>
#include <algorithm>

struct Distance {
  int64_t dist = std::numeric_limits<int64_t>::max();
  int16_t prev = -1;
  int16_t prev_time = -1;
};

void Ford(std::vector<std::vector<std::tuple<int16_t, int64_t, int16_t>>>& vec, std::vector<std::vector<Distance>>& d,
          int s, int k) {
  d[0][s].dist = 0;
  std::vector<std::queue<int64_t>> queue(k + 1);
  queue[0].push(s);
  for (int64_t p = 0; p <= k; ++p) {
    if (queue[p].empty()) {
      continue;
    }
    bool is_change = false;
    while (!queue[p].empty()) {
      auto curr = queue[p].front();
      queue[p].pop();
      for (const auto& [vertex, weight, time] : vec[curr]) {
        if (p + time > k) {
          continue;
        }
        if (d[p][curr].prev == vertex) {
          continue;
        }
        if ((d[p][curr].dist != std::numeric_limits<int64_t>::max()) &&
            (d[p + time][vertex].dist > d[p][curr].dist + weight)) {

          d[p + time][vertex].dist = d[p][curr].dist + weight;
          d[p + time][vertex].prev = static_cast<int16_t>(curr);
          d[p + time][vertex].prev_time = static_cast<int16_t>(p);
          queue[p + time].push(vertex);
          is_change = true;
        }
      }
    }
    if (!is_change) {
      break;
    }
  }
}

void Solver(std::vector<std::vector<std::tuple<int16_t, int64_t, int16_t>>>& edges,
            std::vector<std::vector<Distance>>& dists, int s, int k, int n) {
  Ford(edges, dists, s, k);
  int64_t minrun = std::numeric_limits<int64_t>::max();
  int64_t maxtime = std::numeric_limits<int64_t>::max();
  for (int i = 0; i <= k; ++i) {
    if (dists[i][n].dist >= 0 && dists[i][n].dist < minrun) {
      minrun = dists[i][n].dist;
      maxtime = i;
    }
  }
  if (minrun == std::numeric_limits<int64_t>::max()) {
    std::cout << -1 << '\n';
    return;
  }
  std::vector<int64_t> path;
  path.push_back(n);
  int64_t prev_time = dists[maxtime][n].prev_time;
  int64_t prev = dists[maxtime][n].prev;
  while (prev != -1) {
    int64_t time = prev_time;
    path.emplace_back(prev);
    prev_time = dists[time][prev].prev_time;
    prev = dists[time][prev].prev;
  }
  std::cout << minrun << '\n';
  std::cout << path.size() << '\n';
  for (size_t i = path.size() - 1; i > 0; --i) {
    std::cout << path[i] << ' ';
  }
  std::cout << path[0] << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int max_time = 0;
  std::cin >> n >> m >> max_time;
  std::vector<std::vector<Distance>> dist(max_time + 5, std::vector<Distance>(n + 1));
  std::vector<std::vector<std::tuple<int16_t, int64_t, int16_t>>> edges(n + 1);
  int16_t v1 = 0;
  int16_t v2 = 0;
  int64_t w = 0;
  int16_t time = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2 >> w >> time;
    edges[v1].emplace_back(v2, w, time);
    edges[v2].emplace_back(v1, w, time);
  }
  Solver(edges, dist, 1, max_time, n);
  return 0;
}