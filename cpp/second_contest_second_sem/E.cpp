#include <iostream>
#include <unordered_map>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::unordered_map<std::string, std::string> map;
  size_t n = 0;
  std::cin >> n;
  std::string key;
  std::string value;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> key >> value;
    map.emplace(key, value);
    map.emplace(value, key);
  }
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> key;
    std::cout << map.find(key)->second << '\n';
  }
  return 0;
}