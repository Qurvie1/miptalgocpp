#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int x = 0;
  int y = 0;
  std::cin >> x >> y;
  int h = 0;
  int w = 0;
  std::cin >> h >> w;
  auto array = new int* [x] {};
  for (int i = 0; i < x; ++i) {
    array[i] = new int[y]{};
  }
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      std::cin >> array[i][j];
    }
  }
  int coord1 = -1;
  int coord2 = -1;
  int coord_max1 = 0;
  int coord_max2 = 0;
  int max = array[0][0];
  while (true) {
    if (coord1 == coord_max1 && coord2 == coord_max2) {
      break;
    }
    coord1 = coord_max1;
    coord2 = coord_max2;
    for (int i = coord1; i < (coord1 + h > x ? x : coord1 + h); ++i) {
      for (int j = coord2; j < (coord2 + w > y ? y : coord2 + w); ++j) {
        if (array[i][j] > max) {
          coord_max1 = i;
          coord_max2 = j;
          max = array[i][j];
        }
      }
    }
  }
  std::cout << coord1 << ' ' << coord2;
  for (int i = 0; i < x; ++i) {
    delete[] array[i];
  }
  delete[] array;
  return 0;
}