#ifndef ITEROPS_H
#define ITEROPS_H

#include <type_traits>
#include <concepts>

template <std::random_access_iterator Iterator>
void Advance(Iterator& it, int dist) {
  it += dist;
}

template <std::input_iterator Iterator>
void Advance(Iterator& it, int dist) {
  while (dist < 0) {
    ++dist;
    --it;
  }
  while (dist > 0) {
    --dist;
    ++it;
  }
}

template <typename Iterator>
Iterator Next(Iterator it, int dist = 1) {
  Advance(it, dist);
  return it;
}

template <typename Iterator>
Iterator Prev(Iterator it, int dist = 1) {
  Advance(it, -dist);
  return it;
}

template <std::random_access_iterator Iterator>
int Distance(Iterator it1, Iterator it2) {
  return it2 - it1;
}

template <std::input_iterator Iterator>
int Distance(Iterator it1, Iterator it2) {
  int i = 0;
  for (; it1 != it2; ++i, ++it1);
  return i;
}

#endif