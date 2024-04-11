#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_MEMORY_IMPLEMENTED

#include <compare>
#include <exception>
#include <iterator>
#include <memory>

template <class T>
void SwapHelp(T& first, T& second) {
  auto temp = std::move(first);
  first = std::move(second);
  second = std::move(temp);
}

template <class T>
class Vector {
 public:
  Vector() noexcept : cont_(nullptr), sz_(0ul), cap_(0ul) {}

  explicit Vector(size_t count) : cont_(nullptr), sz_(count), cap_(count) {
    try {
      cont_ = (count > 0 ? reinterpret_cast<T*>(new char[sz_ * sizeof(T)]) : nullptr);
      std::uninitialized_default_construct(cont_, cont_ + sz_);
    } catch (...) {
      delete[] reinterpret_cast<char*>(cont_);
      throw;
    }
    
  }

  Vector(size_t count, const T& value) : cont_(nullptr), sz_(count), cap_(count) {
    try {
      cont_ = (count > 0 ? reinterpret_cast<T*>(new char[sz_ * sizeof(T)]) : nullptr);
      std::uninitialized_fill(cont_, cont_ + sz_, value);
    } catch (...) {
      delete[] reinterpret_cast<char*>(cont_);
      throw;
    }
  }

  template <typename FIterator, typename = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<FIterator>::iterator_category>>>
  Vector(FIterator first, FIterator last) : cont_(nullptr), sz_(std::distance(first, last)), cap_(sz_) {
    try {
      cont_ = (sz_ > 0 ? reinterpret_cast<T*>(new char[sz_ * sizeof(T)]) : nullptr);
      std::uninitialized_copy(first, last, cont_);
    } catch (...) {
      delete[] reinterpret_cast<char*>(cont_);
      throw;
    }
  }

  Vector(std::initializer_list<T> init) : cont_(nullptr), sz_(init.size()), cap_(init.size()) {
    try {
      cont_ = reinterpret_cast<T*>(new char[sz_ * sizeof(T)]);
      std::uninitialized_copy(init.begin(), init.end(), cont_);
    } catch (...) {
      delete[] reinterpret_cast<char*>(cont_);
      throw;
    }
  }

  Vector(const Vector& other) : cont_(nullptr), sz_(other.sz_), cap_(other.cap_) {
    try {
      cont_ = (other.cap_ > 0 ? reinterpret_cast<T*>(new char[other.cap_ * sizeof(T)]) : nullptr);
      std::uninitialized_copy(other.cont_, other.cont_ + sz_, cont_);
    } catch (...) {
      delete[] reinterpret_cast<char*>(cont_);
      throw;
    }
  }

  Vector(Vector&& other) noexcept : cont_(other.cont_), sz_(other.sz_), cap_(other.cap_) {
    other.cap_ = 0ul;
    other.sz_ = 0ul;
    other.cont_ = nullptr;
  }

  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }
    T* newarr = (other.cap_ > 0 ? reinterpret_cast<T*>(new char[other.cap_ * sizeof(T)]) : nullptr);
    size_t i = 0;
    try {
      for (; i < other.sz_; ++i) {
        new (newarr + i) T(other[i]);
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (newarr + j)->~T();
      }
      delete[] reinterpret_cast<char*>(newarr);
      throw;
    }
    for (size_t i = 0; i < sz_; ++i) {
      (cont_ + i)->~T();
    }
    delete[] reinterpret_cast<char*>(cont_);
    cont_ = newarr;
    sz_ = other.sz_;
    cap_ = other.cap_;
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    for (size_t i = 0; i < sz_; ++i) {
      (cont_ + i)->~T();
    }
    delete[] reinterpret_cast<char*>(cont_);
    cont_ = other.cont_;
    sz_ = other.sz_;
    cap_ = other.cap_;
    other.cont_ = nullptr;
    other.cap_ = 0ul;
    other.sz_ = 0ul;
    return *this;
  }

  ~Vector() {
    Clear();
    if (cap_) {
      delete[] reinterpret_cast<char*>(cont_);
    }
  }

  template <bool IsConst>
  class BaseIterator {
   public:
    using value_type = T;  // NOLINT
    using difference_type = size_t;  // NOLINT
    using reference = std::conditional_t<IsConst, const T&, T&>;  // NOLINT
    using pointer = std::conditional_t<IsConst, const T&, T&>;  // NOLINT
    using iterator_category = std::random_access_iterator_tag;  // NOLINT
    BaseIterator(const BaseIterator&) = default;
    BaseIterator& operator=(const BaseIterator&) = default;
  
    std::conditional_t<IsConst, const T&, T&> operator*() const {
      return *ptr_;
    }

    BaseIterator& operator++() {
      ++ptr_;
      return *this;
    }

    BaseIterator operator++(int) {
      BaseIterator copy = *this;
      ++ptr_;
      return copy;
    }

    BaseIterator operator--() {
      --ptr_;
      return *this;
    }

    template <class U>
    BaseIterator operator+(const U& value) const {
      return ptr_ + value;
    }
    
    template <class U>
    BaseIterator operator-(const U& value) const {
      return ptr_ - value;
    }

    BaseIterator operator--(int) {
      BaseIterator copy = *this;
      --ptr_;
      return copy;
    }

    std::conditional_t<IsConst, const T*, T*> operator->() {
      return ptr_;
    }

    bool operator==(const BaseIterator& other) const noexcept {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const BaseIterator& other) const noexcept {
      return !(*this == other);
    }

    BaseIterator(T* ptr) : ptr_(ptr) {}  // NOLINT
  
   private:  
    std::conditional_t<IsConst, const T*, T*> ptr_;
  };

  using Iterator = BaseIterator<false>;
  using ConstIterator = BaseIterator<true>;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  using ValueType = T;
  using Pointer = T*;
  using Reference = T&;
  using ConstPointer = const T*;
  using ConstReference = const T&;
  using SizeType = size_t;

  Iterator begin() noexcept {  // NOLINT
    return Iterator{cont_};
  }

  Iterator end() noexcept {  // NOLINT
    return Iterator{cont_ + sz_};
  }

  ConstIterator begin() const noexcept {  // NOLINT
    return ConstIterator{cont_};
  }

  ConstIterator end() const noexcept {  // NOLINT
    return ConstIterator{cont_ + sz_};
  }

  ConstIterator cbegin() const noexcept {  // NOLINT
    return ConstIterator{cont_};
  }

  ConstIterator cend() const noexcept {  // NOLINT
    return ConstIterator{cont_ + sz_};
  }

  ReverseIterator rbegin() noexcept {  // NOLINT
    return ReverseIterator{cont_ + sz_};
  }

  ReverseIterator rend() noexcept {  // NOLINT
    return ReverseIterator{cont_};
  }

  ConstReverseIterator rbegin() const noexcept {  // NOLINT
    return ConstReverseIterator{cont_ + sz_};
  }

  ConstReverseIterator rend() const noexcept {  // NOLINT
    return ConstReverseIterator{cont_};
  }

  ConstReverseIterator crbegin() const noexcept {  // NOLINT
    return ConstReverseIterator{cont_ + sz_};
  }

  ConstReverseIterator crend() const noexcept {  // NOLINT
    return ConstReverseIterator{cont_};
  }

  template <typename... Args>
  void EmplaceBack(Args&&... args) {
    if (sz_ == cap_) {
      ConstructReserve(cap_ > 0 ? cap_ * 2 : 1, 1, std::forward<Args>(args)...);
      ++sz_;
    } else {
      try {
        new (cont_ + sz_) T(std::forward<Args>(args)...);
        ++sz_;
      } catch (...) {
        throw;
      }
    }
  }

  void PushBack(const T& value) {
    EmplaceBack(value);
  }

  T& Front() {
    return *cont_;
  }

  const T& Front() const {
    return *cont_;
  }

  T& Back() {
    return *(cont_ + sz_ - 1);
  }

  const T& Back() const {
    return *(cont_ + sz_ - 1);
  }

  T* Data() {
    return cont_;
  }

  const T* Data() const noexcept {
    return cont_;
  }

  void Swap(Vector& other) noexcept {
    SwapHelp(cont_, other.cont_);
    SwapHelp(sz_, other.sz_);
    SwapHelp(cap_, other.cap_);
  }

  void Resize(size_t newsize) {
    if (cap_ < newsize) {
      ConstructReserve(newsize, newsize - sz_);
      sz_ = newsize;
      return;
    }
    if (newsize < sz_) {
      while (sz_ != newsize) {
        PopBack();
      }
    } else {
      while (sz_ < newsize) {
        EmplaceBack();
      }
    }
  }

  void Resize(size_t newsize, const T& value) {
     if (cap_ < newsize) {
      ConstructReserve(newsize, newsize - sz_, value);
      sz_ = newsize;
      return;
    }
    if (newsize < sz_) {
      while (sz_ != newsize) {
        PopBack();
      }
    } else {
      while (sz_ < newsize) {
        EmplaceBack(value);
      }
    }
  }

  void ShrinkToFit() {
    ChangeCap(sz_);
  }

  bool operator==(const Vector& other) const {
    if (sz_ != other.sz_) {
      return false;
    }
    for (size_t i = 0; i < sz_; ++i) {
      if (cont_[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  std::weak_ordering operator<=>(const Vector& other) const noexcept {
    size_t minsize = std::min(sz_, other.sz_);
    for (size_t i = 0; i < minsize; ++i) {
      std::weak_ordering comp = cont_[i] <=> other[i];
      if (comp != nullptr) {
        return comp;
      }
    }
    return sz_ <=> other.sz_;
  }

  size_t Size() const noexcept {
    return sz_;
  }

  size_t Capacity() const noexcept {
    return cap_;
  }

  size_t Empty() const noexcept {
    return sz_ == 0;
  }

  void Clear() noexcept {
    for (size_t i = 0; i < sz_; ++i) {
      (cont_ + i)->~T();
    }
    sz_ = 0;
  }

  T& operator[](size_t index) noexcept {
    return cont_[index];
  }

  const T& operator[](size_t index) const noexcept {
    return cont_[index];
  }

  T& At(size_t index) {
    if (index >= sz_) {
      throw std::out_of_range("Out of range");
    }
    return cont_[index];
  }

  const T& At(size_t index) const {
    if (index >= sz_) {
      throw std::out_of_range("Out of range");
    }
    return cont_[index];
  }

  void PushBack(T&& value) {
    EmplaceBack(std::move(value));
  }

  void PopBack() noexcept {
    (cont_ + sz_ - 1)->~T();
    --sz_;
  }

  void Reserve(size_t newcap) {
    if (newcap <= cap_) {
      return;
    }
    ChangeCap(newcap);
  }
 private:
  template <typename... Args>
  void ConstructReserve(size_t newcap, size_t number, Args&&... args) {
    if (newcap <= cap_) {
      return;
    }
    T* newarr = reinterpret_cast<T*>(new char[newcap * sizeof(T)]);
    size_t index1 = 0;
    size_t index2 = 0;
    try {
      for (; index2 < number; ++index2) {
        new (newarr + sz_ + index2) T(std::forward<Args>(args)...);
      }
      for (; index1 < sz_; ++index1) {
        new (newarr + index1) T(std::move_if_noexcept(cont_[index1]));
      }
      for (size_t index = 0; index < sz_; ++index) {
        (cont_ + index)->~T();
      }
      delete[] reinterpret_cast<char*>(cont_);
      cont_ = newarr;
      cap_ = newcap;
    } catch (...) {
      for (size_t i = 0; i < index1; ++i) {
        (newarr + i)->~T();
      }
      for (size_t i = 0; i < index2; ++i) {
        (newarr + sz_ + i)->~T();
      }
      delete[] reinterpret_cast<char*>(newarr);
      throw;
    }
  }

  void ChangeCap(size_t newcap) {
    T* newarr = (newcap > 0 ? reinterpret_cast<T*>(new char[newcap * sizeof(T)]) : nullptr);
    size_t index = 0;
    try {
      for (; index < sz_; ++index) {
        new (newarr + index) T(std::move_if_noexcept(cont_[index]));
      }
    } catch (...) {
      for (size_t i = 0; i < index; ++i) {
        (newarr + i)->~T();
      }
      delete[] reinterpret_cast<char*>(newarr);
      throw;
    }
    for (size_t index = 0; index < sz_; ++index) {
      (cont_ + index)->~T();
    }
    delete[] reinterpret_cast<char*>(cont_);
    cont_ = newarr;
    cap_ = newcap;
  }

  T* cont_;
  size_t sz_;
  size_t cap_;
};

#endif