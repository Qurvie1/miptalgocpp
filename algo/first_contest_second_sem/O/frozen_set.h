#ifndef FROZEN_SET_H
#define FROZEN_SET_H

#include <functional>
#include <random>
#include <optional>
#include "universal_hash.h"

template <class T, class Hash>
class FrozenSet {
 public:
  FrozenSet() : sz_(0), hash_table_{}, primary_hash_{}, secondary_hashes_{} {
  }

  template <typename ForwardIt, typename Generator>
  FrozenSet(ForwardIt begin, ForwardIt end, Generator& gen)
      : sz_(std::distance(begin, end))
      , hash_table_(std::distance(begin, end))
      , primary_hash_{}
      , secondary_hashes_(std::distance(begin, end)) {
    if (hash_table_.empty()) {
      return;
    }
    std::vector<std::vector<T>> objects(hash_table_.size());
    Hash hasher;
    size_t sum_sqr = 0;
    do {
      primary_hash_ = UniversalHash::GenerateHash(gen);
      for (size_t i = 0; i < objects.size(); ++i) {
        objects[i].clear();
      }
      for (ForwardIt it = begin; it != end; ++it) {
        objects[primary_hash_(hasher(*it)) % objects.size()].push_back(*it);
      }
      sum_sqr = 0;
      for (size_t i = 0; i < objects.size(); ++i) {
        sum_sqr += objects[i].size() * objects[i].size();
      }
    } while (sum_sqr >= 4 * objects.size());

    for (size_t i = 0; i < hash_table_.size(); ++i) {
      hash_table_[i] = std::vector<std::optional<T>>(objects[i].size() * objects[i].size());
      bool have_collisions = false;
      do {
        secondary_hashes_[i] = UniversalHash::GenerateHash(gen);
        for (size_t j = 0; j < hash_table_[i].size(); ++j) {
          hash_table_[i][j].reset();
        }
        have_collisions = false;
        for (const auto& obj : objects[i]) {
          size_t j = secondary_hashes_[i](hasher(obj)) % hash_table_[i].size();
          if (hash_table_[i][j].has_value()) {
            have_collisions = true;
            break;
          }
          hash_table_[i][j] = obj;
        }
      } while (have_collisions);
    }
  }

  size_t Size() const {
    return sz_;
  }

  bool Empty() const {
    return sz_ == 0;
  }

  void Clear() {
    for (auto& vec : hash_table_) {
      vec.clear();
    }
    hash_table_.clear();
    sz_ = 0;
  }

  bool Find(const T& obj) const {
    Hash hasher;
    if (sz_ == 0 || hash_table_.empty()) {
      return false;
    }
    size_t i = primary_hash_(hasher(obj)) % hash_table_.size();
    if (hash_table_[i].empty()) {
      return false;
    }
    size_t j = secondary_hashes_[i](hasher(obj)) % hash_table_[i].size();
    return (hash_table_[i][j].has_value() && hash_table_[i][j] == obj);
  }

 private:
  size_t sz_;

  std::vector<std::vector<std::optional<T>>> hash_table_;

  UniversalHash primary_hash_;

  std::vector<UniversalHash> secondary_hashes_;
};

#endif