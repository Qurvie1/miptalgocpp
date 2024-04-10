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

  T* LeafTraversal(NodeBST<T>* current, T* ptr) {
    if (current) {
      ptr = LeafTraversal(current->left, ptr);
      if (current->left == nullptr && current->right == nullptr) {
        *(ptr++) = current->value;
      }
      ptr = LeafTraversal(current->right, ptr);
    }
    return ptr;
  }

 public:
  explicit BinarySearchTree(const T& value) {
    root_ = new NodeBST<T>{nullptr, nullptr, nullptr, value};
  }

  void InOrderLeafTraversal(T* sequence) {
    LeafTraversal(root_, sequence);
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
  auto array = new int[1000000]{};
  bst.InOrderLeafTraversal(array);
  int i = 0;
  while (array[i] != 0) {
    std::cout << array[i++] << ' ';
  }
  delete[] array;
  return 0;
}