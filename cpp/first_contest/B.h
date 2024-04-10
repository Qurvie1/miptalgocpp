#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  int left = 0;
  int right = end - begin - 1;
  bool answer = false;
  while (left <= right) {
    int mid = (left - right) / 2 + right;
    if (begin[mid] < value) {
      left = mid + 1;
    } else if (value < begin[mid]) {
      right = mid - 1;
    } else {
      answer = true;
      break;
    }
  }
  return answer;
}

#endif

#ifndef LOWERBOUND_H
#define LOWERBOUND_H

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  int left = 0;
  int right = end - begin - 1;
  int answer = end - begin;
  bool flag = true;
  while (left <= right) {
    int mid = (left - right) / 2 + right;
    if (begin[mid] < value) {
      left = mid + 1;
    } else {
      if (flag) {
        answer = right;
        flag = false;
      }
      if (begin[mid] < begin[answer]) {
        answer = mid;
      }
      right = mid - 1;
    }
  }
  const T* answer_ptr = begin + answer;
  return answer_ptr;
}

#endif

#ifndef UPPERBOUND_H
#define UPPERBOUND_H

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  int left = 0;
  int right = end - begin - 1;
  int answer = end - begin;
  bool flag = true;
  while (left <= right) {
    int mid = (left - right) / 2 + right;
    if (!(value < begin[mid])) {
      left = mid + 1;
    } else {
      if (flag) {
        answer = right;
        flag = false;
      }
      if (value < begin[mid] && begin[mid] < begin[answer]) {
        answer = mid;
      }
      right = mid - 1;
    }
  }
  const T* answer_ptr = begin + answer;
  return answer_ptr;
}

#endif