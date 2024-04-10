#include <iostream>

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  if (n > m) {
    std::swap(n, m);
  }
  int d[100][100]{};
  int64_t a[100][100]{};
  int temp1[30]{};
  int temp2[30]{};
  for (int i = 0; i < (1 << n); ++i) {
    for (int j = 0; j < (1 << n); ++j) {
      int num1 = i;
      int num2 = j;
      for (int i = 0; i < n; ++i) {
        temp1[i] = 0;
        temp2[i] = 0;
      }
      int c1 = 0;
      int c2 = 0;
      while (num1) {
        temp1[c1++] = num1 % 2;
        num1 /= 2;
      }
      while (num2) {
        temp2[c2++] = num2 % 2;
        num2 /= 2;
      }
      d[i][j] = 1;
      for (int k = 0; k < n - 1; ++k) {
        if (temp1[k] == temp1[k + 1] && temp1[k + 1] == temp2[k] && temp1[k + 1] == temp2[k + 1]) {
          d[i][j] = 0;
          break;
        }
      }
    }
  }
  for (int i = 0; i < (1 << n); ++i) {
    a[0][i] = 1;
  }
  for (int k = 0; k < m; ++k) {
    for (int i = 0; i < (1 << n); ++i) {
      for (int j = 0; j < (1 << n); ++j) {
        a[k][i] += a[k - 1][j] * d[j][i];
      }
    }
  }
  int64_t answer = 0;
  for (int i = 0; i < (1 << n); ++i) {
    answer += a[m - 1][i];
  }
  std::cout << answer;
  return 0;
}