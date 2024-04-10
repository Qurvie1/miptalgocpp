#include <iostream>
#include <cstring>

void DecBin(char* n, char* s, int& start) {
  int p = strlen(n);
  int number = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  if (p == 1 && n[0] == '1') {
    s[start] = n[0];
    ++start;
    return;
  }
  auto new_s = new char[1000000]{};
  auto temp = new char[10000000]{};
  while (true) {
    while (i < p) {
      number = 10 * number + (n[i] - '0');
      if (number > 1) {
        temp[j++] = '0' + (number / 2);
        number %= 2;
      } else if (number <= 1 && i > 0) {
        temp[j++] = '0' + (number / 2);
      }
      ++i;
    }
    p = j;
    for (int q = 0; q < p; ++q) {
      n[q] = temp[q];
      temp[q] = 0;
    }
    new_s[k++] = number + '0';
    number = 0;
    i = 0;
    j = 0;
    if (p <= 1 && n[0] == '1') {
      new_s[k++] = '1';
      break;
    }
  }
  for (int j = 0; j < k / 2; ++j) {
    std::swap(new_s[j], new_s[k - 1 - j]);
  }
  for (int i = 0; i < k; ++i) {
    s[start + i] = new_s[i];
  }
  start += k;
  delete[] temp;
  delete[] new_s;
}

int main() {
  auto s = new char[256]{};
  std::cin.getline(s, 256);
  auto new_s = new char[10000000]{};
  int p = strlen(s);
  int i = 0;
  int j = 0;
  int k = 0;
  auto number = new char[256]{};
  while (i < p) {
    if (isdigit(s[i])) {
      number[k++] = s[i++];
    } else {
      if (number[0]) {
        DecBin(number, new_s, j);
        for (int t = 0; t < k; ++t) {
          number[t] = 0;
        }
        k = 0;
      }
      new_s[j++] = s[i++];
    }
  }
  if (number[0]) {
    DecBin(number, new_s, j);
  }
  int q = strlen(new_s);
  for (int i = 0; i < q; ++i) {
    std::cout << new_s[i];
  }
  delete[] s;
  delete[] new_s;
  delete[] number;
  return 0;
}