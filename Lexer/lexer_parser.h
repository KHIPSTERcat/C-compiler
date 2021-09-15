#pragma once

#include "Token/lexer_token.h"
#include "../Reader/code_reader.h"
#include <iostream>
#include <memory>
#include <map>

namespace compiler{

using TokenShareType = std::shared_ptr<LexerToken>;

class LexerParser{
 private:
  CodeReader codeReader;
  TokenShareType  nowToken;
  std::map<std::string,compiler::KeywordType> keywordDictionary;
  std::map<std::string,compiler::OperatorType> operatorDictionary;


  bool isNoNumber(char sign);
  bool isNumber(char sign);

  void lineCommentSkip();
  void multiLineCommentSkip(compiler::TokenPosition &position);

  bool isOctal(char octal);
  bool isHex(char hex);

  char getEscapeSequence(compiler::TokenPosition position, std::string &codeString);

  TokenShareType getEofToken();
  TokenShareType getErrorToken();
  TokenShareType getOperatorToken();
  TokenShareType getLToken();
  TokenShareType getIdentifierOrKeywordOrLToken();
  TokenShareType getCharToken(compiler::TokenPosition position, std::string codeString);
  TokenShareType getCharToken();
  TokenShareType getStringToken(compiler::TokenPosition position, std::string codeString);
  TokenShareType getStringToken();
  TokenShareType getIntOrFloatToken();
  TokenShareType getIntOrFloatToken(compiler::TokenPosition position, std::string codeString);

 public:
  LexerParser(std::string fileName);
  TokenShareType getToken();
  TokenShareType nextToken();

};



}