#include <iostream>
#include <cstring>

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

class MinMaxHeap {
 public:
  explicit MinMaxHeap(int m) {
    max_size_ = m;
    h_ = new int[m]{};
  }

  ~MinMaxHeap() {
    delete[] h_;
  }

  int Size() {
    return size_;
  }

  void Insert(const int& elem) {
    h_[size_] = elem;
    PushUp(size_);
    ++size_;
  }

  int GetMin() {
    if (size_) {
      return h_[0];
    }
    return -1;
  }

  int GetMax() {
    if (size_) {
      int max = h_[0];
      int max_index = 0;
      if (size_ > 1 && max < h_[1]) {
        max = h_[1];
        max_index = 1;
      }
      if (size_ > 2 && max < h_[2]) {
        max = h_[2];
        max_index = 2;
      }
      return h_[max_index];
    }
    return -1;
  }

  int ExtractMin() {
    if (size_) {
      int min = h_[0];
      Swap(h_[0], h_[size_ - 1]);
      --size_;
      PushDown(0);
      return min;
    }
    return -1;
  }

  int ExtractMax() {
    if (size_) {
      int max = h_[0];
      int max_index = 0;
      if (size_ > 1 && max < h_[1]) {
        max_index = 1;
        max = h_[1];
      }
      if (size_ > 2 && max < h_[2]) {
        max_index = 2;
        max = h_[2];
      }
      Swap(h_[max_index], h_[size_ - 1]);
      --size_;
      PushDown(max_index);
      return max;
    }
    return -1;
  }

  void Clear() {
    for (int i = 0; i < size_; ++i) {
      h_[i] = 0;
    }
    size_ = 0;
  }

 private:
  int size_ = 0;
  int max_size_ = 0;
  int* h_ = nullptr;

  void PushDownMin(int index) {
    int left_child = 2 * index + 1;
    int right_child = left_child + 1;
    if (left_child < size_) {
      int minimum = h_[left_child];
      int minimum_index = left_child;
      if (right_child < size_ && minimum > h_[right_child]) {
        minimum = h_[right_child];
        minimum_index = right_child;
      }
      int counter = 0;
      while (counter < 4) {
        if ((2 * left_child + 1 + counter) < size_ && minimum > h_[2 * left_child + 1 + counter]) {
          minimum = h_[2 * left_child + 1 + counter];
          minimum_index = 2 * left_child + 1 + counter;
        }
        ++counter;
      }
      if (minimum_index > right_child) {
        if (h_[minimum_index] < h_[index]) {
          Swap(h_[minimum_index], h_[index]);
          if (h_[minimum_index] > h_[(minimum_index - 1) / 2]) {
            Swap(h_[minimum_index], h_[(minimum_index - 1) / 2]);
          }
          PushDown(minimum_index);
        }
      } else if (h_[minimum_index] < h_[index]) {
        Swap(h_[minimum_index], h_[index]);
      }
    }
  }

  void PushDownMax(int index) {
    int left_child = 2 * index + 1;
    int right_child = left_child + 1;
    if (left_child < size_) {
      int maximum = h_[left_child];
      int maximum_index = left_child;
      if (right_child < size_ && maximum < h_[right_child]) {
        maximum = h_[right_child];
        maximum_index = right_child;
      }
      int counter = 0;
      while (counter < 4) {
        if ((2 * left_child + 1 + counter) < size_ && maximum < h_[2 * left_child + 1 + counter]) {
          maximum = h_[2 * left_child + 1 + counter];
          maximum_index = 2 * left_child + 1 + counter;
        }
        ++counter;
      }
      if (maximum_index > right_child) {
        if (h_[maximum_index] > h_[index]) {
          Swap(h_[maximum_index], h_[index]);
          if (h_[maximum_index] < h_[(maximum_index - 1) / 2]) {
            Swap(h_[maximum_index], h_[(maximum_index - 1) / 2]);
          }
          PushDown(maximum_index);
        }
      } else if (h_[maximum_index] > h_[index]) {
        Swap(h_[maximum_index], h_[index]);
      }
    }
  }

  int Level(int index) {
    int counter = 1;
    while (index > 0) {
      ++counter;
      index = (index - 1) / 2;
    }
    return counter;
  }

  void PushDown(int index) {
    (Level(index) % 2 ? PushDownMin(index) : PushDownMax(index));
  }

  void PushUpMin(int index) {
    if (index >= 3) {
      int grandparent = ((((index - 1) / 2) - 1) / 2);
      while (grandparent >= 0 && h_[index] < h_[grandparent]) {
        Swap(h_[index], h_[grandparent]);
        index = grandparent;
        if (index < 3) {
          break;
        }
        grandparent = ((((index - 1) / 2) - 1) / 2);
      }
    }
  }

  void PushUpMax(int index) {
    if (index >= 3) {
      int grandparent = ((((index - 1) / 2) - 1) / 2);
      while (grandparent >= 0 && h_[index] > h_[grandparent]) {
        Swap(h_[index], h_[grandparent]);
        index = grandparent;
        if (index < 3) {
          break;
        }
        grandparent = ((((index - 1) / 2) - 1) / 2);
      }
    }
  }

  void PushUp(int index) {
    if (index != 0) {
      if (Level(index) % 2 == 1) {
        if (h_[index] > h_[(index - 1) / 2]) {
          Swap(h_[index], h_[(index - 1) / 2]);
          PushUpMax((index - 1) / 2);
        } else {
          PushUpMin(index);
        }
      } else {
        if (h_[index] < h_[(index - 1) / 2]) {
          Swap(h_[index], h_[(index - 1) / 2]);
          PushUpMin((index - 1) / 2);
        } else {
          PushUpMax(index);
        }
      }
    }
  }
};

int main() {
  int m = 0;
  std::cin >> m;
  MinMaxHeap heap(m);
  char s[100]{};
  for (int i = 0; i < m; ++i) {
    std::cin >> s;
    if (!strcmp(s, "insert")) {
      int a = 0;
      std::cin >> a;
      heap.Insert(a);
      std::cout << "ok" << '\n';
    }
    if (!strcmp(s, "get_min")) {
      int temp = heap.GetMin();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "get_max")) {
      int temp = heap.GetMax();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "extract_min")) {
      int temp = heap.ExtractMin();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "extract_max")) {
      int temp = heap.ExtractMax();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "size")) {
      std::cout << heap.Size() << '\n';
    }
    if (!strcmp(s, "clear")) {
      heap.Clear();
      std::cout << "ok" << '\n';
    }
  }
  return 0;
}
