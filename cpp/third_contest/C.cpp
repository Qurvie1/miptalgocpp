#include <iostream>

struct Group {
  int solved;
  int time;
  int index;
  bool operator<(const Group& other) const {
    if (solved > other.solved) {
      return true;
    }
    if (solved < other.solved) {
      return false;
    }
    if (solved == other.solved) {
      if (time < other.time) {
        return true;
      }
      if (time > other.time) {
        return false;
      }
    }
    return index < other.index;
  }
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
  std::cin >> n;
  auto groups = new Group[n]{};
  for (int i = 0; i < n; ++i) {
    int tasks = 0;
    int addtime = 0;
    int index = i + 1;
    std::cin >> tasks >> addtime;
    Group group{tasks, addtime, index};
    groups[i] = group;
  }
  MergeSort(groups, groups + n);
  for (int i = 0; i < n; ++i) {
    std::cout << groups[i].index << '\n';
  }
  delete[] groups;
  return 0;
}