#ifndef REVERSED_H
#define REVERSED_H

#define REVERSE_REVERSED_IMPLEMENTED

#define TEMPORARY_REVERSED_IMPLEMENTED

#include <iostream>
#include <vector>
#include <array>

template <typename T>
struct Mock {
 public:
  template <typename C>
  static auto check(int) -> decltype(std::declval<C>().ConstV(), std::true_type{});  // NOLINT
    
  template <typename>
  static std::false_type check(...);  // NOLINT

  static constexpr bool value = decltype(Mock<T>::check<T>(0))::value;  // NOLINT
};

template <typename T, bool IsConst>
class Wrapper {
 public:
  Wrapper(T& cont) : startr_(cont.rbegin()), finishr_(cont.rend()), start_(cont.begin()), finish_(cont.end()) {}  // NOLINT

  template <bool RevConst>
  class ReverseIterator {
   public:
    ReverseIterator(std::conditional_t<RevConst, typename T::const_iterator, typename T::iterator> it) : value_(it) {}  // NOLINT

    std::conditional_t<RevConst, typename T::const_reference, typename T::reference> operator*() {
      return *value_;
    }

    ReverseIterator& operator++() {
      ++value_;
      return *this;
    }

    bool operator==(const ReverseIterator& other) const noexcept {
      return (value_ == other.value_);
    }

    bool operator!=(const ReverseIterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    std::conditional_t<RevConst, typename T::const_iterator, typename T::iterator>  value_;
  };

  template <bool ItConst>
  class Iterator {
   public:
    Iterator(std::conditional_t<ItConst, typename T::const_reverse_iterator, typename T::reverse_iterator> it) : value_(it) {}  // NOLINT

    std::conditional_t<ItConst, typename T::const_reference, typename T::reference> operator*() {
      return *value_;
    }

    Iterator& operator++() {
      ++value_;
      return *this;
    }

    bool operator==(const Iterator& other) const noexcept {
      return (value_ == other.value_);
    }

    bool operator!=(const Iterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    std::conditional_t<ItConst, typename T::const_reverse_iterator, typename T::reverse_iterator>  value_;
  };

  using iterator = Iterator<IsConst>;  // NOLINT
  using const_iterator = Iterator<true>;  // NOLINT
  using reverse_iterator = ReverseIterator<IsConst>;  // NOLINT
  using const_reverse_iterator = ReverseIterator<true>;  // NOLINT
  using reference = typename T::reference;  // NOLINT
  using const_reference = typename T::const_reference;  // NOLINT

  iterator begin() {  // NOLINT
    return {startr_};
  }

  iterator end() {  // NOLINT
    return {finishr_};
  }

  iterator begin() const {  // NOLINT
    return {startr_};
  }

  iterator end() const {  // NOLINT
    return {finishr_};
  }

  reverse_iterator rbegin() {  // NOLINT
    return {start_};
  }

  reverse_iterator rend() {  // NOLINT
    return {finish_};
  }

  reverse_iterator rbegin() const {  // NOLINT
    return {start_};
  }

  reverse_iterator rend() const {  // NOLINT
    return {finish_};
  }

  bool ConstV() const {
    return IsConst;
  }

 private:
  std::conditional_t<IsConst, typename T::const_reverse_iterator, typename T::reverse_iterator> startr_;
  std::conditional_t<IsConst, typename T::const_reverse_iterator, typename T::reverse_iterator> finishr_;
  std::conditional_t<IsConst, typename T::const_iterator, typename T::iterator> start_;
  std::conditional_t<IsConst, typename T::const_iterator, typename T::iterator> finish_;
};

template <class T>
class RvalueWrapper {
 public:
  RvalueWrapper(T&& cont) : cont_(std::move(cont)) {}  // NOLINT

  template <bool ReverseConst>
  class ReverseIterator {
   public:
    ReverseIterator(std::conditional_t<ReverseConst, typename T::const_iterator, typename T::iterator> it) : value_(it) {}  // NOLINT

    std::conditional_t<ReverseConst, typename T::const_reference, typename T::reference> operator*() {
      return *value_;
    }

    ReverseIterator& operator++() {
      ++value_;
      return *this;
    }

    bool operator==(const ReverseIterator& other) const noexcept {
      return (value_ == other.value_);
    }

    bool operator!=(const ReverseIterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    std::conditional_t<ReverseConst, typename T::const_iterator, typename T::iterator>  value_;
  };

  template <bool BaseConst>
  class Iterator {
   public:
    Iterator(std::conditional_t<BaseConst, typename T::const_reverse_iterator, typename T::reverse_iterator> it) : value_(it) {}  // NOLINT

    std::conditional_t<BaseConst, typename T::const_reference, typename T::reference> operator*() {
      return *value_;
    }

    Iterator& operator++() {
      ++value_;
      return *this;
    }

    bool operator==(const Iterator& other) const noexcept {
      return (value_ == other.value_);
    }

    bool operator!=(const Iterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    std::conditional_t<BaseConst, typename T::const_reverse_iterator, typename T::reverse_iterator>  value_;
  };

  using iterator = Iterator<!(Mock<T>::value && !std::is_same_v<typename T::const_iterator, typename T::iterator>)>;  // NOLINT
  using const_iterator = Iterator<true>;  // NOLINT
  using reverse_iterator = ReverseIterator<!(Mock<T>::value && !std::is_same_v<typename T::const_reverse_iterator, typename T::reverse_iterator>)>;  // NOLINT
  using const_reverse_iterator = ReverseIterator<true>;  // NOLINT
  using reference = typename T::reference;  // NOLINT
  using const_reference = typename T::const_reference;  // NOLINT

  iterator begin() {  // NOLINT
    return iterator(cont_.rbegin());
  }

  iterator end() {  // NOLINT
    return iterator(cont_.rend());
  }

  iterator begin() const {  // NOLINT
    return iterator(cont_.rbegin());
  }

  iterator end() const {  // NOLINT
    return iterator(cont_.rend());
  }

  reverse_iterator rbegin() {  // NOLINT
    return reverse_iterator(cont_.begin());
  }

  reverse_iterator rend() {  // NOLINT
    return reverse_iterator(cont_.end());
  }
  
  reverse_iterator rbegin() const {  // NOLINT
    return reverse_iterator(cont_.begin());
  }

  reverse_iterator rend() const {  // NOLINT
    return reverse_iterator(cont_.end());
  }

 private:
  T cont_;
};

template <class T, typename = std::enable_if_t<!std::is_lvalue_reference<T>()>>
RvalueWrapper<T> Reversed(T&& val) {
  return RvalueWrapper<T>(std::forward<T>(val));
}

template <class T>
Wrapper<T, std::is_const_v<T>> Reversed(T& val) {
  return Wrapper<T, std::is_const_v<T>>(val);
}

#endif