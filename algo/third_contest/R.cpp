#include <iostream>
#include <cstddef>

struct Cell {
  int coord1;
  int coord2;
  int value1;
  bool operator<(const Cell& other) const {
    return value1 < other.value1;
  }
};

struct Pair {
  Cell key;
  Cell max;
};

struct Node {
  Node* next;
  Pair value;
};

template <class T>
T Max(T a, T b) {
  return (a < b ? b : a);
}

template <class T>
T Max(T a, T b, T c) {
  return (a < b ? (c < b ? b : c) : (c < a ? a : c));
}

class Stack {
 public:
  Stack() {
    size_ = 0;
    last_ = nullptr;
  }

  ~Stack() {
    Clear();
  }

  void PushBack(const Cell& value) {
    if (size_) {
      ++size_;
      Pair pair;
      pair.key = value;
      pair.max = Max(value, last_->value.max);
      Node* p_node = new Node{last_, pair};
      last_ = p_node;
    }
    if (!size_) {
      ++size_;
      Pair pair;
      pair.key = value;
      pair.max = value;
      last_ = new Node{nullptr, pair};
    }
  }

  Cell PopBack() {
    if (size_) {
      --size_;
      Node* p_node = last_;
      last_ = p_node->next;
      Cell value = p_node->value.key;
      delete p_node;
      return value;
    }
    return {0, 0, -1};
  }

  Cell BackValue() {
    return (size_ ? last_->value.key : Cell{0, 0, -1});
  }

  Cell BackMax() {
    return (size_ ? last_->value.max : Cell{0, 0, -1});
  }

  size_t Size() const {
    return size_;
  }

  void Clear() {
    while (last_) {
      Node* p_node = last_;
      last_ = p_node->next;
      delete p_node;
    }
    size_ = 0;
  }

  Cell Maximum() {
    return (size_ ? BackMax() : Cell{0, 0, -1});
  }

 private:
  Node* last_ = nullptr;
  size_t size_ = 0;
};

class MaxQueue {
 public:
  explicit MaxQueue() = default;

  ~MaxQueue() {
    Clear();
  }

  void Insert(const Cell& value) {
    stack_push_.PushBack(value);
  }

  Cell Dequeue() {
    if (stack_pop_.Size() == 0) {
      while (stack_push_.Size()) {
        Cell key = stack_push_.PopBack();
        stack_pop_.PushBack(key);
      }
    }
    return (stack_pop_.Size() ? stack_pop_.PopBack() : Cell{0, 0, -1});
  }
  Cell MaxQ() {
    if (stack_push_.Size() + stack_pop_.Size() == 0) {
      return Cell{0, 0, -1};
    }
    if (stack_push_.Size() == 0 || stack_pop_.Size() == 0) {
      return (stack_push_.Size() ? stack_push_.BackMax() : stack_pop_.BackMax());
    }
    return (Max(stack_push_.BackMax(), stack_pop_.BackMax()));
  }
  size_t Size() const {
    return (stack_push_.Size() + stack_pop_.Size());
  }

  Cell Back() {
    if (stack_pop_.Size() == 0) {
      while (stack_push_.Size()) {
        Cell key = stack_push_.PopBack();
        stack_pop_.PushBack(key);
      }
    }
    return (stack_pop_.Size() ? stack_pop_.BackValue() : Cell{0, 0, -1});
  }
  void Clear() {
    stack_push_.Clear();
    stack_pop_.Clear();
  }

 private:
  Stack stack_push_;
  Stack stack_pop_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int x = 0;
  int y = 0;
  std::cin >> x >> y;
  int h = 0;
  int w = 0;
  std::cin >> h >> w;
  MaxQueue queue;
  auto array = new int* [x] {};
  for (int i = 0; i < x; ++i) {
    array[i] = new int[y];
    for (int j = 0; j < y; ++j) {
      std::cin >> array[i][j];
    }
  }
  // сделаем dp array
  auto dp = new Cell* [x] {};
  for (int i = 0; i < x; ++i) {
    dp[i] = new Cell[y]{};
  }
  int i = 0;
  int j = 0;
  int ptr1 = i;
  int ptr2 = j;
  while (ptr1 < x && w > 1) {
    while (ptr2 < y) {
      while (j < (ptr2 + w - 1 < y ? ptr2 + w - 1 : y)) {
        queue.Insert({i, j, array[i][j]});
        ++j;
      }
      dp[ptr1][ptr2] = queue.MaxQ();
      queue.Dequeue();
      ++ptr2;
    }
    ptr2 = 0;
    ++ptr1;
    ++i;
    j = 0;
    while (queue.Size()) {
      queue.Dequeue();
    }
  }
  i = 0;
  j = 0;
  ptr1 = i;
  ptr2 = j;
  while (ptr2 < y && h > 1) {
    while (ptr1 < x) {
      while (i < (ptr1 + h - 1 < x ? ptr1 + h - 1 : x)) {
        queue.Insert((w == 1 ? Cell{i, j, array[i][j]} : dp[i][j]));
        ++i;
      }
      dp[ptr1][ptr2] = queue.MaxQ();
      queue.Dequeue();
      ++ptr1;
    }
    ptr1 = 0;
    ++ptr2;
    ++j;
    i = 0;
    while (queue.Size()) {
      queue.Dequeue();
    }
  }
  int coord1 = -1;
  int coord2 = -1;
  int coord_max1 = 0;
  int coord_max2 = 0;
  while (true) {
    if (coord1 == coord_max1 && coord2 == coord_max2) {
      break;
    }
    coord1 = coord_max1;
    coord2 = coord_max2;
    std::cout << coord1 << ' ' << coord2 << '\n';
    Cell cell1{0, 0, -1};
    Cell cell2{0, 0, -1};
    Cell cell3{0, 0, -1};
    if (coord1 < x - 1 && h > 1) {
      cell1 = dp[coord1 + 1][coord2];
    }
    if (coord2 < y - 1 && w > 1) {
      cell2 = dp[coord1][coord2 + 1];
    }
    if (coord1 + h - 1 < x && coord2 + w - 1 < y) {
      cell3 = {coord1 + h - 1, coord2 + w - 1, array[coord1 + h - 1][coord2 + w - 1]};
    }
    cell1 = Max(cell1, cell2, cell3);
    if (cell1.value1 == -1) {
      break;
    }
    coord_max1 = cell1.coord1;
    coord_max2 = cell1.coord2;
  }
  for (int i = 0; i < x; ++i) {
    delete[] array[i];
    delete[] dp[i];
  }
  delete[] dp;
  delete[] array;
  return 0;
}