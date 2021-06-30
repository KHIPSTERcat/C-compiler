#include "lexer_parser.h"

compiler::LexerParser::LexerParser(std::string fileName):codeReader(fileName){
  std::pair<size_t, size_t> pos(1,3);
  nowToken = TokenShareType(new CharLexerToken(pos,"0x123", compiler::TokenType::kInt, 'f'));
}

compiler::TokenShareType compiler::LexerParser::getToken() {
  return nowToken;
}

compiler::TokenShareType compiler::LexerParser::nextToken() {
  if (codeReader.getCodeChar() < 33){
    codeReader.nextSignificantChar();
  }

  if (codeReader.getCodeChar() == -1){
    return getEofToken();
  }


  auto tmp = getErrorToken();
  codeReader.nextCodeChar();
  return tmp;
}

compiler::TokenShareType compiler::LexerParser::getEofToken() {
  return TokenShareType(new StringLexerToken(codeReader.getPosition() ,"", compiler::TokenType::kEOF, "EOF"));
}

compiler::TokenShareType compiler::LexerParser::getErrorToken() {
  return TokenShareType(new StringLexerToken(codeReader.getPosition() ,"", compiler::TokenType::kError, "Error"));
}