#pragma once

#include "Token/lexer_token.h"
#include "../Reader/code_reader.h"
#include <iostream>
#include <memory>

namespace compiler{

using TokenShareType = std::shared_ptr<LexerToken>;

class LexerParser{
 private:
  CodeReader codeReader;
  TokenShareType  nowToken;

  int operatorType(char sign);
  bool isNoNumber(char sign);
  bool isNumber(char sign);

  void lineCommentSkip();
  void commentSkip(std::pair<size_t,size_t> &position);
  int octalToDecimal(std::string octal);
  int octalToDecimal(char octal);
  int hexToDecimal(std::string hex);
  int hexToDecimal(char hex);
  char getEscapeSequence(std::pair<size_t,size_t> &position, std::string &codeString);
  TokenShareType getEofToken();
  TokenShareType getErrorToken();
  TokenShareType getOperatorToken(std::pair<size_t,size_t> &position, std::string &codeString);
  TokenShareType getOperatorToken();
  TokenShareType getLToken();
  TokenShareType getCharToken(std::pair<size_t,size_t> position, std::string codeString);
  TokenShareType getCharToken();

 public:
  LexerParser(std::string fileName);
  TokenShareType getToken();
  TokenShareType nextToken();

};



}