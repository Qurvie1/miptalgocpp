#include <iostream>
#include <cstddef>
#include <cstring>

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
  size_t size;
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

  T ExtractMax() {
    NodeAVL<T>* p_curr = root_;
    NodeAVL<T>* p_prev = root_;
    if (!p_curr) {
      return -1;
    }
    while (p_curr) {
      p_prev = p_curr;
      p_curr = p_curr->right;
    }
    T value = p_prev->value;
    Delete(value);
    return value;
  }

  T ExtractMin() {
    NodeAVL<T>* p_curr = root_;
    NodeAVL<T>* p_prev = root_;
    if (!p_curr) {
      return -1;
    }
    while (p_curr) {
      p_prev = p_curr;
      p_curr = p_curr->left;
    }
    T value = p_prev->value;
    Delete(value);
    return value;
  }

  size_t Size() {
    return size_;
  }

  T ExtractMid() {
    return ExtractMidHelper(root_, (size_ % 2 == 1 ? size_ / 2 : (size_ - 1) / 2));
  }
  void ShowTree() {
    ShowTreeHelper(root_);
  }

 private:
  NodeAVL<T>* root_ = nullptr;
  size_t size_ = 0;

  void ShowTreeHelper(NodeAVL<T>* p_node) {
    if (!p_node) {
      return;
    }
    std::cout << p_node->value << ' ' << ':' << ' ' << p_node->size << ' ';
    ShowTreeHelper(p_node->left);
    ShowTreeHelper(p_node->right);
  }

  T ExtractMidHelper(NodeAVL<T>* p_node, size_t mid_number) {
    NodeAVL<T>* p_curr = p_node;
    if (!p_curr) {
      return -1;
    }
    if ((mid_number == 0 && !p_curr->left) || (p_curr->left && p_curr->left->size == mid_number)) {
      T value = p_curr->value;
      Delete(value);
      return value;
    }
    if (p_curr->left && p_curr->left->size > mid_number) {
      return ExtractMidHelper(p_curr->left, mid_number);
    }
    if (p_curr->right && (p_curr->left ? p_curr->left->size : 0) < mid_number) {
      return ExtractMidHelper(p_curr->right, mid_number - 1 - (p_curr->left ? p_curr->left->size : 0));
    }
    return -1;
  }

  static NodeAVL<T>* HelperInsert(NodeAVL<T>* p_node, const T& value) {
    if (!p_node) {
      return new NodeAVL<T>{nullptr, nullptr, static_cast<int>(1), value, static_cast<int>(1)};
    }
    if (p_node->value < value) {
      ++p_node->size;
      p_node->right = HelperInsert(p_node->right, value);
    } else {
      ++p_node->size;
      p_node->left = HelperInsert(p_node->left, value);
    }
    return LocalBalance(p_node);
  }
  static NodeAVL<T>* RotateLeft(NodeAVL<T>* p_node) {
    auto p_child = p_node->right;
    if (p_child) {
      p_child->size = p_node->size;
    }
    if (p_node) {
      p_node->size -= (p_child->right ? p_child->right->size : 0);
      p_node->size--;
    }
    p_node->right = p_child->left;
    p_child->left = p_node;
    SetHeight(p_node);
    SetHeight(p_child);
    return p_child;
  }
  static NodeAVL<T>* RotateRight(NodeAVL<T>* p_node) {
    auto p_child = p_node->left;
    if (p_child) {
      p_child->size = p_node->size;
    }
    if (p_node) {
      p_node->size -= (p_child->left ? p_child->left->size : 0);
      p_node->size--;
    }
    p_node->left = p_child->right;
    p_child->right = p_node;
    SetHeight(p_node);
    SetHeight(p_child);
    return p_child;
  }
  static NodeAVL<T>* RotateBigLeft(NodeAVL<T>* p_node) {
    auto p_child = p_node->right;
    auto p_grandson = p_child->left;
    p_grandson->size = p_node->size;
    if (p_grandson) {
      p_grandson->size = p_child->size;
    }
    if (p_child) {
      p_child->size -= (p_grandson->left ? p_grandson->left->size : 0);
      p_child->size--;
    }
    if (p_grandson) {
      p_grandson->size = p_node->size;
    }
    if (p_node) {
      p_node->size -= (p_grandson->right ? p_grandson->right->size : 0);
      p_node->size--;
    }
    p_node->left = p_child->right;
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
    if (p_grandson) {
      p_grandson->size = p_child->size;
    }
    if (p_child) {
      p_child->size -= (p_grandson->right ? p_grandson->right->size : 0);
      p_child->size--;
    }
    if (p_grandson) {
      p_grandson->size = p_node->size;
    }
    if (p_node) {
      p_node->size -= (p_grandson->left ? p_grandson->left->size : 0);
      p_node->size--;
    }
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

  size_t HelperSize(NodeAVL<T>* p_node) {
    if (!p_node) {
      return 0;
    }
    return 1 + HelperSize(p_node->right) + HelperSize(p_node->left);
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
        p_node->size--;
      } else {
        p_node->right = RemoveOnRight(p_node->right, p_node->value);
        p_node->size--;
      }
      return LocalBalance(p_node);
    }
    if (p_node->value < value) {
      --p_node->size;
      p_node->right = HelperDelete(p_node->right, value);
    } else {
      --p_node->size;
      p_node->left = HelperDelete(p_node->left, value);
    }
    return LocalBalance(p_node);
  }

  static NodeAVL<T>* RemoveOnLeft(NodeAVL<T>* p_node, T& new_value) {
    --p_node->size;
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
    --p_node->size;
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
  int m = 0;
  std::cin >> m;
  char s[10]{};
  AVLTree<int> bst;
  for (int i = 0; i < m; ++i) {
    std::cin >> s;
    if (!strcmp(s, "add")) {
      int a = 0;
      std::cin >> a;
      bst.Insert(a);
    }
    if (!strcmp(s, "mid")) {
      int temp = bst.ExtractMid();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "min")) {
      int temp = bst.ExtractMin();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
    if (!strcmp(s, "max")) {
      int temp = bst.ExtractMax();
      if (temp == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << temp << '\n';
      }
    }
  }
  return 0;
}