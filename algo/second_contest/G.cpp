#include <iostream>
#include <cstddef>

template <class T>
T Max(T a, T b) {
  return (a <= b ? b : a);
}

template <class T>
struct NodeAVL {
  NodeAVL<T>* left;
  NodeAVL<T>* right;
  size_t height;
  T value;
};

template <class T>
class AVLTree {
 public:
  AVLTree() : root_(nullptr), size_(0) {
  }

  ~AVLTree() {
    Clear();
  }
  void Insert(const T& value) {
    ++size_;
    root_ = HelperInsert(root_, value);
  }
  void Delete(const T& value) {
    --size_;
    root_ = HelperDelete(root_, value);
  }

  void Clear() {
    size_ = 0;
    HelperClear(root_);
  }

  T GetMin() {
    auto p_curr = root_;
    if (!p_curr) {
      return -1;
    }
    while (p_curr) {
      if (!p_curr->left) {
        delete p_curr;
        return p_curr->value;
      }
      p_curr = p_curr->left;
    }
  }

  T GetMax() {
    auto p_curr = root_;
    if (!p_curr) {
      return -1;
    }
    while (p_curr) {
      if (!p_curr->right) {
        delete p_curr;
        return p_curr->value;
      }
      p_curr = p_curr->right;
    }
  }

  T ExtractMax() {
    T max = GetMax();
    Delete(max);
    return max;
  }

  T ExtractMin() {
    T min = GetMin();
    Delete(min);
    return min;
  }

  size_t Size() {
    return size_;
  }
  T LowerBound(const T& value) {
    auto p_curr = root_;
    auto p_lowerbound = p_curr;
    if (!p_curr) {
      return -1;
    }
    while (p_curr) {
      if (p_curr->value < value) {
        p_curr = p_curr->right;
      } else {
        p_lowerbound = p_curr;
        p_curr = p_curr->left;
      }
    }
    T value1 = p_lowerbound->value;
    return (value1 >= value ? value1 : -1);
  }

 private:
  NodeAVL<T>* root_ = nullptr;
  size_t size_ = 0;

  static NodeAVL<T>* HelperInsert(NodeAVL<T>* p_node, const T& value) {
    if (!p_node) {
      return new NodeAVL<T>{nullptr, nullptr, 1, value};
    }
    if (p_node->value == value) {
      return p_node;
    }
    if (p_node->value < value) {
      p_node->right = HelperInsert(p_node->right, value);
    } else {
      p_node->left = HelperInsert(p_node->left, value);
    }
    return LocalBalance(p_node);
  }
  static NodeAVL<T>* RotateLeft(NodeAVL<T>* p_node) {
    auto p_child = p_node->right;
    p_node->right = p_child->left;
    p_child->left = p_node;
    SetHeight(p_node);
    SetHeight(p_child);
    return p_child;
  }
  static NodeAVL<T>* RotateRight(NodeAVL<T>* p_node) {
    auto p_child = p_node->left;
    p_node->left = p_child->right;
    p_child->right = p_node;
    SetHeight(p_node);
    SetHeight(p_child);
    return p_child;
  }
  static NodeAVL<T>* RotateBigLeft(NodeAVL<T>* p_node) {
    auto p_child = p_node->right;
    auto p_grandson = p_child->left;
    p_node->right = p_grandson->left;
    p_child->left = p_grandson->right;
    p_grandson->left = p_node;
    p_grandson->right = p_child;
    SetHeight(p_node);
    SetHeight(p_child);
    SetHeight(p_grandson);
    return p_grandson;
  }

  static NodeAVL<T>* RotateBigRight(NodeAVL<T>* p_node) {
    auto p_child = p_node->left;
    auto p_grandson = p_child->right;
    p_node->left = p_grandson->right;
    p_child->right = p_grandson->left;
    p_grandson->right = p_node;
    p_grandson->left = p_child;
    SetHeight(p_node);
    SetHeight(p_child);
    SetHeight(p_grandson);
    return p_grandson;
  }

  static void SetHeight(NodeAVL<T>* p_node) {
    p_node->height = 1 + Max(Height(p_node->left), Height(p_node->right));
  }

  static size_t Height(NodeAVL<T>* p_node) {
    return (p_node ? p_node->height : 0);
  }

  static int BalanceFactor(NodeAVL<T>* p_node) {
    return (Height(p_node->right) - Height(p_node->left));
  }

  static NodeAVL<T>* LocalBalance(NodeAVL<T>* p_node) {
    if (BalanceFactor(p_node) == 2) {
      if (BalanceFactor(p_node->right) == -1) {
        return RotateBigLeft(p_node);
      }
      return RotateLeft(p_node);
    }
    if (BalanceFactor(p_node) == -2) {
      if (BalanceFactor(p_node->left) == 1) {
        return RotateBigRight(p_node);
      }
      return RotateRight(p_node);
    }
    return p_node;
  }

  static NodeAVL<T>* HelperDelete(NodeAVL<T>* p_node, const T& value) {
    if (!p_node) {
      return nullptr;
    }

    if (p_node->value == value) {
      if (!p_node->left && !p_node->right) {
        delete p_node;
        return nullptr;
      }
      if (p_node->left) {
        p_node->left = RemoveOnLeft(p_node->left, p_node->value);
      }
      if (p_node->right) {
        p_node->right = RemoveOnRight(p_node->right, p_node->value);
      }
      return LocalBalance(p_node);
    }
    if (p_node->value < value) {
      p_node->right = HelperDelete(p_node->right, value);
    } else {
      p_node->left = HelperDelete(p_node->left, value);
    }
    return LocalBalance(p_node);
  }

  static NodeAVL<T>* RemoveOnLeft(NodeAVL<T>* p_node, T& new_value) {
    if (p_node->right) {
      p_node->right = RemoveOnLeft(p_node->right, new_value);
      return LocalBalance(p_node);
    }
    new_value = p_node->value;
    auto replacement = p_node->left;
    delete p_node;
    return replacement;
  }

  static NodeAVL<T>* RemoveOnRight(NodeAVL<T>* p_node, T& new_value) {
    if (p_node->left) {
      p_node->left = RemoveOnRight(p_node->left, new_value);
      return LocalBalance(p_node);
    }
    new_value = p_node->value;
    auto replacement = p_node->right;
    delete p_node;
    return replacement;
  }

  void HelperClear(NodeAVL<T>* p_node) {
    if (p_node) {
      HelperClear(p_node->left);
      HelperClear(p_node->right);
      delete p_node;
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  AVLTree<int> bst;
  char prev_char = '0';
  char p = '0';
  int prev_value = 0;
  int a = 0;
  for (int i = 0; i < n; ++i) {
    prev_char = p;
    std::cin >> p >> a;
    if (p == '+') {
      if (prev_char == '?') {
        int temp = (a + prev_value) % 1000000000;
        bst.Insert(temp);
      } else {
        bst.Insert(a);
      }
    }
    if (p == '?') {
      prev_value = bst.LowerBound(a);
      std::cout << prev_value << '\n';
    }
  }
  return 0;
}