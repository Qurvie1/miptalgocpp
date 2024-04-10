#include <iostream>
#include <cstring>

void Plus1(char* s, int m, int& number, int& sum, int* amount) {
  int i = 0;
  while (i < m) {
    int t = s[m - 1 - i] - '0';
    if (t + 1 >= 3) {
      s[m - 1 - i] = '0';
      sum -= 2 * amount[m - 1 - i];
      ++i;
      number -= 2;
    } else {
      s[m - 1 - i] = (t + 1) + '0';
      sum += amount[m - 1 - i];
      ++number;
      break;
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  int m = 0;
  std::cin >> m;
  auto amount = new int[m];
  for (int i = 0; i < m; ++i) {
    std::cin >> amount[i];
  }
  int finish = 1;
  for (int i = 0; i < m; ++i) {
    finish *= 3;
  }
  int sum = 0;
  int number = 0;
  int temp_number = 31;
  auto temp_s = new char[100]{};
  auto s = new char[100]{};
  for (int i = 0; i < m; ++i) {
    s[i] = '0';
  }
  for (int i = 0; i < finish; ++i) {
    if (sum == n && number < temp_number) {
      temp_number = number;
      for (int i = 0; i < m; ++i) {
        temp_s[i] = s[i];
      }
    }
    Plus1(s, m, number, sum, amount);
  }
  if (temp_number == 31) {
    for (int i = 0; i < m; ++i) {
      sum += 2 * amount[i];
    }
    std::cout << (sum < n ? -1 : 0);
  } else {
    std::cout << temp_number << '\n';
    for (int i = 0; i < m; ++i) {
      int t = temp_s[i] - '0';
      for (int j = 0; j < t; ++j) {
        std::cout << amount[i] << ' ';
      }
    }
  }
  delete[] s;
  delete[] temp_s;
  delete[] amount;
  return 0;
}