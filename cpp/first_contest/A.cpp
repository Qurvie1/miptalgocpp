#include <iostream>

bool IsVerticalHorizontal(char** a, int n, int k, bool is_vertical) {
  for (int i = 0; i < n; ++i) {
    if ((is_vertical ? a[i][k] : a[k][i]) == '0') {
      return false;
    }
  }
  return true;
}

void Solution(char** array, int& c_1, int& c_2, int& distance_i, int& distance_j, int n, int m) {
  int temp_i = -1;
  int temp_j = -1;
  for (int i = 0; i < n; ++i) {
    if (IsVerticalHorizontal(array, m, i, false)) {
      ++c_1;
      if (temp_i != -1) {
        distance_i = i - temp_i - 1;
        break;
      }
      temp_i = i;
    }
  }
  for (int j = 0; j < m; ++j) {
    if (IsVerticalHorizontal(array, n, j, true)) {
      ++c_2;
      if (temp_j != -1) {
        distance_j = j - temp_j - 1;
        break;
      }
      temp_j = j;
    }
  }
}

int main() {
  int m = 0;
  int n = 0;
  int distance_i = 0;
  int distance_j = 0;
  int c_1 = 0;
  int c_2 = 0;
  std::cin >> n >> m;
  auto array = new char*[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new char[m];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> array[i][j];
    }
  }
  Solution(array, c_1, c_2, distance_i, distance_j, n, m);
  if (c_1 >= 2 && c_2 == 0 && distance_i != m) {
    std::cout << "Line\n";
  } else if (c_2 >= 2 && c_1 == 0 && distance_j != n) {
    std::cout << "Vertical line\n";
  } else if (c_1 >= 1 && c_2 >= 1 && m != 1 && n != 1) {
    std::cout << "Square\n";
  } else {
    std::cout << "?\n";
  }
  for (int i = 0; i < n; ++i) {
    delete[] array[i];
  }
  delete[] array;
  return 0;
}