#include <cstddef>
#include <iostream>

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n;
  auto first = new int[n + 1]{};
  for (int i = 1; i <= n; ++i) {
    std::cin >> first[i];
  }
  std::cin >> m;
  auto second = new int[m + 1]{};
  for (int i = 1; i <= m; ++i) {
    std::cin >> second[i];
  }
  auto dp = new int* [n + 1] {};
  for (int i = 0; i < n + 1; ++i) {
    dp[i] = new int[m + 1]{};
  }
  for (int i = 1; i < n + 1; ++i) {
    int best = 0;
    for (int j = 1; j < m + 1; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (first[i] == second[j] && dp[i - 1][j] < best + 1) {
        dp[i][j] = best + 1;
      }
      if (first[i] > second[j] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
      }
    }
  }
  int ind1 = 0;
  int max = 0;
  int ind2 = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (dp[ind1][ind2] < dp[i][j]) {
        ind1 = i;
        ind2 = j;
        max = dp[i][j];
      }
    }
  }
  auto answer = new int[501]{};
  int p = 0;
  int len = max;
  int prev_j = 501;
  int pos1 = 0;
  int pos1prev = 501;
  for (int i = ind1; i >= 1; --i) {
    for (int j = ind2; j >= 1; --j) {
      for (int k = i; k >= 1; --k) {
        if (first[k] == second[j]) {
          pos1 = k;
          break;
        }
      }
      if (dp[i][j] == len && len > 0 && (p >= 1 ? second[j] < answer[p - 1] : true) && j < prev_j && pos1 < pos1prev) {
        answer[p++] = second[j];
        --len;
        pos1prev = pos1;
        prev_j = j;
      }
    }
  }
  std::cout << max << '\n';
  for (int k = p - 1; k >= 0; --k) {
    std::cout << answer[k] << ' ';
  }
  for (int i = 0; i < n + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] answer;
  delete[] first;
  delete[] second;
  return 0;
}