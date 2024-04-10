#include <iostream>

int main() {
  int m = 0;
  int n = 0;
  std::cin >> m >> n;
  int64_t dp[15][50]{};
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i != n - 1) {
        dp[i + 1][j] += dp[i][j];
      }
      if (i != n - 1 && j != m - 1) {
        dp[i + 1][j + 1] += dp[i][j];
      }
      if (j != m - 1) {
        dp[i][j + 1] += dp[i][j];
      }
    }
  }
  std::cout << dp[n - 1][m - 1] << '\n';
  return 0;
}