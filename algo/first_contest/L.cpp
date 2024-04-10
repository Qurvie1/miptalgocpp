#include <iostream>

void Merge(int* a1, int n1, int* a2, int n2) {
  int i = 0;
  int j = 0;
  int k = 0;

  auto temp = new int[n1 + n2];

  while (i < n1 && j < n2) {
    temp[k++] = (a1[i] < a2[j] ? a1[i++] : a2[j++]);
  }

  while (i < n1) {
    temp[k++] = a1[i++];
  }
  while (j < n2) {
    temp[k++] = a2[j++];
  }
  for (k = 0; k < n1 + n2; ++k) {
    a1[k] = temp[k];
  }
  delete[] temp;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int k = 0;
  std::cin >> k;
  int counter = k;
  int p = 1;
  auto sizes = new int[k]{};
  auto mass = new int* [k] {};
  for (int i = 0; i < k; ++i) {
    std::cin >> sizes[i];
    mass[i] = new int[1000000];
    for (int j = 0; j < sizes[i]; ++j) {
      std::cin >> mass[i][j];
    }
  }
  while (counter > 1) {
    for (int i = 0; i < k; i += 2 * p) {
      if (k - i > p) {
        Merge(mass[i], sizes[i], mass[i + p], sizes[i + p]);
        sizes[i] += sizes[i + p];
      }
    }
    counter = (counter + 1) / 2;
    p *= 2;
  }
  for (int i = 0; i < sizes[0]; ++i) {
    std::cout << mass[0][i] << ' ';
  }
  for (int i = 0; i < k; ++i) {
    delete[] mass[i];
  }
  delete[] mass;
  delete[] sizes;
  return 0;
}