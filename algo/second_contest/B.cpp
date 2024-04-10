#include <iostream>

class Heap {
 public:
  Heap() : max_size_(0), current_size_(0), h_(nullptr) {
  }

  explicit Heap(int n) {
    max_size_ = n;
    h_ = new int[n]{};
  }

  ~Heap() {
    delete[] h_;
  }

  void Addelem(int elem) {
    if (current_size_ == max_size_) {
      std::cout << -1 << '\n';
      return;
    }
    int index = current_size_;
    int answer = index;
    int parent = 0;
    h_[index] = elem;
    parent = (index - 1) / 2;
    while (parent >= 0 && index > 0) {
      if (h_[index] > h_[parent]) {
        Swap(h_[index], h_[parent]);
        answer = parent;
      }
      index = parent;
      parent = (index - 1) / 2;
    }
    ++current_size_;
    std::cout << answer + 1 << '\n';
  }

  void Getmax() {
    if (current_size_ == 0) {
      std::cout << -1 << '\n';
      return;
    }
    Swap(h_[0], h_[current_size_ - 1]);
    --current_size_;
    if (current_size_ == 0) {
      std::cout << 0 << ' ';
    }
    if (current_size_ > 0) {
      SiftDown(0, true);
    }
    std::cout << h_[current_size_] << '\n';
  }

  void Delelem(int index) {
    --index;
    if (index >= current_size_ || index < 0) {
      std::cout << -1 << '\n';
      return;
    }
    std::cout << h_[index] << '\n';
    Swap(h_[index], h_[current_size_ - 1]);
    --current_size_;
    int parent = 0;
    int temp = index;
    parent = (index - 1) / 2;
    while (parent >= 0 && index > 0) {
      if (h_[index] > h_[parent]) {
        Swap(h_[index], h_[parent]);
        temp = parent;
      }
      index = parent;
      parent = (index - 1) / 2;
    }
    if (temp <= current_size_ / 2 - 1) {
      SiftDown(temp, false);
    }
  }

  void Showheap() {
    for (int i = 0; i < current_size_; ++i) {
      std::cout << h_[i] << ' ';
    }
  }

 private:
  int max_size_ = 0;
  int current_size_ = 0;
  int* h_ = nullptr;

  void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
  }

  void SiftDown(int index, bool show) {
    int left = 0;
    int right = 0;
    int big = 0;
    while (true) {
      left = 2 * index + 1;
      right = left + 1;
      big = index;
      big = (left < current_size_ && h_[big] < h_[left] ? left : big);
      big = (right < current_size_ && h_[big] < h_[right] ? right : big);
      if (big == index) {
        if (show) {
          std::cout << index + 1 << ' ';
        }
        break;
      }
      Swap(h_[big], h_[index]);
      index = big;
    }
  }
};

int main() {
  int n = 0;
  int m = 0;
  int temp = 0;
  std::cin >> n >> m;
  Heap heap(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> temp;
    if (temp == 1) {
      heap.Getmax();
    }
    if (temp == 2) {
      int a = 0;
      std::cin >> a;
      heap.Addelem(a);
    }
    if (temp == 3) {
      int a = 0;
      std::cin >> a;
      heap.Delelem(a);
    }
  }
  heap.Showheap();
  return 0;
}