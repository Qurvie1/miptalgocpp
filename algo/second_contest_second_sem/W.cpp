#include <iostream>
#include <vector>
#include <optional>

enum class Color { kWHITE, kGRAY, kBLACK };

struct Vertex {
  Color used = Color::kWHITE;
  std::vector<std::pair<int64_t, int64_t>> edges;
  std::pair<int64_t, int64_t> monome;
};

void DFS(std::vector<Vertex>& vec, int64_t v, std::optional<int64_t>& x) {
  vec[v].used = Color::kGRAY;
  for (auto&& [u, w] : vec[v].edges) {
    if (vec[u].used == Color::kWHITE) {
      vec[u].monome = {-vec[v].monome.first, w - vec[v].monome.second};
      DFS(vec, u, x);
    } else if (vec[u].used == Color::kGRAY && vec[u].monome.first != -vec[v].monome.first && !x.has_value()) {
      x = (w - vec[v].monome.second - vec[u].monome.second) / (vec[v].monome.first + vec[u].monome.first);
    }
  }
  vec[v].used = Color::kBLACK;
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<Vertex> vec(n);
  int64_t v1 = 0;
  int64_t v2 = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    --v1;
    --v2;
    --w;
    --w;
    vec[v1].edges.emplace_back(v2, w);
    vec[v2].edges.emplace_back(v1, w);
  }
  std::optional<int64_t> x;
  vec[0].monome = {1, 0};
  DFS(vec, 0, x);
  if (x.has_value()) {
    for (int64_t i = 0; i < n; i++) {
      std::cout << vec[i].monome.first * (*x) + vec[i].monome.second + 1 << " ";
    }
    std::cout << "\n";
    return 0;
  }
  int64_t sum_first = 0;
  int64_t sum_second = 0;
  for (int64_t i = 0; i < n; ++i) {
    sum_first += vec[i].monome.first;
    sum_second += vec[i].monome.second;
  }
  if (sum_first != 0) {
    auto x = (n * (n - 1) / 2 - sum_second) / (sum_first);
    for (int64_t i = 0; i < n; ++i) {
      std::cout << vec[i].monome.first * x + vec[i].monome.second + 1 << ' ';
    }
    std::cout << "\n";
    return 0;
  }
  int64_t lower_bound = 0;
  int64_t upper_bound = n;
  for (int64_t i = 0; i < n; ++i) {
    if (vec[i].monome.first > 0) {
      lower_bound = std::max(lower_bound, -vec[i].monome.second);
      upper_bound = std::min(upper_bound, n - vec[i].monome.second - 1);
    } else {
      lower_bound = std::max(lower_bound, vec[i].monome.second - n + 1);
      upper_bound = std::min(upper_bound, vec[i].monome.second);
    }
  }
  std::vector<int64_t> answer;
  answer.reserve(n);
  std::vector<bool> in_answer(n, false);
  for (int64_t x = lower_bound; x <= upper_bound; x++) {
    for (int64_t i = 0; i < n; ++i) {
      if (!in_answer[vec[i].monome.first * x + vec[i].monome.second]) {
        in_answer[vec[i].monome.first * x + vec[i].monome.second] = true;
        answer.emplace_back(vec[i].monome.first * x + vec[i].monome.second + 1);
      } else {
        answer.clear();
        std::fill(in_answer.begin(), in_answer.end(), false);
        break;
      }
    }
    if (in_answer[0]) {
      break;
    }
  }
  for (const auto& x : answer) {
    std::cout << x << " ";
  }
  std::cout << "\n";
  return 0;
}