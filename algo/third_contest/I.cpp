#include <iostream>
#include <cstddef>
#include <cstring>

size_t Min(size_t a, size_t b, size_t c) {
  return (a <= b ? (c <= a ? c : a) : (b <= c ? b : c));
}

int main() {
  char s1[5001]{};
  char s2[5001]{};
  std::cin >> s1;
  std::cin >> s2;
  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);
  auto dp = new size_t* [len1 + 1] {};
  for (size_t i = 0; i < len1 + 1; ++i) {
    dp[i] = new size_t[len2 + 1]{};
  }
  for (size_t i = 0; i < len2 + 1; ++i) {
    dp[0][i] = i;
  }
  for (size_t i = 0; i < len1 + 1; ++i) {
    dp[i][0] = i;
  }
  for (size_t i = 1; i < len1 + 1; ++i) {
    for (size_t j = 1; j < len2 + 1; ++j) {
      dp[i][j] =
          Min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, (s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] : dp[i - 1][j - 1] + 1));
    }
  }
  std::cout << dp[len1][len2] << '\n';
  for (size_t i = 0; i < len1 + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}