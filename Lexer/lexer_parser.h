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

  TokenShareType getEofToken();
  TokenShareType getErrorToken();

 public:
  LexerParser(std::string fileName);
  TokenShareType getToken();
  TokenShareType nextToken();

};



}