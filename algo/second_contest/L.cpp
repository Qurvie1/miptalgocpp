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

  void PostOrderTraversal(NodeBST<T>* current) {
    if (current) {
      PostOrderTraversal(current->left);
      PostOrderTraversal(current->right);
      std::cout << current->value << ' ';
    }
  }

 public:
  ~BinarySearchTree() {
    HelperClear(root_);
  }
  BinarySearchTree(const T* begin, int size) {
    int i = 0;
    root_ = new NodeBST<T>{nullptr, nullptr, nullptr, begin[i++]};
    NodeBST<T>* p_prev = root_;
    NodeBST<T>* p_curr = root_;
    while (i < size) {
      while (i < size && begin[i] < begin[i - 1]) {
        p_prev = p_curr;
        p_curr->left = new NodeBST<T>{p_prev, nullptr, nullptr, begin[i++]};
        p_curr = p_curr->left;
      }
      if (i >= size) {
        break;
      }
      auto p_max = p_curr;
      while (p_curr && p_curr->value <= begin[i]) {
        if (p_curr && p_curr->value > p_max->value) {
          p_max = p_curr;
        }
        p_prev = p_curr;
        p_curr = p_curr->parent;
      }
      p_max->right = new NodeBST<T>{p_max, nullptr, nullptr, begin[i++]};
      p_curr = p_max->right;
    }
  }

  void PostOrderTraversalPublic() {
    PostOrderTraversal(root_);
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  auto a = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  BinarySearchTree<int> bst(a, n);
  bst.PostOrderTraversalPublic();
  delete[] a;
  return 0;
}