#include <iostream>
#include <vector>
#include <stack>

struct Vertex {
  int color = 0;
  std::vector<int> list_;
};

void DFS(std::vector<Vertex>& vec, int v, size_t& counter, std::deque<int>& deque) {
  vec[v].color = 1;
  ++counter;
  deque.push_front(v);
  for (auto u : vec[v].list_) {
    if (vec[u].color == 0) {
      vec[u].color = 1;
      DFS(vec, u, counter, deque);
    }
  }
  vec[v].color = 2;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> vec(n + 1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> v1 >> v2;
    vec[v1].list_.push_back(v2);
    vec[v2].list_.push_back(v1);
  }
  std::vector<size_t> counters;
  int count = 0;
  size_t counter = 0;
  std::deque<int> vertex;
  for (int i = 1; i < n + 1; ++i) {
    if (vec[i].color == 0) {
      DFS(vec, i, counter, vertex);
      counters.push_back(counter);
      counter = 0;
      ++count;
    }
  }
  std::cout << count << '\n';
  for (size_t i = 0; i < counters.size(); ++i) {
    std::cout << counters[i] << '\n';
    for (size_t j = 0; j < counters[i]; ++j) {
      std::cout << vertex.back() << ' ';
      vertex.pop_back();
    }
    std::cout << '\n';
  }
  return 0;
}