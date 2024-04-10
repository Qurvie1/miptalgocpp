#include <iostream>
#include <cstddef>

struct Pair {
  int key;
  int min;
};

struct Node {
  Node* next;
  Pair value;
};

int Min(int a, int b) {
  return (a < b ? a : b);
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

  void PushBack(const int& value) {
    if (size_) {
      ++size_;
      Pair pair;
      pair.key = value;
      pair.min = Min(value, last_->value.min);
      Node* p_node = new Node{last_, pair};
      last_ = p_node;
    }
    if (!size_) {
      ++size_;
      Pair pair;
      pair.key = value;
      pair.min = value;
      last_ = new Node{nullptr, pair};
    }
  }

  int PopBack() {
    if (size_) {
      --size_;
      Node* p_node = last_;
      last_ = p_node->next;
      int value = p_node->value.key;
      delete p_node;
      return value;
    }
    return -1;
  }

  int BackValue() {
    return (size_ ? last_->value.key : -1);
  }

  int BackMin() {
    return (size_ ? last_->value.min : -1);
  }

  size_t Size() {
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

  int Minimun() {
    return (size_ ? BackMin() : -1);
  }

 private:
  Node* last_ = nullptr;
  size_t size_ = 0;
};

class MinQueue {
 public:
  explicit MinQueue() = default;

  ~MinQueue() {
    Clear();
  }

  void Insert(const int& value) {
    stack_push_.PushBack(value);
  }

  int Dequeue() {
    if (stack_pop_.Size() == 0) {
      while (stack_push_.Size()) {
        int key = stack_push_.PopBack();
        stack_pop_.PushBack(key);
      }
    }
    return (stack_pop_.Size() ? stack_pop_.PopBack() : -1);
  }
  int MinQ() {
    if (stack_push_.Size() + stack_pop_.Size() == 0) {
      return -1;
    }
    if (stack_push_.Size() == 0 || stack_pop_.Size() == 0) {
      return (stack_push_.Size() ? stack_push_.BackMin() : stack_pop_.BackMin());
    }
    return (Min(stack_push_.BackMin(), stack_pop_.BackMin()));
  }
  size_t Size() {
    return (stack_push_.Size() + stack_pop_.Size());
  }

  int Back() {
    if (stack_pop_.Size() == 0) {
      while (stack_push_.Size()) {
        int key = stack_push_.PopBack();
        stack_pop_.PushBack(key);
      }
    }
    return (stack_pop_.Size() ? stack_pop_.BackValue() : -1);
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
  int n = 0;
  int k = 0;
  MinQueue q;
  std::cin >> n >> k;
  auto answer = new int[n - k + 1]{};
  for (int i = 0; i < k; ++i) {
    int temp = 0;
    std::cin >> temp;
    q.Insert(temp);
  }
  for (int i = k; i < n; ++i) {
    answer[i - k] = q.MinQ();
    int temp = 0;
    std::cin >> temp;
    q.Insert(temp);
    temp = q.Dequeue();
  }
  answer[n - k] = q.MinQ();
  for (int i = 0; i < n - k + 1; ++i) {
    std::cout << answer[i] << '\n';
  }
  delete[] answer;
  return 0;
}