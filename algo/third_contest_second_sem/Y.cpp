#include <iostream>
#include <string>
#include <array>
#include <unordered_set>
#include <queue>
#include <limits>
#include <sstream>

class State {
 public:
  State() = default;

  explicit State(const std::string& st) {
    numbers_.resize(16);
    for (size_t i = 0; i < st.size(); ++i) {
      if (st[i] == 0) {
        empty_row_ = static_cast<int>(i / 4);
        empty_column_ = static_cast<int>(i % 4);
      }
      numbers_[i] = st[i];
    }
  }

  State(const std::string& st, int val) : value_(val) {
    numbers_.resize(16);
    for (size_t i = 0; i < st.size(); ++i) {
      if (st[i] == 0) {
        empty_row_ = static_cast<int>(i / 4);
        empty_column_ = static_cast<int>(i % 4);
      }
      numbers_[i] = st[i];
    }
  }

  State(const std::string& st, int val, int dp) : value_(val), depth_(dp) {
    numbers_.resize(16);
    for (size_t i = 0; i < st.size(); ++i) {
      if (st[i] == 0) {
        empty_row_ = static_cast<int>(i / 4);
        empty_column_ = static_cast<int>(i % 4);
      }
      numbers_[i] = st[i];
    }
  }

  bool operator<(const State& other) const noexcept {
    return value_ > other.value_;
  }

  bool operator==(const State& other) const noexcept {
    return numbers_ == other.numbers_;
  }

  std::string numbers_;
  std::string actions;
  int value_ = std::numeric_limits<int>::max();
  int empty_column_;
  int empty_row_;
  int depth_;
};

class AStar {
 public:
  explicit AStar(std::string&);

  void Solver();

  bool CheckCorrect(const State&);

  void ExpandNodes(const State&);

  int Heuristic(const State&);

  int ManhattanDistance(const State&);

  int LastMove(const State&);

 private:
  State goalstate_;
  State startstate_;
  std::priority_queue<State> queue_;
  std::unordered_set<std::string> states_;
  int visited_ = 0;
};

void AStar::Solver() {
  if (!CheckCorrect(startstate_)) {
    std::cout << -1;
    return;
  }
  states_.emplace(startstate_.numbers_);
  queue_.push(startstate_);
  while (!queue_.empty()) {
    auto curr = queue_.top();
    queue_.pop();
    ++visited_;
    if (curr == goalstate_) {
      std::cout << curr.depth_ << '\n';
      std::cout << curr.actions << '\n';
      return;
    }
    ExpandNodes(curr);
  }
  std::cout << -1 << '\n';
}

void AStar::ExpandNodes(const State& state) {
  int col = state.empty_column_;
  int row = state.empty_row_;
  char symbol = 'a';
  if (row > 0) {
    symbol = state.numbers_[4 * (row - 1) + col];
    std::string newnumbers = state.numbers_;
    newnumbers[4 * row + col] = symbol;
    newnumbers[4 * (row - 1) + col] = 0;
    State new_st(newnumbers, std::numeric_limits<int>::max(), state.depth_ + 1);
    if (!states_.contains(newnumbers)) {
      new_st.value_ = new_st.depth_ + Heuristic(new_st);
      new_st.actions = state.actions + 'D';
      queue_.push(new_st);
      states_.emplace(newnumbers);
    }
  }
  if (row < 3) {
    symbol = state.numbers_[4 * (row + 1) + col];
    std::string newnumbers = state.numbers_;
    newnumbers[4 * row + col] = symbol;
    newnumbers[4 * (row + 1) + col] = 0;
    State new_st(newnumbers, std::numeric_limits<int>::max(), state.depth_ + 1);
    if (!states_.contains(newnumbers)) {
      new_st.value_ = new_st.depth_ + Heuristic(new_st);
      new_st.actions = state.actions + 'U';
      queue_.push(new_st);
      states_.emplace(newnumbers);
    }
  }
  if (col > 0) {
    symbol = state.numbers_[4 * row + col - 1];
    std::string newnumbers = state.numbers_;
    newnumbers[4 * row + col] = symbol;
    newnumbers[4 * row + col - 1] = 0;
    State new_st(newnumbers, std::numeric_limits<int>::max(), state.depth_ + 1);
    if (!states_.contains(newnumbers)) {
      new_st.value_ = new_st.depth_ + Heuristic(new_st);
      new_st.actions = state.actions + 'R';
      queue_.push(new_st);
      states_.emplace(newnumbers);
    }
  }
  if (col < 3) {
    symbol = state.numbers_[4 * row + col + 1];
    std::string newnumbers = state.numbers_;
    newnumbers[4 * row + col] = symbol;
    newnumbers[4 * row + col + 1] = 0;
    State new_st(newnumbers, std::numeric_limits<int>::max(), state.depth_ + 1);
    if (!states_.contains(newnumbers)) {
      new_st.value_ = new_st.depth_ + Heuristic(new_st);
      new_st.actions = state.actions + 'L';
      queue_.push(new_st);
      states_.emplace(newnumbers);
    }
  }
}

int AStar::ManhattanDistance(const State& state) {
  int result = 0;
  for (size_t i = 0; i < state.numbers_.size(); ++i) {
    char symbol = state.numbers_[i];
    for (size_t j = 0; j < goalstate_.numbers_.size(); ++j) {
      if (symbol == goalstate_.numbers_[j]) {
        result += abs(static_cast<int>((i % 4) - (j % 4))) + abs(static_cast<int>((i / 4) - (j / 4)));
        break;
      }
    }
  }
  return result;
}

int AStar::LastMove(const State& state) {
  if (state.numbers_[15] == 12 || state.numbers_[14] == 12 || state.numbers_[13] == 12 || state.numbers_[12] == 12) {
    return 0;
  }
  if (state.numbers_[3] == 15 || state.numbers_[7] == 15 || state.numbers_[11] == 15 || state.numbers_[15] == 15) {
    return 0;
  }
  return 2;
}

int AStar::Heuristic(const State& state) {
  return ManhattanDistance(state) + LastMove(state);
}

AStar::AStar(std::string& statement) {
  goalstate_.numbers_.resize(16);
  statement.resize(16);
  for (size_t i = 1; i <= 16; ++i) {
    goalstate_.numbers_[i - 1] = static_cast<char>(i % 16);
  }
  startstate_ = State(statement);
  startstate_.depth_ = 0;
  startstate_.value_ = Heuristic(startstate_);
}

bool AStar::CheckCorrect(const State& state) {
  int invs = 0;
  for (size_t i = 0; i < state.numbers_.size(); ++i) {
    if (state.numbers_[i] == 0) {
      continue;
    }
    for (size_t j = i + 1; j < state.numbers_.size(); ++j) {
      if (state.numbers_[j] == 0) {
        continue;
      }
      if (state.numbers_[i] > state.numbers_[j]) {
        ++invs;
      }
    }
  }
  return (invs + state.empty_row_ + 1) % 2 == 0;
}

int main() {
  std::string enter;
  std::getline(std::cin, enter);
  std::string temp;
  int counter = 0;
  std::string statest;
  statest.resize(16);
  std::istringstream stream(enter);
  while (counter < 16) {
    stream >> temp;
    if (temp.size() > 1) {
      statest[counter] = static_cast<char>(10 * (temp[0] - '0') + (temp[1] - '0'));
    } else {
      statest[counter] = static_cast<char>(temp[0] - '0');
    }
    ++counter;
  }
  AStar algo(statest);
  algo.Solver();
  return 0;
}