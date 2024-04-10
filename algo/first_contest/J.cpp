#include <iostream>
#include <cstring>

int main() {
  auto s = new char[100000];
  std::cin.getline(s, 100000);
  int p = strlen(s);
  auto new_s = new char[p - 1];
  int k = 0;
  int h = 0;
  for (int i = 0; i < p - 1; ++i) {
    if (i % 2 == 0) {
      new_s[k++] = s[i];
    } else {
      new_s[p - 2 - h] = s[i];
      h++;
    }
  }
  for (int i = 0; i < p - 1; ++i) {
    std::cout << new_s[i];
  }
  delete[] s;
  delete[] new_s;
  return 0;
}