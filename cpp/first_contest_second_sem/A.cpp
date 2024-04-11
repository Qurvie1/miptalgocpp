#include "A.h"
#include <cstddef>
#include <iostream>
#include <cstring>
#include <utility>

String::String() : s_(nullptr), size_(0), cap_(0) {
}

String::String(const char* cstring) : s_((strlen(cstring) > 0 ? new char[strlen(cstring)] : nullptr)), size_(strlen(cstring)), cap_(strlen(cstring)) {
  for (size_t i = 0; i < size_; ++i) {
    s_[i] = cstring[i];
  }
}

String::String(const String& other) : s_((other.cap_ > 0 ? new char[other.cap_] : nullptr)), size_(other.size_), cap_(other.cap_) {
  for (size_t i = 0; i < size_; ++i) {
    s_[i] = other.s_[i];
  }
}

String& String::operator=(const String& other) {
  if (s_ == other.s_) {
    return *this;
  }
  size_ = other.size_;
  cap_ = other.cap_;
  delete[] s_;
  s_ = new char[cap_];
  for (size_t i = 0; i < size_; ++i) {
    s_[i] = other.s_[i];
  }
  return *this;
}

String& String::operator=(String&& other) {
  if (s_ == other.s_) {
    return *this;
  }
  delete[] s_;
  size_ = std::move(other.size_);
  cap_ = std::move(other.cap_);
  s_ = other.s_;
  other.s_ = nullptr;
  return *this;
}

String::String(size_t size, char symbol) : s_((size > 0 ? new char[size] : nullptr)), size_(size), cap_(size) {
  for (size_t i = 0; i < size_; ++i) {
    s_[i] = symbol;
  }
}

String::String(const char* cstring, size_t size) : s_((size > 0 ? new char[size] : nullptr)), size_(size), cap_(size) {
  for (size_t i = 0; i < (size < strlen(cstring) ? size : strlen(cstring)); ++i) {
    s_[i] = cstring[i];
  }
}

String::String(String&& other) : s_(other.s_), size_(std::move(other.size_)), cap_(std::move(other.cap_)) {
  other.s_ = nullptr;
}

const char& String::operator[](const size_t index) const {
  return s_[index];
}

char& String::operator[](const size_t index) {
  return s_[index];
}

const char& String::At(const size_t index) const {
  if (size_ <= index) {
    throw StringOutOfRange{};
  }
  return s_[index];
}

char& String::At(const size_t index) {
  if (size_ <= index) {
    throw StringOutOfRange{};
  }
  return s_[index];
}

size_t String::Length() const {
  return size_;
}

size_t String::Size() const {
  return size_;
}

bool String::Empty() const {
  return size_ == 0;
}

const char& String::Front() const {
  return *s_;
}

char& String::Front() {
  return *s_;
}

const char& String::Back() const {
  return s_[size_ - 1];
}

char& String::Back() {
  return s_[size_ - 1];
}

const char* String::CStr() const {
  return s_;
}

char* String::CStr() {
  return s_;
}

const char* String::Data() const {
  return s_;
}

size_t String::Capacity() const {
  return cap_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& other) {
  other.s_ = std::exchange(s_, other.s_);
  other.size_ = std::exchange(size_, other.size_);
  other.cap_ = std::exchange(cap_, other.cap_);
}

void String::PopBack() {
  --size_;
}

void String::PushBack(char symbol) {
  if (size_ + 1 > cap_) {
    Reserve((cap_ == 0 ? 1 : cap_ * 2));
  }
  s_[size_++] = symbol;
}

void String::Resize(size_t new_size, char symbol) {
  if (new_size > cap_) {
    Reserve(new_size);
  }
  if (new_size < size_) {
    size_ = new_size;
  }
  while (size_ < new_size) {
    s_[size_++] = symbol;
  }
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity <= cap_) {
    return;
  }
  cap_ = new_capacity;
  char* new_s = new char[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    new_s[i] = s_[i];
  }
  delete[] s_;
  s_ = new_s;
}

void String::ShrinkToFit() {
  cap_ = size_;
  if (size_ == 0) {
    delete[] s_;
    s_ = nullptr;
    return;
  }
  char* new_s = new char[cap_];
  for (size_t i = 0; i < size_; ++i) {
    new_s[i] = s_[i];
  }
  delete[] s_;
  s_ = new_s;
}

String& operator+=(String& lhs, const String& rhs) {
  size_t size1 = lhs.Size();  
  size_t size2 = rhs.Size();
  size_t cap = lhs.Capacity();
  if (cap < size1 + size2) {
    lhs.Reserve((cap * 2 > size1 + size2 ? 2 * cap : size1 + size2));
  }
  lhs.Resize(size1 + size2, 'a');
  for (size_t i = 0; i < size2; ++i) {
    lhs[size1 + i] = rhs[i];
  }
  return lhs;
}

String operator+(const String& lhs, const String& rhs) {
  String copy = lhs;
  copy += rhs;
  return copy;
}

bool operator<(const String& lhs, const String& rhs) {
  for (size_t i = 0; i < (lhs.Size() < rhs.Size() ? lhs.Size() : rhs.Size()); ++i) {
    if (lhs[i] != rhs[i]) {
      return lhs[i] < rhs[i];
    }
  }
  return lhs.Size() < rhs.Size();
}

bool operator>(const String& lhs, const String& rhs) {
  return rhs < lhs;
}

bool operator==(const String& lhs, const String& rhs) {
  return !(lhs < rhs || rhs < lhs);
}

bool operator!=(const String& lhs, const String& rhs) {
  return !(lhs == rhs);
}

bool operator<=(const String& lhs, const String& rhs) {
  return !(rhs < lhs);
}

bool operator>=(const String& lhs, const String& rhs) {
  return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    out << str[i];
  }
  return out;
}