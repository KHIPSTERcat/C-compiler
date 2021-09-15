#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "../Lexer/Token/lexer_token.h"

namespace compiler{


class CodeReader{
 private:
  size_t buffIterator;
  std::string fileName;
  size_t buffSize;
  size_t readSize;
  size_t linePosition;
  size_t charPosition;
  char* buff;
  FILE *file;

  void openFile (std::string fileName);
  size_t readFromFile();

 public:
  explicit CodeReader(std::string fileName, size_t buffSize = 256);
  char getCodeChar();
  void nextCodeChar();
  void nextSignificantChar();
  compiler::TokenPosition getPosition();
  ~CodeReader();
};


}