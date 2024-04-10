#include <iostream>

template <class T>
void QuickSort(T* begin, T* end) {
  int right = end - begin;
  int left = 0;
  if (right - left <= 1) {
    return;
  }

  int pivot = begin[right - 1];

  int index = 0;
  for (int i = 0; i < right - 1; ++i) {
    if (begin[i] < pivot) {
      T temp = begin[i];
      begin[i] = begin[index];
      begin[index] = temp;
      ++index;
    }
  }
  T temp = begin[right - 1];
  begin[right - 1] = begin[index];
  begin[index] = temp;
  QuickSort(begin, begin + index);
  QuickSort(begin + index + 1, end);
}

int main() {
  int n = 0;
  std::cin >> n;
  auto sides = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> sides[i];
  }
  QuickSort(sides, sides + n);
  int i = 0;
  int j = 0;
  int sum = 0;
  int max_sum = sides[0];
  int counter = 1;
  while (i < n - 1) {
    while (j < n) {
      if (sides[j] <= sides[i] + sides[i + 1]) {
        sum += sides[j];
        ++j;
      } else {
        break;
      }
    }
    if (max_sum < sum) {
      max_sum = sum;
      counter = j - i + 1 - 1 * (j == n);
    }
    sum -= sides[i];
    ++i;
  }
  std::cout << counter << ' ' << max_sum;
  delete[] sides;
  return 0;
}