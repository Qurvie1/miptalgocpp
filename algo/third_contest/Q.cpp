#include <iostream>

int Min(int a, int b) {
  return (a <= b ? a : b);
}

int MatrixMultiplication(int l, int r, int** dp, int* sides, int n) {
  if (dp[l][r] == -1) {
    if (l == r - 1) {
      dp[l][r] = 0;
    } else {
      dp[l][r] = 1000000000;
      for (int i = l + 1; i < r; ++i) {
        dp[l][r] =
            Min(dp[l][r], sides[l] * sides[i] * sides[(r < n ? r : n - 1)] + MatrixMultiplication(l, i, dp, sides, n) +
                              MatrixMultiplication(i, r, dp, sides, n));
      }
    }
  }
  return dp[l][r];
}

int main() {
  int n = 0;
  std::cin >> n;
  auto sides = new int[n]{};
  auto dp = new int* [n + 1] {};
  for (int i = 0; i < n + 1; ++i) {
    dp[i] = new int[n + 1]{};
  }
  for (int i = 0; i < n + 1; ++i) {
    for (int j = 0; j < n + 1; ++j) {
      dp[i][j] = -1;
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> sides[i];
  }
  std::cout << MatrixMultiplication(0, n - 1, dp, sides, n) << '\n';
  delete[] sides;
  for (int i = 0; i < n + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}