#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int counter = 1;

struct Team {
  int solved;
  int time;
  int index;
};

std::istream& operator>>(std::istream& in, Team& team) {
  in >> team.solved >> team.time;
  team.index = counter++;
  return in;
}

int main() {
  int size = 0;
  std::cin >> size;
  std::istream_iterator<Team> it(std::cin);
  std::vector<Team> vec(it, std::istream_iterator<Team>());
  std::sort(vec.begin(), vec.end(), [](const Team& first, const Team& second) {
    if (first.solved != second.solved) {
      return first.solved > second.solved;
    }
    if (first.time != second.time) {
      return first.time < second.time;
    }
    return first.index < second.index;
  });
  for (const Team& t : vec) {
    std::cout << t.index << '\n';
  }
  return 0;
}