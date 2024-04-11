#include "polish_notation.h"

std::unique_ptr<IExpression> BuildTree(std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError{};
  }
  if (std::holds_alternative<AbsToken>(tokens[pos])) {
    ++pos;
    return std::make_unique<AbsoluteValue>(BuildTree(tokens, pos));
  } 
  if (std::holds_alternative<ResidualToken>(tokens[pos])) {
    ++pos;
    std::unique_ptr<IExpression> operand1 = BuildTree(tokens, pos);
    std::unique_ptr<IExpression> operand2 = BuildTree(tokens, pos);
    return std::make_unique<Residual>(std::move(operand1), std::move(operand2));
  } 
  if (std::holds_alternative<PlusToken>(tokens[pos])) {
    ++pos;
    return std::make_unique<Sum>(BuildTree(tokens, pos), BuildTree(tokens, pos));
  } 
  if (std::holds_alternative<MinusToken>(tokens[pos])) {
    ++pos;
    std::unique_ptr<IExpression> operand1 = BuildTree(tokens, pos);
    std::unique_ptr<IExpression> operand2 = BuildTree(tokens, pos);
    return std::make_unique<Subtract>(std::move(operand1), std::move(operand2));
  } 
  if (std::holds_alternative<MultiplyToken>(tokens[pos])) {
    ++pos;
    return std::make_unique<Multiply>(BuildTree(tokens, pos), BuildTree(tokens, pos));
  } 
  if (std::holds_alternative<DivideToken>(tokens[pos])) {
    ++pos;
    std::unique_ptr<IExpression> operand1 = BuildTree(tokens, pos);
    std::unique_ptr<IExpression> operand2 = BuildTree(tokens, pos);
    return std::make_unique<Divide>(std::move(operand1), std::move(operand2));
  } 
  if (std::holds_alternative<MinToken>(tokens[pos])) {
    ++pos;
    return std::make_unique<Minimum>(BuildTree(tokens, pos), BuildTree(tokens, pos));
  } 
  if (std::holds_alternative<MaxToken>(tokens[pos])) {
    ++pos;
    return std::make_unique<Maximum>(BuildTree(tokens, pos), BuildTree(tokens, pos));
  } 
  if (std::holds_alternative<SqrToken>(tokens[pos])) {
    ++pos;
    return std::make_unique<Square>(BuildTree(tokens, pos));
  }
  ++pos;
  return std::make_unique<Constant>(std::get<NumberToken>(tokens[pos - 1]).value);
}

int CalculatePolishNotation(std::string_view input) {
  std::vector<Token> tokens = Tokenize(input);
  for (size_t i = 0; i < tokens.size(); ++i) {
    if (std::holds_alternative<UnknownToken>(tokens[i])) {
      throw UnknownSymbolError{};
    }
  }
  size_t pos = 0;
  std::unique_ptr<IExpression> root = BuildTree(tokens, pos);
  if (pos < tokens.size()) {
    throw WrongExpressionError{};
  }
  return root->Calculate();
}