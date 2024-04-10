#include <iostream>

void FateofCell(int** arr, int** fate, int x, int y) {
  int live = 0;
  for (int i = -1; i < 2; ++i) {
    for (int j = -1; j < 2; ++j) {
      live += (arr[x + i][y + j] == 1 ? 1 : 0);
    }
  }
  live -= arr[x][y];
  fate[x][y] = (live <= 1 ? 0 : (live >= 4 ? 0 : (live == 3 && arr[x][y] == 0 ? 1 : arr[x][y])));
}

int main() {
  int n = 0;
  int t = 0;
  std::cin >> n >> t;
  auto arr = new int*[n + 2]{};
  for (int i = 0; i < n + 2; ++i) {
    arr[i] = new int[n + 2]{};
  }
  auto fate = new int*[n + 2]{};
  for (int i = 0; i < n + 2; ++i) {
    fate[i] = new int[n + 2]{};
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < n + 1; ++j) {
      std::cin >> arr[i][j];
    }
  }
  while (t--) {
    for (int i = 1; i < n + 1; ++i) {
      for (int j = 1; j < n + 1; ++j) {
        FateofCell(arr, fate, i, j);
      }
    }
    for (int i = 1; i < n + 1; ++i) {
      for (int j = 1; j < n + 1; ++j) {
        arr[i][j] = fate[i][j];
      }
    }
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < n + 1; ++j) {
      std::cout << arr[i][j] << ' ';
    }
    std::cout << '\n';
  }
  for (int i = 0; i < n + 2; ++i) {
    delete[] arr[i];
    delete[] fate[i];
  }
  delete[] arr;
  delete[] fate;
  return 0;
}