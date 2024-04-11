#include <stdexcept>

#ifndef ANY_H
#define ANY_H

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class Any {
 public:
  Any() : base_(nullptr) {}

  template <class T>
  Any(const T& object) : base_(new AnyHolder<T>(object)) {}  // NOLINT

  template <class T>
  auto& operator=(const T& object);

  template <class T>
  friend T AnyCast(const Any& any);

  ~Any() {
    delete base_;
  }

  Any(const Any& other) : base_(other.base_->Clone()) {}

  Any(Any&& other) {
    base_ = other.base_;
    other.base_ = nullptr;
  }

  auto& operator=(Any&& other) {
    if (base_ == other.base_) {
      return *this;
    }
    delete base_;
    base_ = other.base_;
    other.base_ = nullptr;
    return *this;
  }

  auto& operator=(const Any& other) {
    if (base_ == other.base_) {
      return *this;
    }
    delete base_;
    base_ = other.base_->Clone();
    return *this;
  }

  void Reset() {
    delete base_;
    base_ = nullptr;
  }

  bool HasValue() const {
    return base_ != nullptr;
  }

  void Swap(Any& other) {
    IHolder* temp = other.base_;
    other.base_ = base_;
    base_ = temp;
  }

 private:

  struct IHolder {
    virtual ~IHolder() = default;
    virtual IHolder* Clone() = 0;
  };

  template <class T>
  struct AnyHolder : public IHolder {
    T value;
    AnyHolder(const T& value) : value(value) {}  // NOLINT
    IHolder* Clone() override {
      return new AnyHolder<T>(value);
    }
  };

  IHolder* base_;
};

template <class T>
T AnyCast(const Any& any) {
  try {
    return dynamic_cast<Any::AnyHolder<T>&>(*any.base_).value;
  } catch (...) {
    throw BadAnyCast();
  }
}

template <class T>
auto& Any::operator=(const T& object) {
  try {
    if (AnyCast<T>(*this) == object) {
      return *this;
    }
  } catch (...) {
  }
  delete base_;
  base_ = new AnyHolder<T>(object);
  return *this;
}

#endif