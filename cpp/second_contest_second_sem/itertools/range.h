#ifndef RANGE_H
#define RANGE_H

#define REVERSE_RANGE_IMPLEMENTED

class Range {
 public:
  explicit Range(int finish) : finish_(finish) {}

  Range(int start, int finish) : start_(start), finish_(finish) {}

  Range(int start, int finish, int step) : step_(step), start_(start), finish_(finish) {}

  class Iterator {
   public:
    Iterator(int value, int step) : value_(value), step_(step) {}

    int operator*() {
      return value_;
    }

    Iterator& operator++() {
      value_ += step_;
      return *this;
    }

    bool operator==(const Iterator& other) const noexcept {
      if (step_ > 0) {
        return value_ >= other.value_;
      } 
      if (step_ < 0) {
        return value_ <= other.value_;
      }
      return true;
    }

    bool operator!=(const Iterator& other) const noexcept {
      return !(*this == other);
    }

   private:
    int value_;
    int step_ = 1;
  };

  Iterator begin() {  // NOLINT
    return {start_, step_};
  }

  Iterator end() {  // NOLINT
    return {finish_, step_};
  }

  Iterator begin() const {  // NOLINT
    return {start_, step_};
  }

  Iterator end() const {  // NOLINT
    return {finish_, step_};
  }

  Iterator rbegin() {  // NOLINT
    if (step_ != 0 && (finish_ - start_) % step_ != 0) {
      return {start_ + (finish_ - start_ + step_ - 1) / step_ * step_ - step_, -step_}; 
    }
    return {finish_ - step_, -step_};
  }

  Iterator rend() {  // NOLINT
    return {start_ - step_, -step_};
  }

  Iterator rbegin() const {  // NOLINT
    if (step_ != 0 && (finish_ - start_) % step_ != 0) {
      return {start_ + (finish_ - start_ + step_ - 1) / step_ * step_ - step_, -step_}; 
    }
    return {finish_ - step_, -step_};
  }

  Iterator rend() const {  // NOLINT
    return {start_ - step_, -step_};
  }

 private:
  int step_ = 1;
  int start_ = 0;
  int finish_;
};

#endif