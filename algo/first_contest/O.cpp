#include <iostream>
#include <cmath>

bool IsOkay(int64_t size, int64_t w, int64_t h, int64_t n) {
  return ((size / w) * (size / h) >= n);
}

template <class T>
int Max(T& a, T& b) {
  return (a >= b ? a : b);
}

int64_t BinarySearch(int64_t w, int64_t h, int64_t n) {
  int64_t left = Max(w, h) - 1;
  int64_t right = Max(w, h) * (static_cast<int64_t>(sqrt(n)) + 1) + 1;
  int64_t mid = 0;
  while (right - left > 1) {
    mid = (left + right) / 2;
    if (IsOkay(mid, w, h, n) && IsOkay(mid - 1, w, h, n)) {
      right = mid;
    } else if (!IsOkay(mid, w, h, n)) {
      left = mid;
    } else if (IsOkay(mid, w, h, n) && !IsOkay(mid - 1, w, h, n)) {
      return mid;
    }
  }
  return static_cast<int64_t>((ceil(sqrt(n)))) * n;
}

int main() {
  int64_t w = 0;
  int64_t h = 0;
  int64_t n = 0;
  std::cin >> w >> h >> n;
  std::cout << BinarySearch(w, h, n);
  return 0;
}