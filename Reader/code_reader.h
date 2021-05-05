#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace compiler{


class CodeReader{
 private:
  size_t buffIterator;
  std::string fileName;
  size_t buffSize;
  size_t readSize;
  char* buff;
  FILE *file;

  void openFile (std::string fileName);
  size_t readFromFile();

 public:
  CodeReader(std::string fileName, size_t buffSize = 256);
  char getCodeChar();
  void nextCodeChar();
  void nextSignificantChar();
  ~CodeReader();
};


}
