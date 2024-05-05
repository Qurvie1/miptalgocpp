#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <functional>

int Min(int& first, int& second, int& third) {
  return std::min(std::min(first, second), third);
}

int Max(int& first, int& second, int& third) {
  return std::max(std::max(first, second), third);
}

int Median(int& first, int& second, int& third) {
  return first + second + third - Max(first, second, third) - Min(first, second, third);
}

size_t CantorsFunc(size_t first, size_t second) {
  return (first * first + first + 2 * first * second + 3 * second + second * second) / 2;
}

size_t CantorsTriple(size_t first, size_t second, size_t third) {
  return CantorsFunc(CantorsFunc(first, second), third);
}

struct Triple {
  int first;
  int second;
  int third;
  auto operator<=>(const Triple&) const noexcept = default;
  Triple(int a, int b, int c) : first(Min(a, b, c)), second(Median(a, b, c)), third(Max(a, b, c)) {
  }
};

struct Hash {
  size_t operator()(const Triple& val) const noexcept {
    return CantorsTriple(static_cast<size_t>(val.first), static_cast<size_t>(val.second),
                         static_cast<size_t>(val.third));
  }
};

std::vector<int> SystemSolver(std::vector<int>& values, std::vector<int>& args, int& n, bool& fl,
                              std::vector<int>& checker) {
  int x = (args[0] + args[1] + args[2] - 2 * args[3]);
  if (x <= 0 || x / 3 > n || x % 3 != 0) {
    fl = false;
  }
  int y = (-2 * args[0] + args[1] + args[2] + args[3]);
  if (y <= 0 || y / 3 > n || y % 3 != 0) {
    fl = false;
  }
  int z = (args[0] - 2 * args[1] + args[2] + args[3]);
  if (z <= 0 || z / 3 > n || z % 3 != 0) {
    fl = false;
  }
  int t = (args[0] + args[1] - 2 * args[2] + args[3]);
  if (t <= 0 || t / 3 > n || t % 3 != 0) {
    fl = false;
  }
  if (x == y || y == z || z == t || x == z || x == t || y == t) {
    fl = false;
  }
  std::vector<int> answer(n + 1);
  checker[x / 3] = values[0];
  checker[y / 3] = values[1];
  checker[z / 3] = values[2];
  checker[t / 3] = values[3];
  answer[values[0]] = x / 3;
  answer[values[1]] = y / 3;
  answer[values[2]] = z / 3;
  answer[values[3]] = t / 3;
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int t = 0;
  std::cin >> n >> t;
  std::unordered_map<Triple, int, Hash> unions;
  std::vector<std::unordered_set<int>> list(n + 1);
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  int v4 = 0;
  for (int i = 0; i < t; ++i) {
    std::cin >> v1 >> v2 >> v3 >> v4;
    unions.insert({Triple(v1, v2, v3), v4});
    list[v1].insert(v2);
    list[v1].insert(v3);
    list[v2].insert(v1);
    list[v2].insert(v3);
    list[v3].insert(v1);
    list[v3].insert(v2);
  }
  std::vector<int> vals;
  std::vector<int> args(4);
  for (int i = 1; i < n + 1; ++i) {
    if (list[i].size() >= list.size() - 2 && vals.size() < 3) {
      vals.push_back(i);
      continue;
    }
    if (vals.size() == 3) {
      break;
    }
  }
  if (vals.size() == 3) {
    for (int i = 1; i < n + 1; ++i) {
      if (i != vals[0] && i != vals[1] && i != vals[2]) {
        vals.push_back(i);
        break;
      }
    }
  }
  auto it1 = unions.find(Triple(vals[0], vals[2], vals[3]));
  auto it2 = unions.find(Triple(vals[0], vals[1], vals[3]));
  auto it3 = unions.find(Triple(vals[0], vals[1], vals[2]));
  auto it4 = unions.find(Triple(vals[1], vals[2], vals[3]));
  if (it1 == unions.end() || it2 == unions.end() || it3 == unions.end() || it4 == unions.end()) {
    std::cout << "Impossible\n";
    return 0;
  }
  args[0] = it1->second;
  args[1] = it2->second;
  args[2] = it3->second;
  args[3] = it4->second;
  bool fl = true;
  std::vector<int> checker(n + 1);
  auto map = SystemSolver(vals, args, n, fl, checker);
  if (!fl) {
    std::cout << "Impossible\n";
    return 0;
  }
  int checker1 = map[vals[0]];
  int checker2 = map[vals[1]];
  for (int i = 1; i < n + 1; ++i) {
    if (i != vals[0] && i != vals[1] && i != vals[2] && i != vals[3]) {
      auto it = unions.find(Triple(vals[0], vals[1], i));
      int number = it->second - checker1 - checker2;
      if (number <= 0 || number > n) {
        std::cout << "Impossible\n";
        return 0;
      }
      map[i] = number;
      checker[number] = i;
    }
  }
  for (auto&& [u, v] : unions) {
    if (map[u.first] + map[u.second] + map[u.third] != v) {
      std::cout << "Impossible\n";
      return 0;
    }
  }
  std::cout << "Possible\n";
  for (size_t i = 1; i < map.size(); ++i) {
    std::cout << map[i] << ' ';
  }
  return 0;
}