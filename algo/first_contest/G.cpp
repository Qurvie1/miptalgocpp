#include <iostream>

void ChipsToRec(int n);
void ChipsOutRec(int n);

void ChipsToRec(int n) {
  if (n == 1) {
    std::cout << 1 << ' ';
  } else if (n == 2) {
    std::cout << 1 << ' ' << 2 << ' ';
  } else {
    ChipsToRec(n - 1);
    ChipsOutRec(n - 2);
    std::cout << n << ' ';
    ChipsToRec(n - 2);
  }
}

void ChipsOutRec(int n) {
  if (n == 1) {
    std::cout << -1 << ' ';
  } else if (n == 2) {
    std::cout << -2 << ' ' << -1 << ' ';
  } else {
    ChipsOutRec(n - 2);
    std::cout << -n << ' ';
    ChipsToRec(n - 2);
    ChipsOutRec(n - 1);
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  ChipsToRec(n);
  return 0;
}