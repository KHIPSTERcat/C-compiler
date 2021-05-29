#include "code_reader.h"

void compiler::CodeReader::openFile(std::string fileName) {
  if ((this->file = std::fopen(fileName.c_str(),"r")) == nullptr){
    throw "Cannot open file.\n";
  }
}

size_t compiler::CodeReader::readFromFile() {
  buffIterator = 0;
  return fread(buff, sizeof(char), buffSize, file);
}

compiler::CodeReader::CodeReader(std::string fileName, size_t buffSize):fileName(fileName),buffSize(buffSize),buffIterator(0),stringPosition(1),charPosition(1),file(
    nullptr) {
  try {
    openFile(fileName);
  } catch (const char* msg) {
    std::cout << msg << std::endl;
    exit(1);
  }
  buff = new char[buffSize];
  readSize = readFromFile();
}

compiler::CodeReader::~CodeReader() {
  delete buff;
}

char compiler::CodeReader::getCodeChar() {
  if (!readSize) return -1;
  return buff[buffIterator];
}

void compiler::CodeReader::nextCodeChar() {
  if (readSize){
    if (getCodeChar() == '\n'){
      stringPosition++;
      charPosition = 1;
    } else {
      charPosition++;
    }
    buffIterator++;
    if (buffIterator == readSize){
      readSize = readFromFile();
    }
  }
}

void compiler::CodeReader::nextSignificantChar() {
  nextCodeChar();
  while (true){
    switch (getCodeChar()) {
      case ' ':
        nextCodeChar();
        break;
      case '\n':
        nextCodeChar();
        break;
      default:
        return;
    }
  }
}

std::pair<size_t, size_t> compiler::CodeReader::getPosition() {
  return std::pair<size_t, size_t>(stringPosition,charPosition);
}