#include <iostream>

void PutOrRemove(int p, int q, int n, int** board, bool put) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      board[i][j] += (put ? 1 : -1) * (i == p || j == q || i + j == p + q || i - j == p - q);
    }
  }
}

void Solution(int i, int& counter, int n, int** board) {
  for (int k = 0; k < n; ++k) {
    if (board[k][i] == 0) {
      PutOrRemove(k, i, n, board, true);
      if (i == n - 1) {
        ++counter;
      } else {
        Solution(i + 1, counter, n, board);
      }
      PutOrRemove(k, i, n, board, false);
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  auto board = new int*[10]{};
  for (int i = 0; i < n; ++i) {
    board[i] = new int[n]{};
  }
  int counter = 0;
  Solution(0, counter, n, board);
  std::cout << counter << '\n';
  for (int i = 0; i < n; ++i) {
    delete[] board[i];
  }
  delete[] board;
  return 0;
}