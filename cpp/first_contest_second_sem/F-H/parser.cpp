#include "parser.h"

std::unique_ptr<IExpression> ParseExpression(std::vector<Token> tokens, size_t& pos) {
  std::unique_ptr<IExpression> first;
  std::unique_ptr<IExpression> second;
  first = ParseAddendum(tokens, pos);
  while (true) {
    if (pos == tokens.size()) {
      break;
    }
    if (std::holds_alternative<PlusToken>(tokens[pos])) {
      ++pos;
      second = ParseAddendum(tokens, pos);
      first = std::make_unique<Sum>(std::move(first), std::move(second));
    } else if (std::holds_alternative<MinusToken>(tokens[pos])) {
      ++pos;
      second = ParseAddendum(tokens, pos);
      first = std::make_unique<Subtract>(std::move(first), std::move(second));
    } else if (std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      break;
    }
  }
  return first;
}

std::unique_ptr<IExpression> ParseAddendum(std::vector<Token> tokens, size_t& pos) {
  std::unique_ptr<IExpression> first;
  std::unique_ptr<IExpression> second;
  first = ParseMultiplier(tokens, pos);
  while (true) {
    if (pos == tokens.size()) {
      break;
    }
    if (std::holds_alternative<MultiplyToken>(tokens[pos])) {
      ++pos;
      second = ParseMultiplier(tokens, pos);
      first = std::make_unique<Multiply>(std::move(first), std::move(second));
      continue;
    } 
    if (std::holds_alternative<DivideToken>(tokens[pos])) {
      ++pos;
      second = ParseMultiplier(tokens, pos);
      first = std::make_unique<Divide>(std::move(first), std::move(second));
      continue;
    } 
    if (std::holds_alternative<ResidualToken>(tokens[pos])) {
      ++pos;
      second = ParseMultiplier(tokens, pos);
      first = std::make_unique<Residual>(std::move(first), std::move(second));
      continue;
    }
    if (std::holds_alternative<ClosingBracketToken>(tokens[pos]) || std::holds_alternative<PlusToken>(tokens[pos]) || std::holds_alternative<MinusToken>(tokens[pos])) {
      break;
    }
    if (std::holds_alternative<NumberToken>(tokens[pos]) || std::holds_alternative<OpeningBracketToken>(tokens[pos])) {
      throw WrongExpressionError{};
    }
  }
  return first;
}

std::unique_ptr<IExpression> ParseMultiplier(std::vector<Token> tokens, size_t& pos) {
  if (std::holds_alternative<OpeningBracketToken>(tokens[pos])) {
    ++pos;
    if (pos == tokens.size()) {
      throw WrongExpressionError{};
    }
    std::unique_ptr<IExpression> first = ParseExpression(tokens, pos);
    if (pos < tokens.size() && std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      ++pos;
    } else {
      throw WrongExpressionError{};
    }
    return first;
  } 
  if (std::holds_alternative<NumberToken>(tokens[pos])) {
    ++pos;
    std::unique_ptr<IExpression> first = std::make_unique<Constant>(std::get<NumberToken>(tokens[pos - 1]).value);
    return first;
  }
  throw WrongExpressionError{};
}