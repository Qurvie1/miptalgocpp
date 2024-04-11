#include "../tokenize/tokenize.h"
#include "parser.h"

int CalculateExpression(std::string_view input) {
  std::vector<Token> tokens = Tokenize(input);
  for (size_t i = 0; i < tokens.size(); ++i) {
    if (std::holds_alternative<UnknownToken>(tokens[i])) {
      throw UnknownSymbolError{};
    }
  }
  if (tokens.empty()) {
    throw WrongExpressionError{};
  }
  size_t pos = 0;
  std::unique_ptr<IExpression> root = ParseExpression(tokens, pos);
  if (pos < tokens.size()) {
    throw WrongExpressionError{};
  }
  return root->Calculate();
}