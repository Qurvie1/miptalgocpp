#include <iostream>

const int kMaxTurns = 1000000;

struct Node {
  Node* next = nullptr;
  int value;
};

class Queue {
 public:
  ~Queue() {
    Clear();
  }
  void PushBack(const int& value) {
    if (size_) {
      back_->next = new Node{nullptr, value};
      back_ = back_->next;
    } else {
      front_ = back_ = new Node{nullptr, value};
    }
    ++size_;
  }
  int PopFront() {
    --size_;
    int value = front_->value;
    if (size_) {
      Node* p_node = front_;
      front_ = p_node->next;
      delete p_node;
    } else {
      delete front_;
      front_ = back_ = nullptr;
    }
    return value;
  }
  int Size() const {
    return size_;
  }
  void Clear() {
    while (size_) {
      if (size_ > 1) {
        Node* p_node = front_;
        front_ = p_node->next;
        delete p_node;
      } else if (size_ == 1) {
        delete front_;
        front_ = back_ = nullptr;
      }
      --size_;
    }
  }

 private:
  Node* front_ = nullptr;
  Node* back_ = nullptr;
  int size_ = 0;
};

void CardGame(Queue& q1, Queue& q2, int& counter) {
  while (q1.Size() && q2.Size()) {
    int temp1 = q1.PopFront();
    int temp2 = q2.PopFront();
    if ((temp1 == 0 && temp2 == 9) || (temp1 > temp2 && (temp1 != 9 || temp2 != 0))) {
      q1.PushBack(temp1);
      q1.PushBack(temp2);
      ++counter;
    }
    if ((temp2 == 0 && temp1 == 9) || (temp2 > temp1 && (temp2 != 9 || temp1 != 0))) {
      q2.PushBack(temp1);
      q2.PushBack(temp2);
      ++counter;
    }
    if (counter >= kMaxTurns) {
      break;
    }
  }
}

int main() {
  Queue q1;
  Queue q2;
  int counter = 0;
  for (int i = 0; i < 5; ++i) {
    int a = 0;
    std::cin >> a;
    q1.PushBack(a);
  }
  for (int i = 0; i < 5; ++i) {
    int a = 0;
    std::cin >> a;
    q2.PushBack(a);
  }
  CardGame(q1, q2, counter);
  if (counter >= kMaxTurns) {
    std::cout << "botva";
  }
  std::cout << (q1.Size() == 0 ? "second" : "first") << ' ' << counter;
  return 0;
}