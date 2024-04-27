#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#define ITERATOR_IMPLEMENTED

#define FORWARD_LIST_IMPLEMENTED

#include <cstddef>
#include <vector>
#include <forward_list>
#include <functional>
#include <iterator>
#include <iostream>
#include <sstream>

template <class Key>
class UnorderedSet {
 public:
  UnorderedSet() : sz_(0), elements_{}, buckets_{} {};

  UnorderedSet(size_t count)  // NOLINT
      : sz_(0), elements_{}, buckets_{count} {};

  template <class ForwardIt>
  UnorderedSet(ForwardIt begin, ForwardIt end) {
    size_t sz = 0;
    for (ForwardIt it = begin; it != end; ++it) {
      ++sz;
    }
    buckets_ = std::vector<Iterator>(sz);
    for (ForwardIt it = begin; it != end; ++it) {
      Insert(*it);
    }
  }

  bool Find(const Key& key) const {
    if (buckets_.empty()) {
      return false;
    }
    std::hash<Key> hasher{};
    size_t index = hasher(key) % buckets_.size();
    auto it = buckets_[index];
    if (it == elements_.end()) {
      return false;
    }
    ++it;
    for (; it != elements_.end() && hasher(*it) % buckets_.size() == index; ++it) {
      if (*it == key) {
        return true;
      }
    }
    return false;
  }

  UnorderedSet(const UnorderedSet& other) : buckets_(other.buckets_.size(), elements_.end()) {
    for (auto v : other.elements_) {
      Insert(v);
    }
  }

  UnorderedSet(UnorderedSet&& other) : sz_(other.sz_) {
    size_t index = 0;
    if (sz_) {
      index = std::hash<Key>{}(*other.elements_.begin()) % other.buckets_.size();
    }
    elements_.splice_after(elements_.before_begin(), other.elements_);
    other.sz_ = 0ul;
    buckets_ = std::move(other.buckets_);
    if (sz_) {
      buckets_[index] = elements_.before_begin();
    }
  }

  UnorderedSet& operator=(const UnorderedSet& other) {
    if (this == &other) {
      return *this;
    }
    elements_.clear();
    sz_ = 0;
    buckets_ = std::vector<Iterator>(other.buckets_.size(), elements_.end());
    for (auto v : other.elements_) {
      Insert(v);
    }
    return *this;
  }

  UnorderedSet& operator=(UnorderedSet&& other) {
    if (this == &other) {
      return *this;
    }
    sz_ = other.sz_;
    elements_.clear();
    size_t index = 0;
    if (sz_) {
      index = std::hash<Key>{}(*other.elements_.begin()) % other.buckets_.size();
    }
    elements_.splice_after(elements_.before_begin(), other.elements_);
    other.sz_ = 0ul;
    buckets_ = std::move(other.buckets_);
    if (sz_) {
      buckets_[index] = elements_.before_begin();
    }
    return *this;
  }

  size_t Size() const noexcept {
    return sz_;
  }

  bool Empty() const noexcept {
    return sz_ == 0;
  }

  void Clear() noexcept {
    sz_ = 0ul;
    elements_ = std::forward_list<Key>();
    buckets_ = std::vector<Iterator>();
  }

  size_t BucketCount() const noexcept {
    return buckets_.size();
  }

  size_t BucketSize(size_t id) const noexcept {
    if (buckets_.size() <= id) {
      return 0;
    }
    auto it = buckets_[id];
    if (it == elements_.end()) {
      return 0;
    }
    ++it;
    std::hash<Key> hasher{};
    size_t index = hasher(*it) % buckets_.size();
    size_t counter = 0;
    for (; it != elements_.end() && hasher(*it) % buckets_.size() == index; ++it) {
      ++counter;
    }
    return counter;
  }

  double LoadFactor() const noexcept {
    if (buckets_.empty()) {
      return 0.0;
    }
    return static_cast<double>(sz_) / buckets_.size();
  }

  using DifferenceType = size_t;

  using Iterator = typename std::forward_list<Key>::const_iterator;

  using ConstIterator = typename std::forward_list<Key>::const_iterator;

  Iterator begin() {  // NOLINT
    return elements_.begin();
  }

  Iterator end() {  // NOLINT
    return elements_.end();
  }

  ConstIterator begin() const {  // NOLINT
    return elements_.begin();
  }

  ConstIterator end() const {  // NOLINT
    return elements_.end();
  }

  ConstIterator cbegin() const {  // NOLINT
    return elements_.begin();
  }

  ConstIterator cend() const {  // NOLINT
    return elements_.end();
  }

  void Erase(const Key& key) {
    if (buckets_.empty()) {
      return;
    }
    std::hash<Key> hasher{};
    size_t index = hasher(key) % buckets_.size();
    if (buckets_[index] == elements_.end()) {
      return;
    }
    size_t counter = 0;
    auto next = buckets_[index];
    ++next;
    bool fl = false;
    auto prev = buckets_[index];
    for (; next != elements_.end() && hasher(*next) % buckets_.size() == index;) {
      ++counter;
      if (*next == key) {
        next = elements_.erase_after(prev);
        fl = true;
        --sz_;
        if (next != elements_.end() && hasher(*next) % buckets_.size() != index && counter > 1) {
          size_t new_index = hasher(*next) % buckets_.size();
          buckets_[new_index] = prev;
        }
        break;
      }
      ++next;
      ++prev;
    }
    if (counter == 1 && next == elements_.end() && fl) {
      buckets_[index] = elements_.end();
      return;
    }
    if (counter == 1 && hasher(*next) % buckets_.size() != index && fl) {
      size_t new_index = hasher(*next) % buckets_.size();
      buckets_[new_index] = prev;
      buckets_[index] = elements_.end();
    }
  }

  void Insert(const Key& key) {
    if (buckets_.empty()) {
      Rehash(1);
    }
    std::hash<Key> hasher{};
    size_t index = hasher(key) % buckets_.size();
    if (buckets_[index] == elements_.end() && !elements_.empty()) {
      auto it = elements_.begin();
      size_t index_prev = hasher(*it) % buckets_.size();
      buckets_[index_prev] = elements_.insert_after(elements_.before_begin(), key);
      buckets_[index] = elements_.before_begin();
      ++sz_;
      if (static_cast<double>(sz_) / buckets_.size() > max_load_factor_) {
        Rehash(buckets_.size() * 2);
      }
      return;
    }
    if (buckets_[index] == elements_.end() && elements_.empty()) {
      buckets_[index] = elements_.before_begin();
      elements_.insert_after(elements_.before_begin(), key);
      ++sz_;
      if (static_cast<double>(sz_) / buckets_.size() > max_load_factor_) {
        Rehash(buckets_.size() * 2);
      }
      return;
    }
    auto iterator = buckets_[index];
    ++iterator;
    size_t h = hasher(*iterator);
    for (; iterator != elements_.end() && hasher(*iterator) == h; ++iterator) {
      if (*iterator == key) {
        return;
      }
    }
    if (iterator != elements_.end()) {
      size_t next_hash = hasher(*iterator) % buckets_.size();
      buckets_[next_hash] = elements_.insert_after(buckets_[next_hash], key);
    } else {
      elements_.insert_after(buckets_[index], key);
    }
    ++sz_;
    if (static_cast<double>(sz_) / buckets_.size() > max_load_factor_) {
      Rehash(buckets_.size() * 2);
    }
  }

  size_t Bucket(const Key& key) const noexcept {
    return std::hash<Key>{}(key) % buckets_.size();
  }

  void Insert(Key&& key) {
    if (buckets_.empty()) {
      Rehash(1);
    }
    std::hash<Key> hasher{};
    size_t index = hasher(key) % buckets_.size();
    if (buckets_[index] == elements_.end() && !elements_.empty()) {
      auto it = elements_.begin();
      size_t index_prev = hasher(*it) % buckets_.size();
      buckets_[index_prev] = elements_.insert_after(elements_.before_begin(), std::move(key));
      buckets_[index] = elements_.before_begin();
      ++sz_;
      if (static_cast<double>(sz_) / buckets_.size() > max_load_factor_) {
        Rehash(buckets_.size() * 2);
      }
      return;
    }
    if (buckets_[index] == elements_.end() && elements_.empty()) {
      buckets_[index] = elements_.before_begin();
      elements_.insert_after(elements_.before_begin(), std::move(key));
      ++sz_;
      if (static_cast<double>(sz_) / buckets_.size() > max_load_factor_) {
        Rehash(buckets_.size() * 2);
      }
      return;
    }
    auto iterator = buckets_[index];
    ++iterator;
    size_t h = hasher(*iterator);
    for (; iterator != elements_.end() && hasher(*iterator) == h; ++iterator) {
      if (*iterator == key) {
        return;
      }
    }
    if (iterator != elements_.end()) {
      size_t next_hash = hasher(*iterator) % buckets_.size();
      buckets_[next_hash] = elements_.insert_after(buckets_[next_hash], std::move(key));
    } else {
      elements_.insert_after(buckets_[index], std::move(key));
    }
    ++sz_;
    if (static_cast<double>(sz_) / buckets_.size() > max_load_factor_) {
      Rehash(buckets_.size() * 2);
    }
  }

  void Rehash(size_t count) {
    if (count == buckets_.size() || count < sz_) {
      return;
    }
    std::forward_list<Key> oldel = std::move(elements_);
    buckets_ = std::vector<Iterator>(count, elements_.end());
    while (!oldel.empty()) {
      InsertResize(oldel.before_begin(), oldel, *(oldel.begin()));
    }
  }

  void Reserve(size_t count) {
    if (count <= buckets_.size()) {
      return;
    }
    Rehash(count);
  };

  auto Pointer(size_t id) {
    if (buckets_[id] == elements_.before_begin()) {
      return -1;
    }
    if (buckets_[id] == elements_.end()) {
      return -2;
    }
    return static_cast<int>(Bucket(*buckets_[id]));
  }

 private:
  void InsertResize(Iterator it, std::forward_list<Key>& from, const Key& value) {
    std::hash<Key> hasher{};
    size_t index = hasher(value) % buckets_.size();
    if (buckets_[index] == elements_.end() && !elements_.empty()) {
      auto iter = elements_.begin();
      size_t index_prev = hasher(*iter) % buckets_.size();
      elements_.splice_after(elements_.before_begin(), from, it);
      buckets_[index_prev] = elements_.begin();
      buckets_[index] = elements_.before_begin();
      return;
    }
    if (buckets_[index] == elements_.end() && elements_.empty()) {
      buckets_[index] = elements_.before_begin();
      elements_.splice_after(elements_.before_begin(), from, it);
      return;
    }
    auto iterator = buckets_[index];
    elements_.splice_after(iterator, from, it);
  }
  double max_load_factor_ = 1.0;
  size_t sz_ = 0;
  std::forward_list<Key> elements_;
  std::vector<Iterator> buckets_;
};

#endif