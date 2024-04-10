#include <iostream>
#include <cstddef>

template <class T>
class Array {
 public:
  Array() = default;
  ~Array() {
    delete[] arr_;
  }
  int operator[](size_t index) {
    return arr_[index];
  }
  size_t Size() const {
    return size_;
  }
  T* arr_ = nullptr;
  size_t size_ = 0;
};

template <class T>
void LongestIncreasingSubsequence(const T* array, size_t size, Array<T>& array1) {
  if (size == 0) {
    array1.arr_ = nullptr;
    array1.size_ = 0;
    return;
  }
  T m_inf = *array;
  T inf = *array;
  for (size_t i = 1; i < size; ++i) {
    m_inf = std::min(m_inf, array[i]);
    inf = std::max(inf, array[i]);
  }
  m_inf -= 1000;
  inf += 1000;

  auto last_elem = new T[size + 1]{m_inf};
  for (size_t i = 1; i <= size; ++i) {
    last_elem[i] = inf;
  }
  auto index_curr = new size_t[size + 1];
  auto index_prev = new size_t[size + 1];

  for (size_t i = 0; i < size; ++i) {
    size_t left = 1;
    size_t right = i + 1;
    while (left < right) {
      size_t mid = (left + right) >> 1;
      if (last_elem[mid] >= array[i]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    if (last_elem[left] > array[i]) {
      last_elem[left] = array[i];
      index_curr[left] = i;
      index_prev[i] = index_curr[left - 1];
    }
  }

  size_t left = 1;
  size_t right = size + 1;
  while (left < right) {
    size_t mid = (left + right) >> 1;
    if (last_elem[mid] >= inf) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  auto lis = new T[left - 1];
  auto curr = index_curr[left - 1];
  lis[left - 2] = array[curr];
  for (size_t i = left - 2; i; --i) {
    curr = index_prev[curr];
    lis[i - 1] = array[curr];
  }

  delete[] index_curr;
  delete[] index_prev;
  delete[] last_elem;
  array1.arr_ = lis;
  array1.size_ = left - 1;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  Array<int> answer;
  LongestIncreasingSubsequence(array, n, answer);
  for (size_t i = 0; i < answer.Size(); ++i) {
    std::cout << answer[i] << ' ';
  }
  delete[] array;
  return 0;
}