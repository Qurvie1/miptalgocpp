#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

int timer = 1;

struct Vertex {
  bool color = false;
  int tin;
  int tup;
  std::vector<int> list;
};

void DFS(std::vector<Vertex>& graph, std::set<std::pair<int, int>>& bridges, int v, int parent) {
  graph[v].color = true;
  graph[v].tin = timer;
  graph[v].tup = timer;
  ++timer;
  for (auto u : graph[v].list) {
    if (parent == u) {
      continue;
    }
    if (graph[u].color) {
      graph[v].tup = std::min(graph[v].tup, graph[u].tup);
    } else {
      DFS(graph, bridges, u, v);
      graph[v].tup = std::min(graph[v].tup, graph[u].tup);
      if (graph[u].tup > graph[v].tin) {
        bridges.emplace(v, u);
      }
    }
  }
}

bool IsBridge(int v, int u, std::set<std::pair<int, int>>& bridges) {
  return bridges.find({v, u}) != bridges.end() || bridges.find({u, v}) != bridges.end();
}

void BFS(std::vector<Vertex>& vec, std::set<std::pair<int, int>>& bridges, std::vector<int>& bridge_count, int start,
         int& components) {
  std::queue<int> queue;
  queue.push(start);
  int v = 0;
  while (!queue.empty()) {
    v = queue.front();
    queue.pop();
    vec[v].color = true;
    for (auto u : vec[v].list) {
      if (IsBridge(v, u, bridges)) {
        bridge_count[components]++;
        continue;
      }
      if (vec[u].color) {
        continue;
      }
      queue.push(u);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> graph(n + 1);
  std::set<std::pair<int, int>> bridges;
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    graph[v1].list.emplace_back(v2);
    graph[v2].list.emplace_back(v1);
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!graph[i].color) {
      DFS(graph, bridges, static_cast<int>(i), -1);
    }
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    graph[i].color = false;
  }
  int components = 0;
  std::vector<int> bridge_count(n + 1);
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!graph[i].color) {
      ++components;
      BFS(graph, bridges, bridge_count, static_cast<int>(i), components);
    }
  }
  int leafs = 0;
  for (int i = 1; i <= components; ++i) {
    if (bridge_count[i] == 1) {
      ++leafs;
    }
  }
  std::cout << (leafs + 1) / 2 << '\n';
  return 0;
}