#include <iostream>
#include <string>
#include <variant>
#include <string_view>
#include <vector>

#ifndef TOKENIZE_H
#define TOKENIZE_H

bool IsNumber(std::string a);

bool IsNumberWithPlusOrMinus(std::string a);

struct PlusToken {
  bool operator==(const PlusToken&) const;
};

struct MinusToken {
  bool operator==(const MinusToken&) const;
};

struct MultiplyToken {
  bool operator==(const MultiplyToken&) const;
};

struct DivideToken {
  bool operator==(const DivideToken&) const;
};

struct OpeningBracketToken {
  bool operator==(const OpeningBracketToken&) const;
};

struct ClosingBracketToken {
  bool operator==(const ClosingBracketToken&) const;
};

struct ResidualToken {
  bool operator==(const ResidualToken&) const;
};

struct SqrToken {
  bool operator==(const SqrToken&) const;
};

struct MaxToken {
  bool operator==(const MaxToken&) const;
};

struct MinToken {
  bool operator==(const MinToken&) const;
};

struct AbsToken {
  bool operator==(const AbsToken&) const;
};

struct NumberToken {
  int value;
  bool operator==(const NumberToken&) const;
};

struct UnknownToken {
  std::string value;
  bool operator==(const UnknownToken&) const;
};

using Token = std::variant<ResidualToken, MinusToken, PlusToken, UnknownToken, NumberToken, AbsToken, MinToken, MaxToken, SqrToken, ClosingBracketToken, OpeningBracketToken, DivideToken, MultiplyToken>;

std::vector<Token> Tokenize(std::string_view);

#endif