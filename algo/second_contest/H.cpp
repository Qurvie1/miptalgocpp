#include <iostream>

template <class T>
struct NodeSplay {
  NodeSplay<T>* parent;
  NodeSplay<T>* left;
  NodeSplay<T>* right;
  T value;
};

template <class T>
class SplayTree {
 public:
  SplayTree() : root_(nullptr) {
  }
  ~SplayTree() {
    Clear();
  }

  void Insert(const T& value) {
    if (!root_) {
      root_ = new NodeSplay<T>{nullptr, nullptr, nullptr, value};
      return;
    }
    auto p_closest = FindClosest(value);
    root_ = Splay(p_closest);

    if (p_closest->value == value) {
      return;
    }

    auto p_left = p_closest->left;
    auto p_right = p_closest->right;
    if (p_closest->value < value) {
      p_left = p_closest;
      p_left->right = nullptr;
    } else {
      p_right = p_closest;
      p_right->left = nullptr;
    }

    root_ = new NodeSplay<T>{nullptr, p_left, p_right, value};
    if (p_left) {
      p_left->parent = root_;
    }
    if (p_right) {
      p_right->parent = root_;
    }
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

  void Clear() {
    HelperClear(root_);
  }

 private:
  NodeSplay<T>* root_ = nullptr;
  NodeSplay<T>* Splay(NodeSplay<T>* p_node) {
    while (p_node->parent) {
      auto p_parent = p_node->parent;
      auto p_grandparent = p_parent->parent;

      if (p_grandparent == nullptr) {
        Rotate(p_node);
        return p_node;
      }

      if ((p_grandparent->left == p_parent && p_parent->left == p_node) ||
          (p_grandparent->right == p_parent && p_parent->right == p_node)) {
        Rotate(p_parent);
        Rotate(p_node);
      } else {
        Rotate(p_node);
        Rotate(p_node);
      }
    }
    return p_node;
  }

  NodeSplay<T>* FindClosest(const T& value) {
    NodeSplay<T>* p_prev = nullptr;
    NodeSplay<T>* p_curr = root_;
    while (p_curr) {
      if (p_curr->value == value) {
        return p_curr;
      }
      p_prev = p_curr;
      p_curr = (p_curr->value > value ? p_curr->left : p_curr->right);
    }
    return p_prev;
  }

  void Rotate(NodeSplay<T>* p_node) {
    auto p_parent = p_node->parent;

    if (p_parent->left == p_node) {
      p_parent->left = p_node->right;
      p_node->right = p_parent;
      if (p_parent->left) {
        p_parent->left->parent = p_parent;
      }
    } else {
      p_parent->right = p_node->left;
      p_node->left = p_parent;
      if (p_parent->right) {
        p_parent->right->parent = p_parent;
      }
    }

    p_node->parent = p_parent->parent;
    p_parent->parent = p_node;

    if (p_node->parent) {
      if (p_node->parent->left == p_parent) {
        p_node->parent->left = p_node;
      } else {
        p_node->parent->right = p_node;
      }
    }
  }

  void HelperClear(NodeSplay<T>* p_node) {
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
  SplayTree<int> bst;
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