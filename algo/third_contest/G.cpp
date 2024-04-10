#include <cstddef>
#include <iostream>

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
void LongestCommonSubsequence(const T* first_array, size_t first_size, const T* second_array, size_t second_size,
                              Array<T>& arr) {
  auto lsp_size = new size_t*[first_size + 1];
  for (size_t i = 0; i <= first_size; ++i) {
    lsp_size[i] = new size_t[second_size + 1];
    lsp_size[i][0] = 0;
  }
  for (size_t j = 0; j <= second_size; ++j) {
    lsp_size[0][j] = 0;
  }
  for (size_t i = 1; i <= first_size; ++i) {
    for (size_t j = 1; j <= second_size; ++j) {
      if (first_array[i - 1] == second_array[j - 1]) {
        lsp_size[i][j] = lsp_size[i - 1][j - 1] + 1;
      } else {
        lsp_size[i][j] = std::max(lsp_size[i][j - 1], lsp_size[i - 1][j]);
      }
    }
  }
  auto answer = new T[lsp_size[first_size][second_size]];
  auto i = first_size;
  auto j = second_size;
  auto k = lsp_size[first_size][second_size];

  while (k) {
    if (first_array[i - 1] == second_array[j - 1]) {
      answer[--k] = first_array[i - 1];
      --i;
      --j;
    } else if (lsp_size[i][j] == lsp_size[i - 1][j]) {
      --i;
    } else {
      --j;
    }
  }
  size_t answer_size = lsp_size[first_size][second_size];

  for (size_t i = 0; i <= first_size; ++i) {
    delete[] lsp_size[i];
  }
  delete[] lsp_size;
  arr.arr_ = answer;
  arr.size_ = answer_size;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n;
  auto first = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> first[i];
  }
  std::cin >> m;
  auto second = new int[m]{};
  for (int i = 0; i < m; ++i) {
    std::cin >> second[i];
  }
  Array<int> arr;
  LongestCommonSubsequence(first, n, second, m, arr);
  for (size_t i = 0; i < arr.size_; ++i) {
    std::cout << arr[i] << ' ';
  }
  delete[] first;
  delete[] second;
  return 0;
}