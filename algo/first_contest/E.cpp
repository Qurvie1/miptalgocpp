#include <iostream>

bool IsOkay(int* abitu, int n, int k, int m, int value);

template <class T>
void QuickSortLomuto(T* begin, T* end) {
  int right = end - begin;
  int left = 0;
  if (right - left < 2) {
    return;
  }

  T pivot = begin[right - 1];

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
  QuickSortLomuto(begin, begin + index);
  QuickSortLomuto(begin + index + 1, end);
}

int BinarySearch(int* abitu, int n, int k, int m) {
  int right = abitu[n - 1] - abitu[0];
  int left = 0;
  int mid = 0;
  while (left < right) {
    mid = (right + left) / 2;
    (IsOkay(abitu, n, k, m, mid) ? right = mid : left = mid + 1);
  }
  return right;
}

bool IsOkay(int* abitu, int n, int k, int m, int value) {
  int i = 0;
  int counter = 0;
  while (i < n - k + 1) {
    if (abitu[i + k - 1] - abitu[i] <= value) {
      ++counter;
      i += k;
    } else {
      ++i;
    }
  }
  return counter >= m;
}

int main() {
  int n = 0;
  std::cin >> n;
  int m = 0;
  std::cin >> m;
  int k = 0;
  std::cin >> k;
  auto abitu = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> abitu[i];
  }
  QuickSortLomuto(abitu, abitu + n);
  std::cout << BinarySearch(abitu, n, k, m) << '\n';
  delete[] abitu;
  return 0;
}