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
  size_t Size() const {
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
  size_t size_ = 0;
};

int Calculate(char* s) {
  Deque deque;
  int len = static_cast<int>(strlen(s));
  for (int i = 0; i < len; ++i) {
    if (s[i] == '+') {
      int a = deque.PopBack();
      int b = deque.PopBack();
      deque.PushBack(a + b);
    }
    if (s[i] == '-') {
      int b = deque.PopBack();
      int a = deque.PopBack();
      deque.PushBack(a - b);
    }
    if (s[i] == '*') {
      int a = deque.PopBack();
      int b = deque.PopBack();
      deque.PushBack(a * b);
    }
    if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
      deque.PushBack(s[i] - '0');
    }
  }
  return deque.Back();
}

int main() {
  auto s = new char[1000000]{};
  std::cin.getline(s, 1000000);
  std::cout << Calculate(s);
  delete[] s;
  return 0;
}