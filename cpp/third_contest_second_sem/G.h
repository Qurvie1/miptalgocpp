#ifndef LRU_H
#define LRU_H

#include <unordered_map>
#include <map>
#include <cstddef>
#include <stdexcept>

template <typename Key, typename Value>
class LRUMap {
 public:
  explicit LRUMap(size_t cap) : capacity_(cap) {
  }

  LRUMap(const LRUMap& other)
      : map_(other.map_), mins_(other.mins_), current_time_(other.current_time_), capacity_(other.capacity_) {
  }

  LRUMap(LRUMap&& other)
      : map_(std::move(other.map_))
      , mins_(std::move(other.mins_))
      , current_time_(std::move(other.current_time_))
      , capacity_(other.capacity_) {
  }

  LRUMap& operator=(const LRUMap& other) {
    if (this == &other) {
      return *this;
    }
    map_ = other.map_;
    mins_ = other.mins_;
    current_time_ = other.current_time_;
    capacity_ = other.capacity_;
  }

  LRUMap& operator=(LRUMap&& other) {
    if (this == &other) {
      return *this;
    }
    map_ = std::move(other.map_);
    mins_ = std::move(other.mins_);
    current_time_ = std::move(other.current_time_);
    capacity_ = other.capacity_;
  }

  size_t Size() const noexcept {
    return map_.size();
  }

  size_t Capacity() const noexcept {
    return capacity_;
  }

  bool Empty() const noexcept {
    return map_.empty();
  }

  bool Contains(const Key& key) const {
    return UpdateTime(key);
  }

  void Erase(const Key& key) {
    ++current_time_;
    auto it = map_.find(key);
    if (it == map_.end()) {
      return;
    }
    mins_.erase(it->second.second);
    map_.erase(it);
  }

  void Add(const Key& key, const Value& val) {
    if (map_.size() == capacity_) {
      Erase((--mins_.end())->second);
    }
    if (UpdateTime(key)) {
      return;
    }
    ++current_time_;
    map_.emplace(std::piecewise_construct, std::forward_as_tuple(key),
                 std::forward_as_tuple(std::move(val), current_time_));
    mins_.emplace(current_time_, key);
  }

  void Add(const Key& key, Value&& val) {
    if (map_.size() == capacity_) {
      Erase((--mins_.end())->second);
    }
    if (UpdateTime(key)) {
      return;
    }
    ++current_time_;
    map_.emplace(std::piecewise_construct, std::forward_as_tuple(key),
                 std::forward_as_tuple(std::move(val), current_time_));
    mins_.emplace(current_time_, key);
  }

  const Value& GetOr(const Key& key, const Value& default_value) const {
    if (UpdateTime(key)) {
      return map_[key].first;
    }
    return default_value;
  }

  Value& Get(const Key& key) const {
    if (UpdateTime(key)) {
      return map_[key].first;
    }
    throw std::out_of_range("Out of range!");
  }

  void Clear() {
    map_.clear();
    mins_.clear();
  }

 private:
  bool UpdateTime(const Key& key) const {
    auto it = map_.find(key);
    if (it == map_.end()) {
      return false;
    }
    ++current_time_;
    size_t time = it->second.second;
    mins_.erase(time);
    mins_.emplace(current_time_, key);
    it->second.second = current_time_;
    return true;
  }

  mutable std::unordered_map<Key, std::pair<Value, size_t>> map_;
  mutable std::map<size_t, Key, std::greater<size_t>> mins_;
  mutable size_t current_time_ = 0;
  const size_t capacity_;
};

#endif