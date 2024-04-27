#include <iostream>
#include <vector>

int counter = 0;

struct Vertex {
  int color = 0;
  bool used = false;
  std::vector<int> list_;
};

void DFS(std::vector<Vertex>& vec, int v, int start) {
  for (auto u : vec[v].list_) {
    if (vec[u].color == 0) {
      vec[u].color = 1;
      DFS(vec, u, start);
    } else if (vec[u].used && u != start) {
      --counter;
      vec[u].used = false;
    }
  }
  vec[v].color = 2;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Vertex> vec(n + 1);
  int v = 0;
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> v;
    vec[v].list_.push_back(i);
  }
  for (int i = 1; i < n + 1; ++i) {
    if (vec[i].color == 0) {
      ++counter;
      DFS(vec, i, i);
      vec[i].used = true;
    }
  }
  std::cout << counter << '\n';
  return 0;
}