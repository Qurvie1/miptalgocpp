#ifndef ENUMERATE_H
#define ENUMERATE_H

#define TEMPORARY_ENUMERATE_IMPLEMENTED

template <typename T, bool IsConst>
class Wrapper {
 public:
  Wrapper(T& cont) : start_(cont.begin()), finish_(cont.end()) {}  // NOLINT

  using reference = typename std::pair<size_t, std::conditional_t<IsConst, typename T::const_reference, typename T::reference>>;  // NOLINT
  using const_reference = const typename std::pair<size_t, std::conditional_t<IsConst, typename T::const_reference, typename T::reference>>;  // NOLINT

  class Iterator {
   public:
    Iterator(std::conditional_t<IsConst, typename T::const_iterator, typename T::iterator&> it) : value_(it) {}  // NOLINT

    std::pair<size_t, std::conditional_t<IsConst, typename T::const_reference, typename T::reference>> operator*() {
      return {index_, *value_};
    }

    Iterator& operator++() {
      ++index_;
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
    std::conditional_t<IsConst, typename T::const_iterator, typename T::iterator&>  value_;
    size_t index_ = 0;
  };

  using iterator = Iterator;  // NOLINT
  using const_iterator = Iterator;  // NOLINT

  Iterator begin() {  // NOLINT
    return {start_};
  }

  Iterator end() {  // NOLINT
    return {finish_};
  }

  Iterator begin() const {  // NOLINT
    return {start_};
  }

  Iterator end() const {  // NOLINT
    return {finish_};
  }
 private:
  std::conditional_t<IsConst, typename T::const_iterator, typename T::iterator> start_;
  std::conditional_t<IsConst, typename T::const_iterator, typename T::iterator> finish_;
};

template <class T>
class RvalueWrapper {
 public:
  RvalueWrapper(T&& cont) : cont_(std::move(cont)) {}  // NOLINT

  using reference = typename std::pair<size_t, typename T::reference>;  // NOLINT
  using const_reference = const typename std::pair<size_t, typename T::const_reference>;  // NOLINT

  class Iterator {
   public:
    Iterator(typename T::iterator it) : value_(it) {}  // NOLINT

    std::pair<size_t, typename T::reference> operator*() {
      return {index_, *value_};
    }

    Iterator& operator++() {
      ++index_;
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
    typename T::iterator value_;
    size_t index_ = 0;
  };

  class ConstIterator {
   public:
    ConstIterator(typename T::const_iterator it) : value_(it) {}  // NOLINT

    std::pair<size_t, typename T::const_reference> operator*() {
      return {index_, *value_};
    }

    ConstIterator& operator++() {
      ++index_;
      ++value_;
      return *this;
    }

    bool operator==(const ConstIterator& other) const noexcept {
      return (value_ == other.value_);
    }

    bool operator!=(const ConstIterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    typename T::const_iterator value_;
    size_t index_ = 0;
  };

  using iterator = Iterator;  // NOLINT
  using const_iterator = ConstIterator;  // NOLINT

  Iterator begin() {  // NOLINT
    return Iterator(cont_.begin());
  }

  Iterator end() {  // NOLINT
    return Iterator(cont_.end());
  }

  ConstIterator begin() const {  // NOLINT
    return ConstIterator(cont_.begin());
  }

  ConstIterator end() const {  // NOLINT
    return ConstIterator(cont_.end());
  }

 private:
  T cont_;
};

template <class T, typename = std::enable_if_t<!std::is_lvalue_reference<T>()>>
RvalueWrapper<T> Enumerate(T&& val) {
  return RvalueWrapper(std::forward<T>(val));
}

template <class T>
Wrapper<T, std::is_const_v<T>> Enumerate(T& val) {
  return Wrapper<T, std::is_const_v<T>>(val);
}

#endif