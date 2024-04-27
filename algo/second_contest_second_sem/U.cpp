#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

enum class Color { kWHITE, kGRAY, kBLACK };

struct Vertex {
  bool is_hydro = false;
  Color used = Color::kWHITE;
  std::vector<int> list;
};

bool DFS(std::vector<Vertex>& vec, int v, int p = -1) {
  if ((vec[v].is_hydro && vec[v].list.size() != 1) || (!vec[v].is_hydro && vec[v].list.size() != 4)) {
    return false;
  }
  if (vec[v].used == Color::kGRAY) {
    return false;
  }
  vec[v].used = Color::kGRAY;
  for (auto u : vec[v].list) {
    if (u != p) {
      if (!DFS(vec, u, v)) {
        return false;
      }
    }
  }
  vec[v].used = Color::kBLACK;
  return true;
}

bool IsAlkan(std::vector<Vertex>& vec) {
  int counter = 0;
  for (size_t i = 1; i < vec.size(); ++i) {
    if (vec[i].used == Color::kWHITE) {
      ++counter;
      if (!DFS(vec, static_cast<int>(i))) {
        return false;
      }
    }
  }
  return counter == 1;
}

bool IsMultiply(std::vector<Vertex>& vec, int v1, int v2) {
  return (std::find(vec[v1].list.begin(), vec[v1].list.end(), v2) != vec[v1].list.end());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::cin.ignore();
  std::string text;
  std::getline(std::cin, text);
  int counter = 1;
  std::vector<Vertex> atoms(n + 1);
  for (auto el : text) {
    if (el == 'H') {
      atoms[counter++].is_hydro = true;
    } else if (el == 'C') {
      counter++;
    }
  }
  int v1 = 0;
  int v2 = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    if (IsMultiply(atoms, v1, v2) || (atoms[v1].is_hydro && atoms[v2].is_hydro)) {
      std::cout << "NO" << '\n';
      return 0;
    }
    atoms[v1].list.push_back(v2);
    atoms[v2].list.push_back(v1);
  }
  std::cout << (IsAlkan(atoms) ? "YES" : "NO") << '\n';
  return 0;
}