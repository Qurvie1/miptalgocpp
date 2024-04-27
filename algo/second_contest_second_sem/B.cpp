#include <iostream>
#include <vector>

struct Vertex {
  int color = 0;
  std::vector<int> list_;
};

void DFS(std::vector<Vertex>& vec, int v, int col, bool& fl) {
  vec[v].color = col;
  for (auto u : vec[v].list_) {
    if (vec[u].color == 0) {
      DFS(vec, u, -col, fl);
    } else if (vec[u].color != -col) {
      fl = true;
      return;
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> student(n + 1);
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    if (v1 == v2) {
      continue;
    }
    student[v1].list_.push_back(v2);
    student[v2].list_.push_back(v1);
  }
  bool fl = false;
  for (int i = 1; i < n + 1; ++i) {
    if (student[i].color == 0) {
      DFS(student, i, 1, fl);
    }
  }
  std::cout << (fl ? "NO" : "YES") << '\n';
  return 0;
}