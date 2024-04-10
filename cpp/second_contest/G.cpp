#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  Node* next = nullptr;
  char value;
};

class Deque {
 public:
  Deque() : first_(nullptr), last_(nullptr), size_(0) {
  }
  ~Deque() {
    Clear();
  }
  void PushFront(const char& value) {
    if (size_) {
      first_->prev = new Node{nullptr, first_, value};
      first_ = first_->prev;
    } else {
      first_ = last_ = new Node{nullptr, nullptr, value};
    }
    ++size_;
  }
  void PushBack(const char& value) {
    if (size_) {
      last_->next = new Node{last_, nullptr, value};
      last_ = last_->next;
    } else {
      last_ = first_ = new Node{nullptr, nullptr, value};
    }
    ++size_;
  }
  void PopFront() {
    --size_;
    if (size_) {
      Node* p_node = first_;
      first_ = p_node->next;
      delete p_node;
      first_->prev = nullptr;
    } else {
      delete first_;
      first_ = last_ = nullptr;
    }
  }
  void PopBack() {
    --size_;
    if (size_) {
      Node* p_node = last_;
      last_ = p_node->prev;
      delete p_node;
      last_->next = nullptr;
    } else {
      delete last_;
      first_ = last_ = nullptr;
    }
  }
  char Front() {
    return first_->value;
  }
  char Back() {
    return (size_ ? last_->value : '1');
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

bool IsCorrectBracketSequence(Deque& deque, char* s) {
  int len = static_cast<int>(strlen(s));
  for (int i = 0; i < len; ++i) {
    if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
      deque.PushBack(s[i]);
    } else if ((deque.Back() == '(' && s[i] == ')') || (deque.Back() == '{' && s[i] == '}') ||
               (deque.Back() == '[' && s[i] == ']')) {
      deque.PopBack();
    } else {
      deque.PushBack(s[i]);
      break;
    }
  }
  return deque.Size() == 0;
}

int main() {
  Deque deque;
  auto s = new char[100001]{};
  std::cin.getline(s, 100001);
  std::cout << (IsCorrectBracketSequence(deque, s) ? "YES" : "NO");
  delete[] s;
  return 0;
}