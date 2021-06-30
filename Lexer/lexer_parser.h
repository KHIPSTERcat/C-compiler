#pragma once

#include "Token/lexer_token.h"
#include "../Reader/code_reader.h"
#include <iostream>

namespace compiler{

class LexerParser{
 private:
  CodeReader codeReader;
  LexerToken &nowToken;

 public:
  LexerParser(std::string fileName);
  LexerToken &getToken();
  LexerToken &nextToken();

};



}