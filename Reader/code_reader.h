#pragma once

#include <iostream>
#include <string>

namespace compiler{


class CodeReader{
 private:
  size_t buffIterator;


 public:
  char getCodeChar();
  void nextCodeChar();
  void nextSignificantChar();

};


}
