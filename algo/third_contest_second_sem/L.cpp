#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

const int kWMAX = 10;
const int kEMAX = 3 * 10e6;

void Ford(std::vector<std::tuple<int, int, int>>& edges, std::vector<int>& dists, int s) {
  dists[s] = 0;
  for (size_t i = 0; i < dists.size() - 1; ++i) {
    for (auto&& [v, u, w] : edges) {
      if (dists[u] > dists[v] + w && dists[v] != kWMAX * kEMAX + 1) {
        dists[u] = dists[v] + w;
      }
    }
  }
}

void Dijkstra(std::vector<std::vector<int>>& d, std::vector<std::vector<std::pair<int, int>>>& adj_list, int s) {
  d[s][s] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
  queue.emplace(0, s);
  while (!queue.empty()) {
    auto [cur, v] = queue.top();
    queue.pop();
    if (cur > d[s][v]) {
      continue;
    }
    for (auto [u, w] : adj_list[v]) {
      if (d[s][u] > d[s][v] + w) {
        d[s][u] = d[s][v] + w;
        queue.emplace(d[s][u], u);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> adj_list(n + 1);
  std::vector<std::tuple<int, int, int>> edges;
  std::vector<int> dist(n + 1, kWMAX * kEMAX + 1);
  std::vector<std::vector<int>> d(n + 1, std::vector<int>(n + 1, kWMAX * kEMAX + 1));
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    adj_list[v1].emplace_back(v2, w);
    edges.emplace_back(v1, v2, w);
  }
  for (int i = 0; i < n; ++i) {
    adj_list[n].emplace_back(i, 0);
  }
  Ford(edges, dist, n);
  for (int i = 0; i < n; ++i) {
    for (auto&& [u, w] : adj_list[i]) {
      w = w + dist[i] - dist[u];
    }
  }

  for (int i = 0; i < n; ++i) {
    Dijkstra(d, adj_list, i);
  }
  int max = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i < j) {
        d[i][j] = d[i][j] + dist[j] - dist[i];
      }
      max = (max < d[i][j] && d[i][j] < kEMAX * kWMAX + 1 ? d[i][j] : max);
    }
  }
  std::cout << max << '\n';
  return 0;
}