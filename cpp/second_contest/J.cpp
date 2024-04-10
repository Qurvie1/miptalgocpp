#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  Node* next = nullptr;
  int value;
};

class Deque {
 public:
  Deque() : first_(nullptr), last_(nullptr), size_(0) {
  }
  ~Deque() {
    Clear();
  }
  void PushFront(const int& value) {
    if (size_) {
      first_->prev = new Node{nullptr, first_, value};
      first_ = first_->prev;
    } else {
      first_ = last_ = new Node{nullptr, nullptr, value};
    }
    ++size_;
  }
  void PushBack(const int& value) {
    if (size_) {
      last_->next = new Node{last_, nullptr, value};
      last_ = last_->next;
    } else {
      last_ = first_ = new Node{nullptr, nullptr, value};
    }
    ++size_;
  }
  int PopFront() {
    --size_;
    int value = first_->value;
    if (size_) {
      Node* p_node = first_;
      first_ = p_node->next;
      delete p_node;
      first_->prev = nullptr;
    } else {
      delete first_;
      first_ = last_ = nullptr;
    }
    return value;
  }
  int PopBack() {
    --size_;
    int value = last_->value;
    if (size_) {
      Node* p_node = last_;
      last_ = p_node->prev;
      delete p_node;
      last_->next = nullptr;
    } else {
      delete last_;
      first_ = last_ = nullptr;
    }
    return value;
  }
  int Front() const {
    return first_->value;
  }
  int Back() const {
    return last_->value;
  }
  int Size() const {
    return size_;
  }
  void Clear() {
    while (size_) {
      if (size_ > 1) {
        Node* p_node = last_;
        last_ = p_node->prev;
        delete p_node;
        last_->next = nullptr;
      }
      if (size_ == 1) {
        delete last_;
        first_ = last_ = nullptr;
      }
      --size_;
    }
  }

 private:
  Node* first_ = nullptr;
  Node* last_ = nullptr;
  int size_ = 0;
};

void Goblins(int n) {
  Deque deque1;
  Deque deque2;
  char s[100]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> s;
    if (!strcmp(s, "+")) {
      int a = 0;
      std::cin >> a;
      (deque2.Size() ? deque2 : deque1).PushBack(a);
    }
    if (!strcmp(s, "-")) {
      std::cout << (deque1.Size() ? deque1 : deque2).PopFront() << '\n';
    }
    if (!strcmp(s, "*")) {
      int a = 0;
      bool flag = false;
      std::cin >> a;
      int sum = deque1.Size() + deque2.Size();
      while (deque1.Size() >= (sum + 1) / 2) {
        if (deque1.Size() == (sum + 1) / 2) {
          deque1.PushBack(a);
          flag = true;
          break;
        }
        deque2.PushFront(deque1.PopBack());
      }
      if (!flag) {
        while (deque1.Size() <= (sum + 1) / 2) {
          if (deque1.Size() == (sum + 1) / 2) {
            deque1.PushBack(a);
            break;
          }
          deque1.PushBack(deque2.PopFront());
        }
      }
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  Goblins(n);
  return 0;
}