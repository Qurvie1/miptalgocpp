#include <iostream>
#include <cstring>

int Max(int a, int b) {
  return (a <= b ? b : a);
}

int MaxPalyndrome(int left, int right, int** dp, char s[10001]) {
  if (left == right) {
    return 1;
  };
  if (right < left) {
    return 0;
  }
  if (dp[left][right] == 0 && left != right) {
    if (s[left] == s[right]) {
      dp[left][right] = MaxPalyndrome(left + 1, right - 1, dp, s) + 2;
    } else {
      dp[left][right] = Max(MaxPalyndrome(left + 1, right, dp, s), MaxPalyndrome(left, right - 1, dp, s));
    }
  }
  return dp[left][right];
}

int main() {
  char s[10001]{};
  std::cin >> s;
  int len = static_cast<int>(strlen(s));
  auto dp = new int* [len] {};
  for (int i = 0; i < len; ++i) {
    dp[i] = new int[len]{};
  }
  std::cout << (len == 2 && s[0] != s[1] ? 1 : len - MaxPalyndrome(0, len - 1, dp, s)) << '\n';
  for (int i = 0; i < len; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}