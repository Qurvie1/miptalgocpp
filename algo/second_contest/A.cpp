#include <iostream>

template <class T>
void MergeSort(T* begin, T* end) {
  int left = 0;
  int right = end - begin;
  if (right - left < 2) {
    return;
  }
  T* mid = begin + right / 2;
  int mid1 = right / 2;
  MergeSort(begin, mid);
  MergeSort(mid, end);
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

struct Person {
  char name[41]{};
  char surname[41]{};
  int balls;
  bool operator<(const Person& other) const {
    return balls < other.balls;
  }
};

int main() {
  int n = 0;
  int balls = 0;
  int temp = 0;
  std::cin >> n;
  auto persons = new Person[n]{};
  for (int i = 0; i < n; ++i) {
    Person people;
    std::cin >> people.surname >> people.name;
    for (int j = 0; j < 3; ++j) {
      std::cin >> temp;
      balls += temp;
    }
    people.balls = balls;
    balls = 0;
    persons[i] = people;
  }
  MergeSort(persons, persons + n);
  for (int i = n - 1; i >= 0; --i) {
    std::cout << persons[i].surname << ' ' << persons[i].name << '\n';
  }
  delete[] persons;
  return 0;
}