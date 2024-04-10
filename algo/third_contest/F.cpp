#include <iostream>
#include <algorithm>

int Min(int a, int b) {
  return (a <= b ? a : b);
}

int main() {
  int n = 0;
  std::cin >> n;
  auto cords = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> cords[i];
  }
  std::sort(cords, cords + n);
  auto dp = new int[n]{};
  dp[0] = 0;
  dp[1] = cords[1] - cords[0];
  if (n > 2) {
    dp[2] = cords[2] - cords[1] + dp[1];
  }
  for (int i = 3; i < n; ++i) {
    dp[i] = Min(cords[i] - cords[i - 1] + dp[i - 1], cords[i] - cords[i - 1] + dp[i - 2]);
  }
  std::cout << dp[n - 1] << '\n';
  delete[] dp;
  delete[] cords;
  return 0;
}