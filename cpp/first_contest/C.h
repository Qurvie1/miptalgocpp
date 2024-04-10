#ifndef SORT_H
#define SORT_H

template <class T>
void Sort(T* begin, T* end) {
  int left = 0;
  int right = end - begin;
  if (right - left < 2) {
    return;
  }
  T* mid = begin + right / 2;
  int mid1 = right / 2;
  Sort(begin, mid);
  Sort(mid, end);
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

#endif