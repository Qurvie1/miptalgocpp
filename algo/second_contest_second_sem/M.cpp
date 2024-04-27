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

void DFS(std::vector<Vertex>& graph, std::set<int>& points, int v, int parent) {
  graph[v].color = true;
  graph[v].tin = timer;
  graph[v].tup = timer;
  ++timer;
  int child = 0;
  for (auto u : graph[v].list) {
    if (parent == u) {
      continue;
    }
    if (graph[u].color) {
      graph[v].tup = std::min(graph[v].tup, graph[u].tin);
    } else {
      DFS(graph, points, u, v);
      graph[v].tup = std::min(graph[v].tup, graph[u].tup);
      if (graph[u].tup >= graph[v].tin && parent != -1) {
        points.insert(v);
      }
      ++child;
    }
  }
  if (parent == -1 && child > 1) {
    points.insert(v);
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> graph(n + 1);
  std::set<int> points;
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    graph[v1].list.push_back(v2);
    graph[v2].list.push_back(v1);
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!graph[i].color) {
      DFS(graph, points, static_cast<int>(i), -1);
    }
  }
  std::cout << points.size() << '\n';
  for (auto& v : points) {
    std::cout << v << '\n';
  }
  return 0;
}