#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#define MAKE_UNIQUE_IMPLEMENTED

template <typename T>
class UniquePtr {
 public:
  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  }

  UniquePtr(const UniquePtr<T>&) = delete;

  UniquePtr& operator=(const UniquePtr<T>&) = delete;

  UniquePtr(UniquePtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr<T>&& other) noexcept {
    if (other.ptr_ != ptr_) {
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T& operator*() {
    return *ptr_;
  }

  T* operator->() {
    return ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  T* Get() {
    return ptr_;
  }

  T* Get() const {
    return ptr_;
  }

  T* Release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }

  void Swap(UniquePtr& other) {
    if (ptr_ == other.ptr_) {
      return;
    }
    T* tptr = other.ptr_;
    other.ptr_ = ptr_;
    ptr_ = tptr;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T* ptr_;
};

template <typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&&... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
