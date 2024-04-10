#include <iostream>
#include <cstddef>

void MergeSort(int* array, size_t left, size_t right, int64_t& inv) {
  if (right - left <= 1) {  // останавливаем разбиение, если уже спустились к массивам единичной длины
    return;
  }
  size_t mid = (left + right) / 2;  // делим массив пополам, чтоб сортировать меньшие куски.
  MergeSort(array, left, mid, inv);
  MergeSort(array, mid, right, inv);
  auto temp = new int[right - left];
  size_t i = left;                // указатель первого массива
  size_t j = mid;                 // указатель второго массива
  size_t k = 0;                   // суммарный номер в получившеся массиве
  while (i < mid && j < right) {  // засовываем из двух массивов в новый
    if (array[i] <= array[j]) {
      temp[k++] = array[i++];
    } else {
      temp[k++] = array[j++];
      inv += (mid - i);  // прибавляем разницу между концом массива меньших номеров и номером i
    }  // идейный смысл: в случае если меньше элемент a[j], то он образует инверсную пару с каждым
  }    // с каждым, кто находится после a[i] включительно
  while (i < mid) {  // массив не полностью заполнен, то дозаполняем
    temp[k++] = array[i++];
  }
  while (j < right) {
    temp[k++] = array[j++];
  }
  for (size_t k = left; k < right; ++k) {  // заполняем из нового массива
    array[k] = temp[k - left];
  }
  delete[] temp;
}

int main() {
  int n = 0;
  int64_t inv = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, n, inv);
  std::cout << inv;
  delete[] array;
  return 0;
}