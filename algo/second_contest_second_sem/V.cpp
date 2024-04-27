#include <iostream>
#include <vector>
#include <queue>

bool HasRunoff(std::vector<std::vector<int>>& map, size_t i, size_t j) {
  return map[i][j] > map[i][j - 1] || map[i][j] > map[i][j + 1] || map[i][j] > map[i - 1][j] ||
         map[i][j] > map[i + 1][j];
}

bool HasEqual(std::vector<std::vector<int>>& map, size_t i, size_t j) {
  return map[i][j] == map[i][j - 1] || map[i][j] == map[i][j + 1] || map[i][j] == map[i - 1][j] ||
         map[i][j] == map[i + 1][j];
}

void BFS(std::vector<std::vector<int>>& map, std::vector<std::vector<bool>>& used, int start_i, int start_j,
         bool& run) {
  used[start_i][start_j] = true;
  if (!run) {
    run = HasRunoff(map, start_i, start_j);
  }
  if (!used[start_i + 1][start_j] && map[start_i + 1][start_j] == map[start_i][start_j]) {
    BFS(map, used, start_i + 1, start_j, run);
  }
  if (!used[start_i][start_j + 1] && map[start_i][start_j + 1] == map[start_i][start_j]) {
    BFS(map, used, start_i, start_j + 1, run);
  }
  if (!used[start_i][start_j - 1] && map[start_i][start_j - 1] == map[start_i][start_j]) {
    BFS(map, used, start_i, start_j - 1, run);
  }
  if (!used[start_i - 1][start_j] && map[start_i - 1][start_j] == map[start_i][start_j]) {
    BFS(map, used, start_i - 1, start_j, run);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> map(n + 2, std::vector<int>(m + 2, 10001));
  std::vector<std::vector<bool>> used(n + 2, std::vector<bool>(m + 2, false));
  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      std::cin >> map[i][j];
    }
  }
  int counter = 0;
  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      if (used[i][j]) {
        continue;
      }
      if (!HasEqual(map, i, j) && HasRunoff(map, i, j)) {
        used[i][j] = true;
      } else if (!HasEqual(map, i, j) && !HasRunoff(map, i, j)) {
        ++counter;
      }
      if (HasEqual(map, i, j)) {
        bool run = false;
        BFS(map, used, static_cast<int>(i), static_cast<int>(j), run);
        if (!run) {
          ++counter;
        }
      }
    }
  }
  std::cout << counter << '\n';
  return 0;
}