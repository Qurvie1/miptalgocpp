#ifndef HEAP_H
#define HEAP_H

template <class T>
void Swap(T& a, T& b) {
  T temp = b;
  b = a;
  a = temp;
}

template <class T>
void PushHeap(T* begin, T* end) {
  int i = end - begin - 1;
  int parent = (i - 1) / 2;
  while (true) {
    if (parent < 0 || i < 1) {
      break;
    }
    if (begin[parent] < begin[i]) {
      Swap(begin[i], begin[parent]);
    }
    i = parent;
    parent = (i - 1) / 2;
  }
}

template <class T>
void PopHeap(T* begin, T* end) {
  int size = end - begin;
  Swap(begin[0], begin[size - 1]);
  --size;
  int i = 0;
  int left = 0;
  int right = 0;
  int big = 0;
  while (true) {
    left = 2 * i + 1;
    right = left + 1;
    big = i;
    big = (left < size && begin[big] < begin[left] ? left : big);
    big = (right < size && begin[big] < begin[right] ? right : big);
    if (big == i) {
      break;
    }
    Swap(begin[big], begin[i]);
    i = big;
  }
}

#endif