#ifndef KTH_H
#define KTH_H

template <class T>
void Swap(T& a, T& b) {
  T temp = b;
  b = a;
  a = temp;
}

template <class T>
void KthElement(T* begin, T* kth, T* end) {
  int left = 0;
  int right = end - begin;
  int k = kth - begin;
  while (true) {
    int index = left;
    for (int i = left; i < right - 1; ++i) {
      if (begin[i] < begin[right - 1]) {
        Swap(begin[i], begin[index]);
        ++index;
      }
    }
    Swap(begin[index], begin[right - 1]);
    if (k < index + 1 && index < k + 1) {
      return;
    } else if (k < index) {
      right = index;
    } else {
      left = index + 1;
    }
  }
}

#endif