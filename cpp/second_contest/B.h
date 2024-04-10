#include <stdexcept>

#ifndef STRING_VIEW_H
#define STRING_VIEW_H

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  StringView();

  StringView(const char* string); // NOLINT

  StringView(const char* string, size_t size);
  
  void Swap(StringView& s);

  StringView Substr (size_t pos, size_t count);

  void RemoveSuffix(size_t suffix_size);

  void RemovePrefix(size_t prefix_size);

  size_t Size() const;

  size_t Length() const;

  const char* Data() const;

  bool Empty() const;

  const char& Back() const;

  const char& Front() const;

  const char& operator [](size_t index) const;

 private:

  const char* s_;
  size_t size_;
};

#endif