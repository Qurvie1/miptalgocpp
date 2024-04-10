#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int64_t answer = 0;
  for (int i = 0; i < n; ++i) {
    int h = 0;
    int w = 0;
    std::cin >> h >> w;
    answer += (w < h ? h : w);
  }
  std::cout << answer;
  return 0;
}