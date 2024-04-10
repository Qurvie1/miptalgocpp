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

  NodeBST<T>* PremaxHelper(NodeBST<T>* root) {
    if (root->right == nullptr) {
      return root;
    }
    return PremaxHelper(root->right);
  }

 public:
  explicit BinarySearchTree(const T& value) {
    root_ = new NodeBST<T>{nullptr, nullptr, nullptr, value};
  }

  ~BinarySearchTree() {
    HelperClear(root_);
  }

  T FindPremax() {
    NodeBST<T>* max = PremaxHelper(root_);
    if (max->left) {
      auto operand = max->left;
      while (operand->right) {
        operand = operand->right;
      }
      if (max->parent) {
        return (operand->value < max->parent->value ? max->parent->value : operand->value);
      }
      return operand->value;
    }
    return (max->parent->value);
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
      p_curr = (p_curr->value < value ? p_curr->right : p_curr->left);
    }
    if (p_prev->value < value) {
      p_prev->right = new NodeBST<T>{p_prev, nullptr, nullptr, value};
    } else {
      p_prev->left = new NodeBST<T>{p_prev, nullptr, nullptr, value};
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
  std::cout << bst.FindPremax();
  return 0;
}