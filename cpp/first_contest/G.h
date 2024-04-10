#ifndef MERGE_H
#define MERGE_H

template <class T, class U, class K>
void Merge(const T* start1, T* end1, const U* start2, U* end2, K* out) {
  int i = 0;
  int j = 0;
  int k = 0;
  int size1 = end1 - start1;
  int size2 = end2 - start2;
  K* temp = new K[size1 + size2];
  while (i < size1 && j < size2) {
    if (static_cast<K>(start1[i]) < static_cast<K>(start2[j])) {
      temp[k++] = static_cast<K>(start1[i++]);
    } else {
      temp[k++] = static_cast<K>(start2[j++]);
    }
  }
  while (i < size1) {
    temp[k++] = static_cast<K>(start1[i++]);
  }
  while (j < size2) {
    temp[k++] = static_cast<K>(start2[j++]);
  }
  for (int i = 0; i < size1 + size2; ++i) {
    out[i] = temp[i];
  }
  delete[] temp;
}

#endif