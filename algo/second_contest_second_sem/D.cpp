#include <iostream>
#include <vector>
#include <queue>

struct Vertex {
  int shortest_path = -1;
  int color = 0;
};

void BFS(std::vector<std::vector<Vertex>>& vertex, std::vector<std::vector<int>>& table,
         std::queue<std::pair<int, int>>& queue) {
  while (!queue.empty()) {
    std::pair<int, int> u = queue.front();
    queue.pop();
    if (u.first > 0 && vertex[u.first - 1][u.second].color == 0) {
      vertex[u.first - 1][u.second].color = 1;
      vertex[u.first - 1][u.second].shortest_path = vertex[u.first][u.second].shortest_path + 1;
      table[u.first - 1][u.second] =
          std::min(vertex[u.first - 1][u.second].shortest_path, table[u.first - 1][u.second]);
      queue.emplace(u.first - 1, u.second);
    }
    if (u.second > 0 && vertex[u.first][u.second - 1].color == 0) {
      vertex[u.first][u.second - 1].color = 1;
      vertex[u.first][u.second - 1].shortest_path = vertex[u.first][u.second].shortest_path + 1;
      table[u.first][u.second - 1] =
          std::min(vertex[u.first][u.second - 1].shortest_path, table[u.first][u.second - 1]);
      queue.emplace(u.first, u.second - 1);
    }
    if (u.first < static_cast<int>(vertex.size() - 1) && vertex.at(u.first + 1).at(u.second).color == 0) {
      vertex[u.first + 1][u.second].color = 1;
      vertex[u.first + 1][u.second].shortest_path = vertex[u.first][u.second].shortest_path + 1;
      table[u.first + 1][u.second] =
          std::min(vertex[u.first + 1][u.second].shortest_path, table[u.first + 1][u.second]);
      queue.emplace(u.first + 1, u.second);
    }
    if (u.second < static_cast<int>(vertex[u.first].size() - 1) && vertex[u.first][u.second + 1].color == 0) {
      vertex[u.first][u.second + 1].color = 1;
      vertex[u.first][u.second + 1].shortest_path = vertex[u.first][u.second].shortest_path + 1;
      table[u.first][u.second + 1] =
          std::min(vertex[u.first][u.second + 1].shortest_path, table[u.first][u.second + 1]);
      queue.emplace(u.first, u.second + 1);
    }
    vertex[u.first][u.second].color = 2;
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1));
  std::vector<std::vector<Vertex>> buffer(n + 1, std::vector<Vertex>(m + 1));
  std::queue<std::pair<int, int>> queue;
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      std::cin >> table.at(i).at(j);
      if (table[i][j] == 1) {
        queue.emplace(i, j);
        buffer[i][j].color = 1;
        buffer[i][j].shortest_path = 0;
        table[i][j] = 0;
      } else {
        table[i][j] = 3000;
      }
    }
  }
  BFS(buffer, table, queue);
  for (size_t i = 1; i < table.size(); ++i) {
    for (size_t j = 1; j < table[i].size(); ++j) {
      std::cout << table[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}