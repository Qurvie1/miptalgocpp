#include "tokenize.h"
#include <variant>
#include <string_view>
#include <cstring>

bool IsNumber(std::string a) {
  if (a.empty()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (0 > a[i] - '0' || a[i] - '0' > 9) {
      return false;
    }
  }
  return true;
}

bool IsNumberWithPlusOrMinus(std::string a) {
  if (a.size() < 2) {
    return false;
  }
  if (a[0] != '+' && a[0] != '-') {
    return false;
  }
  for (size_t i = 1; i < a.size(); ++i) {
    if (0 > a[i] - '0' || a[i] - '0' > 9) {
      return false;
    }
  }
  return true;
}

bool PlusToken::operator==(const PlusToken&) const {
  return true;
}

bool MinusToken::operator==(const MinusToken&) const {
  return true;
}

bool SqrToken::operator==(const SqrToken&) const {
  return true;
}

bool MaxToken::operator==(const MaxToken&) const {
  return true;
}

bool MinToken::operator==(const MinToken&) const {
  return true;
}

bool MultiplyToken::operator==(const MultiplyToken&) const {
  return true;
}

bool ResidualToken::operator==(const ResidualToken&) const {
  return true;
}

bool DivideToken::operator==(const DivideToken&) const {
  return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken&) const {
  return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken&) const {
  return true;
}

bool AbsToken::operator==(const AbsToken&) const {
  return true;
}

bool NumberToken::operator==(const NumberToken& other) const {
  return value == other.value;
}

bool UnknownToken::operator==(const UnknownToken& other) const {
  return value == std::string(other.value);
}

std::vector<Token> Tokenize(std::string_view str) {
  std::vector<Token> vec;
  size_t i = 0;
  std::string other;
  while (i <= str.size()) {
    if (str[i] == ' ' || i == str.size()) {
      if (other == "+") {
        vec.emplace_back(PlusToken{});
      } else if (other == "-") {
        vec.emplace_back(MinusToken{});
      } else if (other == "%") {
        vec.emplace_back(ResidualToken{});
      } else if (other == "/") {
        vec.emplace_back(DivideToken{});
      } else if (other == "*") {
        vec.emplace_back(MultiplyToken{});
      } else if (other == "(") {
        vec.emplace_back(OpeningBracketToken{});
      } else if (other == ")") {
        vec.emplace_back(ClosingBracketToken{});
      } else if (other == "max") {
        vec.emplace_back(MaxToken{});
      } else if (other == "min") {
        vec.emplace_back(MinToken{});
      } else if (other == "sqr") {
        vec.emplace_back(SqrToken{});
      } else if (other == "abs") {
        vec.emplace_back(AbsToken{});
      } else if (IsNumber(other)) {
        int value = 0;
        for (size_t i = 0; i < other.size(); ++i) {
          value = 10 * value + (other[i] - '0');
        }
        vec.emplace_back(NumberToken{value});
      } else if (IsNumberWithPlusOrMinus(other)) {
        int value = 0;
        for (size_t i = 1; i < other.size(); ++i) {
          value = 10 * value + (other[i] - '0');
        }
        if (other[0] == '-') {
          vec.emplace_back(NumberToken{-value});
        } else if (other[0] == '+') {
          vec.emplace_back(NumberToken{+value});
        }
      } else if (!other.empty()) {
        vec.emplace_back(UnknownToken{other});
      }
      other.clear();
      ++i;
    } else if (str[i] != ' ') {
      other += str[i];
      ++i;
    }
  }
  return vec;
}