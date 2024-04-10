#include <iostream>

struct MemoryUnit {
  int start;
  int end;
  int idx;
  int used;
  MemoryUnit* left;
  MemoryUnit* right;
  MemoryUnit(MemoryUnit* left, struct MemoryUnit* right, int start, int end, int idx, int used) {
    this->left = left;
    this->right = right;
    this->start = start;
    this->end = end;
    this->idx = idx;
    this->used = used;
    if (left) {
      left->right = this;
    }
    if (right) {
      right->left = this;
    }
  }
  void Remove() {
    if (left) {
      left->right = right;
    }
    if (right) {
      right->left = left;
    }
  }
};

int Length(MemoryUnit* memoryunit) {
  return memoryunit->end - memoryunit->start + 1;
}

bool Comparator(MemoryUnit* memoryunit1, MemoryUnit* memoryunit2) {
  int len1 = Length(memoryunit1);
  int len2 = Length(memoryunit2);
  if (len1 != len2) {
    return len1 > len2;
  }
  return memoryunit1->start < memoryunit2->start;
}

class MaxHeap {
 public:
  MemoryUnit* heap[100000];
  int len = 0;

  void Swap(int i, int j) {
    MemoryUnit* temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    heap[i]->idx = i;
    heap[j]->idx = j;
  }

  void SiftDown(int i) {
    while (true) {
      int j = i;
      int left = 2 * j + 1;
      int right = left + 1;
      if (left < len && Comparator(heap[left], heap[i])) {
        i = left;
      }
      if (right < len && Comparator(heap[right], heap[i])) {
        i = right;
      }
      if (i != j) {
        Swap(i, j);
      } else {
        break;
      }
    }
  }

  void SiftUp(int index) {
    int parent = 0;
    parent = (index - 1) / 2;
    while (Comparator(heap[index], heap[parent]) && index > 0) {
      Swap(index, parent);
      index = parent;
      parent = (index - 1) / 2;
    }
  }

  void Add(MemoryUnit* memoryunit) {
    memoryunit->idx = len;
    heap[len] = memoryunit;
    SiftUp(len++);
  }

  void Remove(int i) {
    Swap(i, --len);
    SiftUp(i);
    SiftDown(i);
  }
};

int main() {
  int n = 0;
  int m = 0;
  MaxHeap maxh;
  MemoryUnit* request[100000];
  std::cin >> n >> m;
  maxh.heap[0] = new MemoryUnit(nullptr, nullptr, 1, n, maxh.len++, 0);
  for (int i = 0; i < m; i++) {
    int x = 0;
    std::cin >> x;
    if (x > 0) {
      if (!maxh.len || Length(maxh.heap[0]) < x) {
        std::cout << -1 << '\n';
      } else {
        MemoryUnit* temp = maxh.heap[0];
        std::cout << temp->start << '\n';
        request[i] = new MemoryUnit(temp->left, temp, temp->start, temp->start + x - 1, -1, 1);
        temp->start += x;
        if (Length(temp)) {
          maxh.SiftDown(temp->idx);
        } else {
          temp->Remove();
          maxh.Swap(0, --maxh.len);
          maxh.SiftDown(0);
          delete temp;
        }
      }
    } else {
      x = -(x + 1);
      struct MemoryUnit* temp = request[x];
      if (!temp) {
        continue;
      }
      MemoryUnit* left = request[x]->left;
      MemoryUnit* right = request[x]->right;
      if (left && !left->used && right && !right->used) {
        left->end = right->end;
        maxh.SiftUp(left->idx);
        temp->Remove();
        delete temp;
        maxh.Remove(right->idx);
        right->Remove();
        delete right;
      } else if (left && !left->used) {
        left->end = temp->end;
        maxh.SiftUp(left->idx);
        temp->Remove();
        delete temp;
      } else if (right && !right->used) {
        right->start = temp->start;
        maxh.SiftUp(right->idx);
        temp->Remove();
        delete temp;
      } else {
        temp->used = false;
        maxh.Add(temp);
      }
    }
  }
  return 0;
}