#include <cstddef>
#include <iostream>
#include <stdexcept>

#ifndef STRING_H
#define STRING_H

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 public:
  String();

  ~String() {
    delete[] s_;
  }

  String(size_t size, char symbol);

  String(const String& other);

  String(String&& other);

  String(const char* cstring);  // NOLINT

  String(const char* cstring, size_t size);

  const char& operator[](size_t index) const;

  char& operator[](size_t index);

  String& operator=(const String& other);

  String& operator=(String&& other);

  const char& At(size_t index) const;

  char& At(size_t index);

  char& Front();

  const char& Front() const;

  char& Back();

  const char& Back() const;

  const char* CStr() const;

  char* CStr();

  const char* Data() const;

  bool Empty() const;

  size_t Size() const;

  size_t Length() const;

  size_t Capacity() const;

  void Clear();

  void Swap(String& other);

  void PopBack();

  void PushBack(char symbol);

  void Resize(size_t new_size, char symbol);

  void Reserve(size_t new_capacity);

  void ShrinkToFit();

 private:
  char* s_;
  size_t size_;
  size_t cap_;
};

String& operator+=(String& lhs, const String& rhs);

String operator+(const String& lhs, const String& rhs);

bool operator<(const String& lhs, const String& rhs);

bool operator>(const String& lhs, const String& rhs);

bool operator<=(const String& lhs, const String& rhs);

bool operator>=(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const String& rhs);

bool operator!=(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& out, const String& string);

#endif