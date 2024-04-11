#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <stdexcept>

class BadOptionalAccess : public std::runtime_error {
 public:
  BadOptionalAccess() : std::runtime_error("BadOptionalAccess") {
  }
};

template <class T>
class Optional {
 public:
  Optional() = default;

  bool HasValue() const {
    return has_value_;
  }

  operator bool() const {  // NOLINT
    return has_value_;
  }

  Optional(const T& other) : has_value_(true) {  // NOLINT
    new (mas_) T(other);
  }

  Optional(T&& other) : has_value_(true) {  // NOLINT
    new (mas_) T(std::move(other));
  }

  Optional(const Optional& other) {  // NOLINT
    if (other.HasValue()) {
      new (mas_) T(*other);
      has_value_ = true;
    }
  }

  Optional(Optional&& other) {
    if (other.HasValue()) {
      new (mas_) T(std::move(*other));
      has_value_ = true;
    }
  }

  ~Optional() {
    if (has_value_) {
      reinterpret_cast<T*>(mas_)->~T();
    }
  }

  Optional& operator=(const Optional& other) {
    if (*this == other) {
      return *this;
    }
    Reset();
    if (other.HasValue()) {
      new (mas_) T(*other);
      has_value_ = true;
    }
    return *this;
  }

  Optional& operator=(Optional&& other) {
    if (*this == other) {
      return *this;
    }
    Reset();
    if (other.HasValue()) {
      new (mas_) T(std::move(*other));
      has_value_ = true;
    }
    return *this;
  }

  Optional& operator=(const T& other) {
    Reset();
    new (mas_) T(other);
    has_value_ = true;
    return *this;
  }
  
  Optional& operator=(T&& other) {
    Reset();
    new (mas_) T(std::move(other));
    has_value_ = true;
    return *this;
  }

  T& operator*() {
    return *obj_;
  }

  const T& operator*() const {
    return *obj_;
  }

  template<typename... Args>
  void Emplace(Args&&... args) {
    if (has_value_) {
      reinterpret_cast<T*>(mas_)->~T();
    }
    new (mas_) T(std::forward<Args>(args)...);
    has_value_ = true;
  }

  void Reset() {
    if (has_value_) {
      reinterpret_cast<T*>(mas_)->~T();
    }
    has_value_ = false;
  }

  T& Value() {
    if (!has_value_) {
      throw BadOptionalAccess{};
    }
    return *obj_;
  }

  const T& Value() const {
    if (!has_value_) {
      throw BadOptionalAccess{};
    }
    return *obj_;
  }

  void Swap(Optional& other) {
    if (has_value_ && !other.has_value_) {
      other = std::move(*this);
      has_value_ = false;
      return;
    }
    if (!has_value_ && other.has_value_) {
      *this = std::move(other);
      other.has_value_ = false;
      return;
    }
    if (has_value_ && other.has_value_) {
      auto t = std::move(other.obj_);
      other.obj_ = std::move(this->obj_);
      this->obj_ = std::move(t);
    }
  }
 private:
  char mas_[sizeof(T)];
  T* obj_ = reinterpret_cast<T*>(mas_);
  bool has_value_ = false;
};

#endif