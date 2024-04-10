#include <iostream>

int Max(int a, int b) {
  return (a >= b ? a : b);
}

int Solution(int** arr, int n, int* answer, int** solution_arr) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (arr[i][j] != arr[j][i] || arr[i][i] != 0) {
        return 0;
      }
      solution_arr[i][j] = arr[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 2; j <= n; ++j) {
      if (solution_arr[i][j] > solution_arr[i][j - 1] && i != j && i != j - 1) {
        answer[j] = solution_arr[i][j];
      } else if (solution_arr[i][j] != answer[j] && answer[j] != 0 && solution_arr[i][j] != 0) {
        answer[i] = solution_arr[i][j];
      } else if (solution_arr[i][j] < solution_arr[i][j - 1] && i != j && i != j - 1) {
        answer[j - 1] = solution_arr[i][j - 1];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (answer[i] == 0) {
      int min_value = 1000;
      for (int j = 1; j <= n; ++j) {
        if (solution_arr[i][j] < min_value && i != j) {
          min_value = solution_arr[i][j];
        }
      }
      answer[i] = min_value;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (arr[i][j] != Max(answer[i], answer[j]) && i != j) {
        return 0;
      }
    }
  }
  if (answer[1] == 0) {
    return 0;
  }
  return 1;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto arr = new int*[n + 1]{};
  auto answer = new int[n + 1]{};
  for (int i = 1; i <= n; ++i) {
    arr[i] = new int[n + 1]{};
    for (int j = 1; j <= n; ++j) {
      std::cin >> arr[i][j];
    }
  }
  auto solution_arr = new int*[n + 1]{};
  for (int i = 1; i <= n; ++i) {
    solution_arr[i] = new int[n + 1]{};
  }
  bool flag = Solution(arr, n, answer, solution_arr);
  if (flag && n != 1) {
    for (int i = 1; i <= n; ++i) {
      std::cout << answer[i] << ' ';
    }
  } else if (n == 1) {
    std::cout << (arr[1][1] == 0 ? 1 : -1) << '\n';
  } else {
    std::cout << -1 << '\n';
  }
  for (int i = 1; i <= n; ++i) {
    delete[] arr[i];
    delete[] solution_arr[i];
  }
  delete[] solution_arr;
  delete[] answer;
  delete[] arr;
  return 0;
}