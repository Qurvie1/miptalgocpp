#include <stdexcept>

#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#define WEAK_PTR_IMPLEMENTED

#define MAKE_SHARED_IMPLEMENTED

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

struct Counter {
  size_t strong_count;
  size_t weak_count;
};

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
 public:
  SharedPtr() : ptr_(nullptr), counter_(nullptr){};

  SharedPtr(T* ptr) : ptr_(ptr), counter_(ptr != nullptr ? new Counter{1, 0} : nullptr){};  // NOLINT

  SharedPtr(T* ptr, Counter* counter) : ptr_(ptr), counter_(counter){};

  SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (counter_) {
      ++(counter_->strong_count);
    }
  }
  
  SharedPtr(const WeakPtr<T>& other) {  // NOLINT
    if (other.Expired()) {
      throw BadWeakPtr{};
    }
    ptr_ = other.Get();
    counter_ = other.GetCount();
    if (counter_) {
      ++(counter_->strong_count);
    }
  }

  SharedPtr(SharedPtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
    if (other.ptr_ != ptr_) {
      if (counter_) {
        --(counter_->strong_count);
        CounterCheck();
      }
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }

  SharedPtr<T>& operator=(const SharedPtr<T>& other) {
    if (ptr_ == other.ptr_) {
      return *this;
    }
    if (counter_) {
      --(counter_->strong_count);
      CounterCheck();
    }
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      ++(counter_->strong_count);
    }
    return *this;
  }

  T* Get() {
    return ptr_;
  }

  T* Get() const {
    return ptr_;
  }

  T* operator->() {
    return ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  T& operator*() {
    return *ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  size_t UseCount() const {
    return (counter_ == nullptr ? 0 : counter_->strong_count);
  }

  ~SharedPtr() {
    if (counter_) {
      --(counter_->strong_count);
    }
    CounterCheck();
  }

  void Swap(SharedPtr<T>& other) {
    Counter* tcount = other.counter_;
    T* tptr = other.ptr_;
    other.counter_ = counter_;
    other.ptr_ = ptr_;
    counter_ = tcount;
    ptr_ = tptr;
  }

  void Reset(T* ptr = nullptr) {
    if (ptr == ptr_) {
      return;
    }
    if (counter_ != nullptr) {
      --(counter_->strong_count);
      CounterCheck();
    }
    ptr_ = ptr;
    counter_ = (ptr != nullptr ? new Counter{1, 0} : nullptr);
  }

  Counter* GetCounter() const {
    return counter_;
  }

 private:
  T* ptr_;
  Counter* counter_;
  void CounterCheck() {
    if (!counter_) {
      return;
    }
    if (counter_->strong_count == 0) {
      if (ptr_ && counter_->weak_count == 0) {
        delete ptr_;
        delete counter_;
      } else {
        delete ptr_;
      }
    }
  }
};

template <class T>
class WeakPtr {
 public:
  WeakPtr() : ptr_(nullptr), counter_(nullptr){}

  WeakPtr(const WeakPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (counter_) {
      ++(counter_->weak_count);
    }
  }

  WeakPtr(const SharedPtr<T>& other) : ptr_(other.Get()), counter_(other.GetCounter()) {  // NOLINT
    if (counter_) {
      ++(counter_->weak_count);
    }
  }

  WeakPtr(WeakPtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  ~WeakPtr() {
    if (counter_) {
      --(counter_->weak_count);
    }
    CounterCheck();
  }

  WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept {
    if (other.ptr_ != ptr_) {
      ptr_ = other.ptr_;
      if (counter_) {
        --(counter_->weak_count);
        CounterCheck();
      }
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }

  WeakPtr<T>& operator=(const WeakPtr<T>& other) {
    if (ptr_ != other.ptr_) {
      ptr_ = other.ptr_;
      if (counter_) {
        --(counter_->weak_count);
        CounterCheck();
      }
      counter_ = other.counter_;
      if (counter_) {
        ++(counter_->weak_count);
      }
    }
    return *this;
  }

  void Swap(WeakPtr<T>& other) {
    Counter* tcount = other.counter_;
    T* tptr = other.ptr_;
    other.counter_ = counter_;
    other.ptr_ = ptr_;
    counter_ = tcount;
    ptr_ = tptr;
  }

  void Reset() {
    ptr_ = nullptr;
    if (counter_ != nullptr) {
      --(counter_->weak_count);
      CounterCheck();
    }
    counter_ = nullptr;
  }

  size_t UseCount() const {
    return (counter_ != nullptr ? counter_->strong_count : 0);
  }

  bool Expired() const {
    return (counter_ == nullptr ? true : counter_->strong_count == 0);
  }

  T* Get() const {
    return ptr_;
  }

  Counter* GetCount() const {
    return counter_;
  }

  SharedPtr<T> Lock() const {
    if (Expired()) {
      return nullptr;
    }
    SharedPtr<T> ptr(ptr_, counter_);
    ++(counter_->strong_count);
    return ptr;
  }
  
 private:
  T* ptr_;
  Counter* counter_;
  void CounterCheck() {
    if (!counter_) {
      return;
    }
    if (counter_ ->weak_count == 0 && counter_->strong_count == 0) {
      delete counter_;
    }
  }
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif