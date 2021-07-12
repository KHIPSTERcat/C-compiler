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
  void multiLineCommentSkip(std::pair<size_t,size_t> &position);
  int octalToDecimal(std::string octal);
  int octalToDecimal(char octal);
  int hexToDecimal(std::string hex);
  int hexToDecimal(char hex);
  char getEscapeSequence(std::pair<size_t,size_t> position, std::string &codeString);

  TokenShareType getEofToken();
  TokenShareType getErrorToken();
  TokenShareType getOperatorToken();
  TokenShareType getLToken();
  TokenShareType getIdentifierOrKeywordOrLToken();
  TokenShareType getCharToken(std::pair<size_t,size_t> position, std::string codeString);
  TokenShareType getCharToken();
  TokenShareType getStringToken(std::pair<size_t,size_t> position, std::string codeString);
  TokenShareType getStringToken();
  TokenShareType getIntOrFloatToken();
  TokenShareType getIntOrFloatToken(std::pair<size_t,size_t> position, std::string codeString);

 public:
  LexerParser(std::string fileName);
  TokenShareType getToken();
  TokenShareType nextToken();

};



}