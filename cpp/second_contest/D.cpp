#include <iostream>
#include <cstddef>
#include <cstring>

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
  int m = 0;
  MinQueue q;
  char s[100]{};
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> s;
    if (!strcmp(s, "enqueue")) {
      int a = 0;
      std::cin >> a;
      q.Insert(a);
      std::cout << "ok" << '\n';
    }
    if (!strcmp(s, "dequeue")) {
      int temp = q.Dequeue();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "front")) {
      int temp = q.Back();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "size")) {
      std::cout << q.Size() << '\n';
    }
    if (!strcmp(s, "clear")) {
      q.Clear();
      std::cout << "ok" << '\n';
    }
    if (!strcmp(s, "min")) {
      int temp = q.MinQ();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
  }
  return 0;
}