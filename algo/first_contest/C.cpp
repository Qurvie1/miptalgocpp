#include <iostream>

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void QuickSort(int* array, int left, int right) {
  if (right - left <= 1) {
    return;
  }
  int pivot = array[right - 1];
  int index = left;
  for (int i = left; i < right - 1; ++i) {
    if (array[i] < pivot) {
      Swap(array[i], array[index]);
      ++index;
    }
  }
  Swap(array[index], array[right - 1]);
  QuickSort(array, left, index);
  QuickSort(array, index + 1, right);
}

bool IsInMas(int* array, int len, int n) {
  int left = 0;
  int right = len - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (n < array[mid]) {
      right = mid - 1;
    } else if (n > array[mid]) {
      left = mid + 1;
    } else {
      return true;
    }
  }
  return false;
}

int main() {
  int n1 = 0;
  std::cin >> n1;
  auto a1 = new int[n1];
  int n2 = 0;
  bool eq = true;
  for (int i = 0; i < n1; ++i) {
    std::cin >> a1[i];
  }
  std::cin >> n2;
  auto a2 = new int[n2];
  for (int i = 0; i < n2; ++i) {
    std::cin >> a2[i];
  }
  QuickSort(a1, 0, n1);
  QuickSort(a2, 0, n2);
  for (int i = 0; i < n1; ++i) {
    if (!IsInMas(a2, n2, a1[i])) {
      eq = false;
      break;
    }
  }
  if (eq) {
    for (int i = 0; i < n2; ++i) {
      if (!IsInMas(a1, n1, a2[i])) {
        eq = false;
        break;
      }
    }
  }
  std::cout << (eq ? "YES\n" : "NO\n");
  delete[] a1;
  delete[] a2;
  return 0;
}