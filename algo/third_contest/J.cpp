#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int64_t[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  auto dp = new int64_t[n]{};
  dp[0] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (array[j] < array[i]) {
        dp[i] = (dp[i] + (dp[j] % 1000000)) % 1000000;
      }
    }
    ++dp[i];
  }
  int64_t sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += dp[i];
  }
  std::cout << sum % 1000000 << '\n';
  delete[] array;
  delete[] dp;
  return 0;
}