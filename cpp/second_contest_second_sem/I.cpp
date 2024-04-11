#include <algorithm>
#include <iostream>
#include <queue>

int main() {
  std::priority_queue<int, std::vector<int>, std::greater<int>> mins;
  double cost = 0;
  int n = 0;
  std::cin >> n;
  int number = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> number;
    mins.push(number);
  }
  while (mins.size() > 1) {
    number = mins.top();
    mins.pop();
    cost += 0.05 * (mins.top() + number);
    mins.push(mins.top() + number);
    mins.pop();
  }
  std::cout << cost << '\n';
  return 0;
}