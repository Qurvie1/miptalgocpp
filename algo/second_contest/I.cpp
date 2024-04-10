#include <iostream>

struct Pair {
  int64_t key;
  int value;
};

template <class T>
void MergeSort(T* begin, T* end) {
  int left = 0;
  int right = end - begin;
  if (right - left < 2) {
    return;
  }
  T* mid = begin + right / 2;
  int mid1 = right / 2;
  MergeSort(begin, mid);
  MergeSort(mid, end);
  T* temp = new T[right - left];
  int i = left;
  int j = right / 2;
  int k = 0;
  while (i < mid1 && j < right) {
    temp[k++] = (begin[i] < begin[j] ? begin[i++] : begin[j++]);
  }
  while (i < mid1) {
    temp[k++] = begin[i++];
  }
  while (j < right) {
    temp[k++] = begin[j++];
  }
  for (int k = left; k < right; ++k) {
    begin[k] = temp[k - left];
  }
  delete[] temp;
}

int main() {
  int n = 0;
  int64_t k = 0;
  int64_t answer = 0;
  std::cin >> n >> k;
  auto cards = new int[n]{};
  auto dublicates = new Pair[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> cards[i];
  }
  int counter = 1;
  int p = 0;
  MergeSort(cards, cards + n);
  for (int i = 1; i < n; ++i) {
    if (cards[i] != cards[i - 1]) {
      Pair pair{cards[i - 1], counter};
      dublicates[p++] = pair;
      counter = 0;
    }
    ++counter;
    if (i == n - 1) {
      Pair pair{cards[i], counter};
      dublicates[p++] = pair;
      counter = 0;
    }
  }
  int i = 0;
  int j = 0;
  int64_t size = 0;
  int64_t size2 = 0;
  while (i < p) {
    while (j < p && k * dublicates[i].key >= dublicates[j].key) {
      answer = answer + size * (size - 1) * 3 + 3 * size2;
      if (dublicates[j].value >= 2) {
        answer += 3 * size;
        ++size2;
      }
      ++size;
      ++j;
    }
    i++;
    --size;
    if (dublicates[i - 1].value >= 2) {
      size2--;
    }
  }
  for (int i = 0; i < p; ++i) {
    if (dublicates[i].value >= 3) {
      ++answer;
    }
  }
  std::cout << answer << '\n';
  delete[] dublicates;
  delete[] cards;
  return 0;
}