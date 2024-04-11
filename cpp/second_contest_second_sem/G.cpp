#include <set>
#include <iostream>
#include <string>
#include <unordered_map>

struct Word {
  int amount;
  std::string name;
  bool operator<(const Word& other) const {
    if (amount != other.amount) {
      return amount > other.amount;
    }
    return name < other.name;
  }
};

int main() {
  std::set<Word> set;
  std::unordered_map<std::string, int> score;
  std::string word;
  while (std::cin >> word) {
    auto it1 = score.find(word);
    if (it1 == score.end()) {
      score.emplace(word, 1);
      set.insert(Word{1, word});
    } else {
      auto it2 = set.find(Word{it1->second, it1->first});
      ++score[word];
      set.insert(Word{it2->amount + 1, it2->name});
      set.erase(*it2);
    }
  }
  for (const auto& elem : set) {
    std::cout << elem.name << '\n';
  }
  return 0;
}