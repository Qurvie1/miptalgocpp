#include <unordered_map>
#include <iostream>

int main() {
  std::unordered_map<std::string, int> bank;
  int operation = 0;
  std::string name;
  int money = 0;
  size_t n = 0;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> operation;
    std::cin >> name;
    auto it = bank.find(name);
    if (operation == 1) {
      std::cin >> money;
      if (it == bank.end()) {
        bank.emplace(name, money);
      } else {
        it->second += money;
      }
    } else if (operation == 2) {
      if (it == bank.end()) {
        std::cout << "ERROR" << '\n';
      } else {
        std::cout << it->second << '\n';
      }
    }
  }
  return 0;
}