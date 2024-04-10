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
  int height_ = 0;
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

  ~BinarySearchTree() {
    HelperClear(root_);
  }

  void InsertElement(const T& value) {
    if (!root_) {
      root_ = new NodeBST<T>{nullptr, nullptr, nullptr, value};
      return;
    }
    auto p_curr = root_;
    int counter_height = 1;
    NodeBST<T>* p_prev = p_curr;
    while (p_curr) {
      p_prev = p_curr;
      p_curr = (p_curr->value < value ? p_curr->right : p_curr->left);
      ++counter_height;
    }
    height_ = (counter_height > height_ ? counter_height : height_);
    if (p_prev->value < value) {
      p_prev->right = new NodeBST<T>{p_prev, nullptr, nullptr, value};
    } else {
      p_prev->left = new NodeBST<T>{p_prev, nullptr, nullptr, value};
    }
  }
  int Height() {
    return height_;
  }
};

int main() {
  int a = 0;
  std::cin >> a;
  BinarySearchTree<int> bst(a);
  while (std::cin >> a && a) {
    bst.InsertElement(a);
  }
  std::cout << bst.Height();
  return 0;
}