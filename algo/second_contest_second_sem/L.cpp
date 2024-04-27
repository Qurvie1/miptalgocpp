#include <iostream>
#include <vector>
#include <deque>

void DFS1(std::vector<bool>& colors, std::vector<std::vector<int>>& list, std::deque<int>& ans, int v) {
  colors[v] = true;
  for (auto u : list[v]) {
    if (!colors[u]) {
      DFS1(colors, list, ans, u);
    }
  }
  ans.push_front(v);
}

void DFS2(std::deque<int>& components, std::vector<std::vector<int>>& list, int& counter, int v) {
  components[v] = counter;
  for (auto u : list[v]) {
    if (components[u] == -1) {
      DFS2(components, list, counter, u);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  int counter = 1;
  std::cin >> n >> m;
  std::vector<bool> colors(n + 1, false);
  std::vector<std::vector<int>> list1(n + 1);
  std::vector<std::vector<int>> list2(n + 1);
  std::deque<int> sort(n + 1);
  std::deque<int> components(n + 1, -1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    list1[v1].push_back(v2);
    list2[v2].push_back(v1);
  }
  for (size_t i = 1; i < list1.size(); ++i) {
    if (!colors[i]) {
      DFS1(colors, list1, sort, static_cast<int>(i));
    }
  }
  for (auto v : sort) {
    if (components[v] == -1) {
      DFS2(components, list2, counter, v);
      ++counter;
    }
  }
  std::cout << counter - 2 << '\n';
  for (size_t i = 1; i < list1.size(); ++i) {
    std::cout << components[i] << ' ';
  }
  return 0;
}