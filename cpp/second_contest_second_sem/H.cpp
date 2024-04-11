#include <map>
#include <iostream>

int main() {
  std::map<std::string, std::map<std::string, int64_t>> map;
  std::string name;
  std::string item;
  int64_t amount = 0;
  while (std::cin >> name) {
    std::cin >> item >> amount;
    auto it = map.find(name);
    if (it == map.end()) {
      std::map<std::string, int64_t> mp;
      mp.emplace(item, amount);
      map.emplace(name, std::move(mp));
    } else {
      auto elem = map[name].find(item);
      if (elem == map[name].end()) {
        map[name].emplace(item, amount);
      } else {
        map[name][item] += amount;
      }
    }
  }
  for (auto& it : map) {
    std::cout << it.first << ":\n";
    for (auto& elem : it.second) {
      std::cout << elem.first << ' ' << elem.second << '\n';
    }
  }
  return 0;
}