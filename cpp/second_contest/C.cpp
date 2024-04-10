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
  int Front() {
    return first_->value;
  }
  int Back() {
    return last_->value;
  }
  int Size() {
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

int main() {
  int k = 0;
  std::cin >> k;
  Deque deque;
  char s[100]{};
  for (int i = 0; i < k; ++i) {
    std::cin >> s;
    if (!strcmp(s, "push_front")) {
      int a = 0;
      std::cin >> a;
      deque.PushFront(a);
      std::cout << "ok" << '\n';
    }
    if (!strcmp(s, "push_back")) {
      int a = 0;
      std::cin >> a;
      deque.PushBack(a);
      std::cout << "ok" << '\n';
    }
    if (!strcmp(s, "pop_front")) {
      if (deque.Size() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << deque.PopFront() << '\n';
      }
    }
    if (!strcmp(s, "pop_back")) {
      if (deque.Size() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << deque.PopBack() << '\n';
      }
    }
    if (!strcmp(s, "back")) {
      if (deque.Size() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << deque.Back() << '\n';
      }
    }
    if (!strcmp(s, "front")) {
      if (deque.Size() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << deque.Front() << '\n';
      }
    }
    if (!strcmp(s, "size")) {
      std::cout << deque.Size() << '\n';
    }
    if (!strcmp(s, "clear")) {
      deque.Clear();
      std::cout << "ok" << '\n';
    }
    if (!strcmp(s, "exit")) {
      std::cout << "bye" << '\n';
      deque.Clear();
    }
  }
  return 0;
}