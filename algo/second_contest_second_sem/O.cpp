#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int timer = 1;

struct Vertex {
  bool color = false;
  int tin;
  int tup;
  std::vector<int> list;
};

void DFS(std::vector<std::vector<int>>& graph, std::vector<int>& tin, std::vector<int>& tup, std::vector<bool>& colors,
         std::set<int>& points, int v, int parent, int m) {
  colors[v] = true;
  tin[v] = timer;
  tup[v] = timer;
  ++timer;
  int child = 0;
  for (auto u : graph[v]) {
    if (parent == u) {
      continue;
    }
    if (colors[u]) {
      tup[v] = std::min(tup[v], tin[u]);
    } else {
      DFS(graph, tin, tup, colors, points, u, v, m);
      tup[v] = std::min(tup[v], tup[u]);
      if (tup[u] >= tin[v] && parent != -1 && v <= m) {
        points.insert(v);
      }
      ++child;
    }
  }
  if (parent == -1 && child > 1 && v <= m) {
    points.insert(v);
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + m + 1);
  std::vector<int> tin(n + m + 1);
  std::vector<int> tout(n + m + 1);
  std::vector<bool> colors(n + m + 1, false);
  std::set<int> points;
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2 >> v3;
    graph[i].push_back(v1 + m);
    graph[v1 + m].push_back(i);
    graph[i].push_back(v2 + m);
    graph[v2 + m].push_back(i);
    graph[i].push_back(v3 + m);
    graph[v3 + m].push_back(i);
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!colors[i]) {
      DFS(graph, tin, tout, colors, points, static_cast<int>(i), -1, m);
    }
  }
  std::cout << points.size() << '\n';
  for (auto& v : points) {
    std::cout << v << '\n';
  }
  return 0;
}