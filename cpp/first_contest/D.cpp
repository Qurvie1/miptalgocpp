#include "D.h"

size_t Strlen(const char* str) {
  size_t len = 0;
  size_t i = 0;
  while (str[i] != '\0') {
    ++len;
    ++i;
  }
  return len;
}

int Strcmp(const char* first, const char* second) {
  size_t i = 0;
  while (first[i] != '\0' && second[i] != '\0') {
    if (first[i] < second[i]) {
      return 1;
    }
    if (first[i] > second[i]) {
      return -1;
    }
    ++i;
  }
  return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t i = 0;
  while (first[i] != '\0' && second[i] != '\0' && i < count) {
    if (first[i] < second[i]) {
      return 1;
    }
    if (first[i] > second[i]) {
      return -1;
    }
    ++i;
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  size_t i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    ++i;
  }
  dest[i] = src[i];
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t i = 0;
  while (i < count) {
    if (src[i] != '\0') {
      dest[i] = src[i];
      ++i;
    } else {
      dest[i] = src[i];
      ++i;
      break;
    }
  }
  while (i < count) {
    dest[i++] = '\0';
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {
  size_t i = 0;
  while (dest[i] != '\0') {
    ++i;
  }
  size_t j = 0;
  while (src[j] != '\0') {
    dest[i++] = src[j++];
  }
  dest[i] = src[j];
  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t i = 0;
  while (dest[i] != '\0') {
    ++i;
  }
  size_t j = 0;
  while (src[j] != '\0' && j < count) {
    dest[i++] = src[j++];
  }
  dest[i] = '\0';
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  size_t i = 0;
  while (str[i] != '\0') {
    if (str[i] == symbol) {
      const char* ptr = str + i;
      return ptr;
    }
    ++i;
  }
  if (symbol == '\0') {
    const char* ptr = str + i;
    return ptr;
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  size_t i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  if (symbol == '\0') {
    const char* ptr = str + i;
    return ptr;
  }
  --i;
  while (i >= 0) {
    if (str[i] == symbol) {
      const char* ptr = str + i;
      return ptr;
    }
    --i;
  }
  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  size_t i = 0;
  size_t j = 0;
  size_t counter = 0;
  while (dest[i] != '\0') {
    while (src[j] != '\0') {
      if (dest[i] == src[j]) {
        ++counter;
        j = 0;
        break;
      }
      ++j;
    }
    if (j != 0) {
      break;
    }
    ++i;
  }
  return counter;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t i = 0;
  size_t j = 0;
  size_t counter = 0;
  while (dest[i] != '\0') {
    while (src[j] != '\0') {
      if (dest[i] == src[j]) {
        j = -1;
        break;
      }
      ++j;
    }
    if (j == -1) {
      break;
    }
    ++counter;
    j = 0;
    ++i;
  }
  return counter;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t i = 0;
  size_t j = 0;
  while (dest[i] != '\0') {
    while (breakset[j] != '\0') {
      if (dest[i] == breakset[j]) {
        j = -1;
        break;
      }
      ++j;
    }
    if (j == -1) {
      const char* ptr = dest + i;
      return ptr;
    }
    j = 0;
    ++i;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  size_t i = 0;
  size_t j = 0;
  size_t len_pattern = 0;
  size_t len_string = 0;
  while (pattern[j] != '\0') {
    ++len_pattern;
    ++j;
  }
  j = 0;
  while (str[i] != '\0') {
    ++len_string;
    ++i;
  }
  i = 0;
  while (i < len_string - len_pattern + 1) {
    j = 0;
    while (j < len_pattern && str[i + j] == pattern[j]) {
      ++j;
    }
    if (j == len_pattern) {
      const char* ptr = str + i;
      return ptr;
    }
    ++i;
  }
  return nullptr;
}