#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

struct Vertex {
  bool used = false;
  bool was = false;
  std::unordered_multiset<int> list;
};

void DFS(std::vector<Vertex>& vec, int v) {
  vec[v].used = true;
  for (auto u : vec[v].list) {
    if (!vec[u].used) {
      DFS(vec, u);
    }
  }
}

bool CheckEuler(std::vector<Vertex>& vec, std::vector<int>& degrees) {
  int counter = 0;
  for (size_t i = 1; i < vec.size(); ++i) {
    if (!vec[i].used && vec[i].was) {
      DFS(vec, static_cast<int>(i));
      ++counter;
    }
    if (degrees[i] != 0) {
      return false;
    }
  }
  return counter == 1;
}

void Euler(std::vector<Vertex>& vec, std::vector<int>& ans, int v) {
  while (!vec[v].list.empty()) {
    auto u = *vec[v].list.begin();
    vec[v].list.erase(vec[v].list.begin());
    Euler(vec, ans, u);
  }
  ans.push_back(v);
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> graph(m + 1);
  std::vector<int> degrees(m + 1, 0);
  std::vector<int> ans;
  int v1 = 0;
  int v2 = 0;
  int col = 0;
  bool first = true;
  int start = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> col >> v1;
    if (first) {
      start = v1;
      first = false;
    }
    for (int j = 0; j < col; ++j) {
      std::cin >> v2;
      graph[v1].list.insert(v2);
      graph[v1].was = true;
      graph[v2].was = true;
      ++degrees[v1];
      --degrees[v2];
      v1 = v2;
    }
  }
  if (CheckEuler(graph, degrees)) {
    Euler(graph, ans, start);
    std::reverse(ans.begin(), ans.end());
    int min = 10000000;
    size_t min_index = 0;
    for (size_t i = 0; i < ans.size(); ++i) {
      if (ans[i] < min) {
        min = ans[i];
        min_index = i;
      }
    }
    std::cout << ans.size() << ' ';
    for (size_t i = 0; i < ans.size(); ++i) {
      if ((i + min_index) % ans.size() == 0 && i > 0) {
        continue;
      }
      std::cout << ans[(i + min_index) % ans.size()] << ' ';
    }
    if (min_index > 0) {
      std::cout << min << '\n';
    }
  } else {
    std::cout << 0 << '\n';
  }
  return 0;
}