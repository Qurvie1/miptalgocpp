#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::istream_iterator<int> it(std::cin);
  std::vector<int> vec(it, std::istream_iterator<int>());
  std::cout << std::count(vec.begin(), vec.end(), vec.back()) - 1;
  return 0;
}