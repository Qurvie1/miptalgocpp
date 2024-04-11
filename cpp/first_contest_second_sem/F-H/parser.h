#include <string>
#include <stdexcept>
#include "../tokenize/tokenize.h"
#include "../polish_notation/expressions.h"

#ifndef PARSER_H
#define PARSER_H

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

std::unique_ptr<IExpression> ParseExpression(std::vector<Token> tokens, size_t& pos);

std::unique_ptr<IExpression> ParseAddendum(std::vector<Token> tokens, size_t& pos);

std::unique_ptr<IExpression> ParseMultiplier(std::vector<Token> tokens, size_t& pos);

#endif