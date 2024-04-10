#include <iostream>
#include <cstring>
#include <cctype>

void Swap(char& a, char& b) {
  char temp = b;
  b = a;
  a = temp;
}

bool IsPalyndrome(char* s, bool for_delete) {
  int p = strlen(s);
  bool flag = true;
  int troubles = 0;
  for (int i = 0; i < p / 2; ++i) {
    if (s[i] != s[p - i - 1] && !for_delete) {
      ++troubles;
      s[i] = (flag ? s[p - i - 1] : s[i]);
      flag = false;
    } else if (s[i] != s[p - i - 1] && for_delete) {
      return false;
    }
  }
  return troubles <= 1;
}

bool IsDelete(char* s) {
  int p = strlen(s);
  int i = 0;
  bool flag = true;
  while (i < p / 2 && p - i - 2 >= 0) {
    if (s[i] != s[p - i - 1] && s[i] == s[p - i - 2]) {
      for (int j = p - i - 1; j >= 1; --j) {
        Swap(s[j], s[j - 1]);
      }
      flag = false;
    } else if (s[i] != s[p - i - 1] && s[i + 1] == s[p - i - 1]) {
      for (int j = i; j >= 1; --j) {
        Swap(s[j], s[j - 1]);
      }
      flag = false;
    }
    if (!flag) {
      break;
    }
    ++i;
  }
  return IsPalyndrome(s + 1, true);
}

int main() {
  auto s = new char[100001]{};
  std::cin.getline(s, 100001);
  int p = strlen(s);
  int k = 0;
  auto new_s = new char[100001]{};
  for (int i = 0; i < p; ++i) {
    if (std::isalpha(s[i])) {
      new_s[k++] = toupper(s[i]);
    }
  }
  int q = strlen(new_s);
  auto new_s1 = new char[100001]{};
  for (int i = 0; i < q; ++i) {
    new_s1[i] = new_s[i];
  }
  if (IsPalyndrome(new_s, false)) {
    std::cout << "YES\n" << new_s;
  } else if (IsDelete(new_s1)) {
    std::cout << "YES\n" << new_s1 + 1;
  } else {
    std::cout << "NO\n";
  }
  delete[] s;
  delete[] new_s1;
  delete[] new_s;
  return 0;
}