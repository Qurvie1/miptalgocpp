#include <iostream>

struct Pair {
  int start;
  int finish;
};

bool IsOkay(Pair car, int* lenght, int* commitment, int n, int e, int* borders) {
  double sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += static_cast<double>(lenght[i]) / (commitment[i] + borders[e]);
  }
  return sum > car.finish - car.start;
}

int BinarySearch(Pair car, int* lenght, int* commitment, int n, int m, int* borders) {
  int right = m + 1;
  int left = -1;
  while (right - left > 1) {
    int mid = (left + right) / 2;
    (IsOkay(car, lenght, commitment, n, mid, borders) ? left = mid : right = mid);
  }
  return right;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  auto commitment = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> commitment[i];
  }
  auto lenght = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> lenght[i];
  }
  int m = 0;
  std::cin >> m;
  --m;
  auto borders = new int[m + 1]{};
  for (int i = 1; i <= m; ++i) {
    std::cin >> borders[i];
  }
  auto taxes = new int[m + 2]{};
  for (int i = 1; i <= m + 1; ++i) {
    std::cin >> taxes[i];
  }
  int q = 0;
  std::cin >> q;
  auto cars = new Pair[q]{};
  for (int i = 0; i < q; ++i) {
    Pair car;
    std::cin >> car.start >> car.finish;
    cars[i] = car;
  }
  for (int i = 0; i < q; ++i) {
    int index = BinarySearch(cars[i], lenght, commitment, n, m, borders);
    std::cout << taxes[index] << '\n';
  }
  delete[] commitment;
  delete[] lenght;
  delete[] borders;
  delete[] taxes;
  delete[] cars;
  return 0;
}