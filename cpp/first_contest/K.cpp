#include <iostream>

int main() {
  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  std::cin >> n >> m >> k;
  auto colors = new int64_t[k]{};
  for (int i = 0; i < k; ++i) {
    colors[i] = (n / k) * (m / k) * k + (n / k) * (m % k) + (m / k) * (n % k);
  }
  int ost1 = n % k;
  int ost2 = m % k;
  int counter = 1;
  int i = 0;
  int j = (ost1 >= ost2 ? ost1 - ost2 : ost2 - ost1);
  while (counter < ost1 && counter < ost2 && ost1 > 0 && ost2 > 0) {
    colors[i % k] += counter;
    ++counter;
    ++i;
  }
  while (j && ost1 > 0 && ost2 > 0) {
    colors[i % k] += counter;
    ++i;
    --j;
  }
  while (counter && ost1 > 0 && ost2 > 0) {
    colors[i % k] += counter;
    --counter;
    ++i;
  }
  for (int i = 0; i < k; ++i) {
    std::cout << colors[i] << ' ';
  }
  delete[] colors;
  return 0;
}