#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int array[10][21];
  for (int i = 0; i < 10; ++i) {
    array[i][1] = 1;
  }
  for (int i = 2; i < n + 1; ++i) {
    array[0][i] = array[6][i - 1] + array[4][i - 1];
    array[1][i] = array[6][i - 1] + array[8][i - 1];
    array[2][i] = array[7][i - 1] + array[9][i - 1];
    array[3][i] = array[4][i - 1] + array[8][i - 1];
    array[4][i] = array[3][i - 1] + array[9][i - 1] + array[0][i - 1];
    array[6][i] = array[1][i - 1] + array[7][i - 1] + array[0][i - 1];
    array[7][i] = array[2][i - 1] + array[6][i - 1];
    array[8][i] = array[1][i - 1] + array[3][i - 1];
    array[9][i] = array[4][i - 1] + array[2][i - 1];
  }
  int sum = 0;
  for (int i = 0; i < 10; ++i) {
    if (i != 0 && i != 8) {
      sum += array[i][n];
    }
  }
  std::cout << sum << '\n';
  return 0;
}