#include <iostream>
#include <cstring>

int AnswerCount(char* s, int k) {
  int q = strlen(s);
  int counter = 0;
  int answer = 0;
  for (int i = 0; i < q - k; ++i) {
    if (s[i] == s[i + k]) {
      ++counter;
    } else {
      counter = 0;
    }
    answer += counter;
  }
  return answer;
}

int main() {
  int k = 0;
  std::cin >> k;
  auto s = new char[1000001]{};
  std::cin >> s;
  std::cout << AnswerCount(s, k) << '\n';
  delete[] s;
  return 0;
}