#pragma once

namespace compiler{

enum class TokenType {
  kNone = 0,
  kInt,
  kFloat,
  kChar,
  kString,
  kIdentifier,
  kKeyword,
  kOperator,
  kEOF,
  kSeparator
};

class LexerToken{
 private:
  TokenType tokenType;
  std::pair<size_t, size_t> tokenPosition;
  std::string tokenCodeString;

 public:
  TokenType getType();
  std::pair<size_t, size_t> getPosition();
  std::string getCodeString;

};


}