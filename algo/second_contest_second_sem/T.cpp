#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

int64_t timer = 1;

struct Vertex {
  bool color = false;
  int64_t tin;
  int64_t tup;
  std::vector<int64_t> list;
};

void DFS1(std::vector<Vertex>& graph, std::unordered_set<int64_t>& points, int64_t v, int64_t parent) {
  graph[v].color = true;
  graph[v].tin = timer;
  graph[v].tup = timer;
  ++timer;
  int64_t child = 0;
  for (auto u : graph[v].list) {
    if (parent == u) {
      continue;
    }
    if (graph[u].color) {
      graph[v].tup = std::min(graph[v].tup, graph[u].tin);
    } else {
      DFS1(graph, points, u, v);
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

bool IsArticulation(std::unordered_set<int64_t>& points, int64_t check) {
  return (points.find(check) != points.end());
}

int64_t DFSNoArt(std::vector<Vertex>& graph, std::unordered_set<int64_t>& points, std::vector<int64_t>& ans, int64_t v);
int64_t DFSArt(std::vector<Vertex>& graph, std::unordered_set<int64_t>& points, std::vector<int64_t>& ans, int64_t v);

int64_t DFSArt(std::vector<Vertex>& graph, std::unordered_set<int64_t>& points, std::vector<int64_t>& ans, int64_t v) {
  graph[v].color = true;
  std::vector<int64_t> dfs_leafs;
  int64_t sum = 0;
  int64_t counter = 0;
  for (auto u : graph[v].list) {
    if (!graph[u].color) {
      if (IsArticulation(points, u)) {
        int64_t temp = DFSArt(graph, points, ans, u);
        counter += temp;
        if (graph[u].tup >= graph[v].tin) {
          dfs_leafs.push_back(temp);
          sum += dfs_leafs.back();
        }
      } else {
        int64_t temp = DFSNoArt(graph, points, ans, u);
        counter += temp;
        if (graph[u].tup >= graph[v].tin) {
          dfs_leafs.push_back(temp);
          sum += dfs_leafs.back();
        }
      }
    }
  }
  int64_t answer = (static_cast<int64_t>(graph.size()) - 2) * (static_cast<int64_t>(graph.size()) - 1) / 2;
  for (auto el : dfs_leafs) {
    answer -= (el * (el - 1) / 2);
  }
  answer -= static_cast<int64_t>(graph.size()) - 2;
  answer -= (static_cast<int64_t>(graph.size()) - 2 - sum) * (static_cast<int64_t>(graph.size()) - 3 - sum) / 2;
  ans[v] += answer;
  return 1 + counter;
}

int64_t DFSNoArt(std::vector<Vertex>& graph, std::unordered_set<int64_t>& points, std::vector<int64_t>& ans,
                 int64_t v) {
  graph[v].color = true;
  int64_t counter = 0;
  for (auto u : graph[v].list) {
    if (!graph[u].color) {
      if (IsArticulation(points, u)) {
        counter += DFSArt(graph, points, ans, u);
      } else {
        counter += DFSNoArt(graph, points, ans, u);
      }
    }
  }
  return 1 + counter;
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> graph(n + 1);
  std::unordered_set<int64_t> points;
  std::vector<int64_t> ans(n + 1, n - 1);
  int64_t v1 = 0;
  int64_t v2 = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    graph[v1].list.push_back(v2);
    graph[v2].list.push_back(v1);
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!graph[i].color) {
      DFS1(graph, points, static_cast<int64_t>(i), -1);
    }
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    graph[i].color = false;
  }
  if (IsArticulation(points, 1)) {
    DFSArt(graph, points, ans, 1);
  } else {
    DFSNoArt(graph, points, ans, 1);
  }
  for (size_t i = 1; i < graph.size(); ++i) {
    std::cout << ans[i] << '\n';
  }
  return 0;
}