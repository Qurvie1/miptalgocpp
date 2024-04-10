#include <cstddef>
#include "B.h"
#include <iostream>

StringView::StringView() : s_(nullptr), size_(0) { 
}

StringView::StringView(const char* string) {
  size_ = 0;
  s_ = string;
  while (string[size_] != '\0') {
    ++size_;
  }
}

StringView::StringView(const char* string, size_t size) {
  size_ = size;
  s_ = string;
}

const char& StringView::operator[](size_t index) const {
  return s_[index];
}

const char& StringView::Front() const {
  return s_[0];
}

const char& StringView::Back() const {
  return s_[size_ - 1];
}

bool StringView::Empty() const {
  return size_ == 0;    
}

const char* StringView::Data() const {
  return s_;
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

void StringView::RemovePrefix(size_t prefix_size) {
  s_ = s_ + prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count = -1) {
  if (size_ <= pos) {
    throw StringViewOutOfRange();
  }
  StringView s(s_ + pos, (size_ - pos < count ? size_ - pos : count));
  return s;
}

void StringView::Swap(StringView& s) {
  const char* temp_s = s_;
  size_t temp_size = size_;
  s_ = s.s_;
  size_ = s.size_;
  s.s_ = temp_s;
  s.size_ = temp_size;
}