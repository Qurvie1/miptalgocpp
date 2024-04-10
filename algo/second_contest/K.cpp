#include <iostream>

template <class T>
struct NodeBST {
  NodeBST<T>* parent;
  NodeBST<T>* left;
  NodeBST<T>* right;
  T value;
};

template <class T>
class BinarySearchTree {
 private:
  NodeBST<T>* root_ = nullptr;
  void HelperClear(NodeBST<T>* pnode) {
    if (pnode) {
      HelperClear(pnode->left);
      HelperClear(pnode->right);
      delete pnode;
    }
  }

 public:
  explicit BinarySearchTree(const T& value) {
    root_ = new NodeBST<T>{nullptr, nullptr, nullptr, value};
  }

  void InOrderTraversal() {
    NodeBST<T>* prev = nullptr;
    NodeBST<T>* p_node = root_;
    while (p_node) {
      if (prev == p_node->parent) {
        prev = p_node;
        if (p_node->left) {
          p_node = p_node->left;
        } else {
          std::cout << p_node->value << '\n';
          if (p_node->right) {
            p_node = p_node->right;
          } else {
            p_node = p_node->parent;
          }
        }
      } else if (prev == p_node->left) {
        prev = p_node;
        std::cout << p_node->value << '\n';
        if (p_node->right) {
          p_node = p_node->right;
        } else {
          p_node = p_node->parent;
        }
      } else if (prev == p_node->right) {
        prev = p_node;
        p_node = p_node->parent;
      }
    }
  }

  ~BinarySearchTree() {
    HelperClear(root_);
  }

  void InsertElement(const T& value) {
    if (!root_) {
      root_ = new NodeBST<T>{nullptr, nullptr, nullptr, value};
      return;
    }
    auto p_curr = root_;
    NodeBST<T>* p_prev = p_curr;
    while (p_curr) {
      p_prev = p_curr;
      if (p_curr->value == value) {
        return;
      }
      p_curr = (p_curr->value < value ? p_curr->right : p_curr->left);
    }
    if (p_prev->value < value) {
      p_prev->right = new NodeBST<T>{p_prev, nullptr, nullptr, value};
    } else if (p_prev->value > value) {
      p_prev->left = new NodeBST<T>{p_prev, nullptr, nullptr, value};
    } else {
      return;
    }
  }
};

int main() {
  int a = 0;
  std::cin >> a;
  BinarySearchTree<int> bst(a);
  while (std::cin >> a && a) {
    bst.InsertElement(a);
  }
  bst.InOrderTraversal();
  return 0;
}