#include <vector>
#include <map>
#include <iostream>
#include <tuple>

struct Vertex {
  bool used = false;
  std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> adj_list;
};

int64_t DFS(std::vector<Vertex>& vec, int64_t u, int64_t c, int64_t t) {
  if (u == t) {
    return c;
  }
  vec[u].used = true;
  for (auto&& [v, cap, f, back] : vec[u].adj_list) {
    if (!vec[v].used && f < cap) {
      int64_t delta = DFS(vec, v, std::min(c, cap - f), t);
      if (delta > 0) {
        f += delta;
        std::get<2>(vec[v].adj_list[back]) -= delta;
        return delta;
      }
    }
  }
  return 0;
}

int64_t FordFulkerson(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  int64_t delta = DFS(vec, s, 1'000'000, t);
  int64_t ans = 0;
  while (delta) {
    ans += delta;
    for (auto&& [used, vect] : vec) {
      used = false;
    }
    delta = DFS(vec, s, 1'000'000, t);
  }
  return ans;
}

bool Checker(std::vector<Vertex>& vec, int64_t s, int64_t t) {
  FordFulkerson(vec, s, t);
  int64_t from = 0;
  int64_t to = 0;
  for (auto&& [u, cap, f, back] : vec[s].adj_list) {
    from += f;
    if (f != cap) {
      return false;
    }
  }
  for (auto&& [u, cap, f, back] : vec[t].adj_list) {
    auto&& [v, cap1, f1, back1] = vec[u].adj_list[back];
    to += f1;
    if (f1 != cap1) {
      return false;
    }
  }
  return from == to;
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> vec((n + 1) * (m + 1) + 3);
  std::vector<std::vector<char>> field(n + 1, std::vector(m + 1, '.'));
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      std::cin >> field[i][j];
    }
  }
  char symbol = 0;
  int valence = 0;
  int counter = 0;
  for (int64_t i = 1; i < n + 1; ++i) {
    for (int64_t j = 1; j < m + 1; ++j) {
      symbol = field[i][j];
      if (symbol == 'H') {
        valence = 1;
      } else if (symbol == 'C') {
        valence = 4;
      } else if (symbol == 'O') {
        valence = 2;
      } else if (symbol == 'N') {
        valence = 3;
      } else {
        continue;
      }
      ++counter;
      if ((i + j) % 2 == 0) {
        vec[(n + 1) * (m + 1) + 1].adj_list.emplace_back(i * m + j, valence, 0, vec[i * m + j].adj_list.size());
        vec[i * m + j].adj_list.emplace_back((n + 1) * (m + 1) + 1, 0, 0,
                                             vec[(n + 1) * (m + 1) + 1].adj_list.size() - 1);
      } else {
        vec[i * m + j].adj_list.emplace_back((n + 1) * (m + 1) + 2, valence, 0,
                                             vec[(n + 1) * (m + 1) + 2].adj_list.size());
        vec[(n + 1) * (m + 1) + 2].adj_list.emplace_back(i * m + j, 0, 0, vec[i * m + j].adj_list.size() - 1);
      }
      if (j != 1 && field[i][j - 1] != '.') {
        vec[i * m + j].adj_list.emplace_back(i * m + j - 1, 1, 0, vec[i * m + j - 1].adj_list.size());
        vec[i * m + j - 1].adj_list.emplace_back(i * m + j, 0, 0, vec[i * m + j].adj_list.size() - 1);
      }
      if (i != 1 && field[i - 1][j] != '.') {
        vec[i * m + j].adj_list.emplace_back((i - 1) * m + j, 1, 0, vec[(i - 1) * m + j].adj_list.size());
        vec[(i - 1) * m + j].adj_list.emplace_back(i * m + j, 0, 0, vec[i * m + j].adj_list.size() - 1);
      }
      if (j != m && field[i][j + 1] != '.') {
        vec[i * m + j].adj_list.emplace_back(i * m + j + 1, 1, 0, vec[i * m + j + 1].adj_list.size());
        vec[i * m + j + 1].adj_list.emplace_back(i * m + j, 0, 0, vec[i * m + j].adj_list.size() - 1);
      }
      if (i != n && field[i + 1][j] != '.') {
        vec[i * m + j].adj_list.emplace_back((i + 1) * m + j, 1, 0, vec[(i + 1) * m + j].adj_list.size());
        vec[(i + 1) * m + j].adj_list.emplace_back(i * m + j, 0, 0, vec[i * m + j].adj_list.size() - 1);
      }
    }
  }
  std::cout << (Checker(vec, (n + 1) * (m + 1) + 1, (n + 1) * (m + 1) + 2) && counter ? "Valid\n" : "Invalid\n");
  return 0;
}