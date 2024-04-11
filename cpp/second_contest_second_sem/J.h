#ifndef STACK_H
#define STACK_H

#include <deque>

template <class T, class Container = std::deque<T>>
class Stack {
 public:
  explicit Stack(const Container& cont) {
    cont_ = cont;
  }

  template <class InputIt>
  Stack(InputIt begin, InputIt end) : cont_(begin, end) {
  }

  Stack() = default;

  T& Top() {
    return cont_.back();
  }

  const T& Top() const {
    return cont_.back();
  }

  size_t Size() const {
    return cont_.size();
  }

  bool Empty() const {
    return cont_.empty();
  }

  void Push(const T& val) {
    cont_.push_back(val);
  }

  void Push(T&& val) {
    cont_.push_back(std::move(val));
  }

  void Pop() {
    cont_.pop_back();
  }

  template <typename... Args>
  void Emplace(Args&&... args) {
    cont_.emplace_back(std::forward<Args>(args)...);
  }

  void Swap(Stack& st) {
    cont_.swap(st.cont_);
  }
 private:
  Container cont_;
};

#endif