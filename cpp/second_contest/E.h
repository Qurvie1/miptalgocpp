#ifndef HEAPSORT_H
#define HEAPSORT_H

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
void SiftDown (T* begin, int size, int index) {
  int left = 0;
  int right = 0;
  int biggest = 0;
  while (true) {
    left = 2 * index + 1;
    right = left + 1;
    biggest = index;
    biggest = (left < size && begin[biggest] < begin[left] ? left : biggest);
    biggest = (right < size && begin[biggest] < begin[right] ? right : biggest);
    if (biggest == index) {
      break;
    }
    Swap(begin[biggest], begin[index]);
    index = biggest;
  }
}

template <class T>
void MakeHeap(T* begin, T* end) {
  int size = end - begin;
  for (int i = size / 2 - 1; i >= 0; --i) {
    SiftDown(begin, size, i);
  }
}

template <class T>
void SortHeap(T* begin, T* end) {
  int size = end - begin;
  for (int i = size - 1; i >= 0; --i) {
    Swap(begin[i], begin[0]);
    SiftDown(begin, i, 0);
  }
}

#endif