#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int timer = 1;

struct Vertex {
  bool color = false;
  bool bridge = false;
  int tin;
  int tup;
  std::vector<std::pair<int, int>> list;
};

void DFS(std::vector<Vertex>& graph, std::set<int>& bridges, int v, int parent) {
  graph[v].color = true;
  graph[v].tin = timer;
  graph[v].tup = timer;
  ++timer;
  for (auto [u, number] : graph[v].list) {
    if (parent == u) {
      continue;
    }
    if (graph[u].color) {
      graph[v].tup = std::min(graph[v].tup, graph[u].tup);
    } else {
      DFS(graph, bridges, u, v);
      graph[v].tup = std::min(graph[v].tup, graph[u].tup);
      if (graph[u].tup > graph[v].tin) {
        int counter = 0;
        for (auto p : graph[v].list) {
          if (p.first == u) {
            ++counter;
            if (counter > 1) {
              break;
            }
          }
        }
        if (counter == 1) {
          bridges.insert(number);
        }
      }
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  int counter = 1;
  std::vector<Vertex> graph(n + 1);
  std::set<int> bridges;
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    graph[v1].list.emplace_back(v2, counter);
    graph[v2].list.emplace_back(v1, counter);
    ++counter;
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!graph[i].color) {
      DFS(graph, bridges, static_cast<int>(i), -1);
    }
  }
  std::cout << bridges.size() << '\n';
  for (auto& v : bridges) {
    std::cout << v << '\n';
  }
  return 0;
}