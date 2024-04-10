#ifndef ARRAY_H
#define ARRAY_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <cstddef>

template <class T, size_t N>
class Array {
 public:

  T arr[N];

  const T& operator[](size_t index) const {
    return arr[index];
  }

  T& operator[](size_t index) {
    return arr[index];
  }

  const T& Front() const {
    return arr[0];
  }

  T& Front() {
    return arr[0];
  }

  const T& Back() const {
    return arr[N - 1];
  }

  T& Back() {
    return arr[N - 1];
  }

  const T* Data() const {
    return arr;
  }

  T* Data() {
    return arr;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T temp = arr[i];
      arr[i] = other[i];
      other[i] = temp;
    }
  }
};

template <class T>
size_t GetSize(T) {
  return 0;
}

template <class T, size_t N>
size_t GetSize(T (&)[N]) {
  return N;
}

template <class T>
size_t GetRank(T) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(T (&a)[N]) {
  return 1 + GetRank(*a);
}

template <class T>
size_t GetNumElements(T) {
  return 1;
}

template <class T, size_t N>
size_t GetNumElements(T (&a)[N]) {
  return N * GetNumElements(*a);
}

#endif