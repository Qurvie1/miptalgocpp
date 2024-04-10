#include <iostream>

struct Faculty {
  int fac = 0;
  int value = 0;
};

int BinarySearch(Faculty* array, int size, int value) {
  int left = 0;
  int right = size - 1;
  while (left <= right) {
    int mid = (left - right) / 2 + right;
    if (array[mid].fac < value) {
      left = mid + 1;
    } else if (array[mid].fac > value) {
      right = mid - 1;
    } else {
      return array[mid].value;
    }
  }
  return 0;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new Faculty[n]{};
  int p = 0;
  int c = 1;
  int temp = 0;
  if (n > 0) {
    std::cin >> temp;
  }
  int a = 0;
  for (int i = 1; i < n; ++i) {
    std::cin >> a;
    if (a != temp) {
      Faculty t{temp, c};
      array[p++] = t;
      c = 0;
    }
    ++c;
    temp = a;
  }
  if (n > 0) {
    Faculty t{temp, c};
    array[p++] = t;
  }
  int m = 0;
  std::cin >> m;
  int number = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> number;
    std::cout << BinarySearch(array, p, number) << '\n';
  }
  delete[] array;
  return 0;
}