#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string_view>
#include "expressions.h"
#include "../tokenize/tokenize.h"

#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

class UnknownSymbolError : public std::runtime_error {
 public:
  explicit UnknownSymbolError(const std::string& symbol = "") : std::runtime_error("UnknownSymbolError: " + symbol) {
  }
};

class WrongExpressionError : public std::runtime_error {
 public:
  explicit WrongExpressionError(const std::string& msg = "") : std::runtime_error("WrongExpressionError: " + msg) {
  }
};

std::unique_ptr<IExpression> BuildTree(std::vector<Token>& tokens, size_t& pos);

int CalculatePolishNotation(std::string_view input);

#endif