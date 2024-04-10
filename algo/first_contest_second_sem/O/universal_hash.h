#ifndef UNIVERSAL_HASH_H
#define UNIVERSAL_HASH_H

#include <random>

class UniversalHash {
 public:
  static constexpr inline size_t kPrime = 4'294'967'231;

  static constexpr inline size_t kMaxValue = kPrime - 1;

  static inline std::uniform_int_distribution<size_t> mult_random{1, kMaxValue};

  static inline std::uniform_int_distribution<size_t> add_random{0, kMaxValue};

  UniversalHash(size_t a = 1, size_t b = 0) : first_(a), second_(b){};  // NOLINT

  template <typename Generator>
  static UniversalHash GenerateHash(Generator& generator) {
    return {mult_random(generator), add_random(generator)};
  }

  size_t operator()(size_t x) const {
    return ((first_ * x) % kPrime + second_) % kPrime;
  }

 private:
  size_t first_;
  size_t second_;
};

#endif