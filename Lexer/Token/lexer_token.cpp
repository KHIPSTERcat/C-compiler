#include "lexer_token.h"

compiler::LexerToken::LexerToken(std::pair<size_t, size_t> position,
                                 std::string codeString,
                                 compiler::TokenType type):
                                 tokenType(type),
                                 tokenPosition(position),
                                 tokenCodeString(codeString) {

}

std::string compiler::LexerToken::toString() {
  return "All is fine(No)";
}

std::pair<size_t, size_t> compiler::LexerToken::getPosition() {
  return tokenPosition;
}

std::string compiler::LexerToken::getCodeString() {
  return tokenCodeString;
}

compiler::TokenType compiler::LexerToken::getType() {
  return tokenType;
}

std::string compiler::LexerToken::typeToString() {
  switch (getType()){
    case TokenType::kFloat: return "FLOAT";
    case TokenType::kInt: return "INT";
    case TokenType::kIdentifier: return "INDENTIFIER";
    case TokenType::kString: return "STRING";
    case TokenType::kSeparator: return "SEPARATOR";
    case TokenType::kKeyword: return "KEYWORD";
    case TokenType::kEOF: return "EOF";
    case TokenType::kOperator: return "OPERATOR";
    case TokenType::kChar: return "CHAR";
    case TokenType::kNone: return "NONE";
    default: return "ERROR";
  }
}

compiler::IntLexerToken::IntLexerToken(std::pair<size_t, size_t> position,
                                       std::string codeString,
                                       compiler::TokenType type,
                                       int value):
                                       LexerToken(position,codeString,type),
                                       tokenValue(value){
}

int compiler::IntLexerToken::getValue() {
  return tokenValue;
}

std::string compiler::IntLexerToken::toString() {
  return std::to_string(getPosition().first) + " "
  + std::to_string(getPosition().second) + " "
  + typeToString() + " " + std::to_string(getValue())
  + " " + getCodeString();
}

compiler::FloatLexerToken::FloatLexerToken(std::pair<size_t, size_t> position,
                                           std::string codeString,
                                           compiler::TokenType type,
                                           float value):
                                           LexerToken(position,codeString,type),
                                           tokenValue(value){

}

float compiler::FloatLexerToken::getValue() {
  return tokenValue;
}

std::string compiler::FloatLexerToken::toString() {
  return std::to_string(getPosition().first) + " "
      + std::to_string(getPosition().second) + " "
      + typeToString() + " " + std::to_string(getValue())
      + " " + getCodeString();
}

compiler::CharLexerToken::CharLexerToken(std::pair<size_t, size_t> position,
                                         std::string codeString,
                                         compiler::TokenType type,
                                         char value):
                                         LexerToken(position,codeString,type),
                                         tokenValue(value){

}

char compiler::CharLexerToken::getValue() {
  return tokenValue;
}

std::string compiler::CharLexerToken::toString() {
  return std::to_string(getPosition().first) + " "
      + std::to_string(getPosition().second) + " "
      + typeToString() + " " + getValue()
      + " " + getCodeString();
}

compiler::StringLexerToken::StringLexerToken(std::pair<size_t, size_t> position,
                                             std::string codeString,
                                             compiler::TokenType type,
                                             std::string value):
    LexerToken(position,codeString,type),
    tokenValue(value) {

}

std::string compiler::StringLexerToken::getValue() {
  return tokenValue;
}

std::string compiler::StringLexerToken::toString() {
  return std::to_string(getPosition().first) + " "
      + std::to_string(getPosition().second) + " "
      + typeToString() + " " + getValue()
      + " " + getCodeString();
}

compiler::KeywordLexerToken::KeywordLexerToken(std::pair<size_t, size_t> position,
                                             std::string codeString,
                                             compiler::TokenType type,
                                             compiler::KeywordType value):
    LexerToken(position,codeString,type),
    tokenValue(value) {

}

compiler::KeywordType compiler::KeywordLexerToken::getValue() {
  return tokenValue;
}

std::string compiler::KeywordLexerToken::toString() {
  return std::to_string(getPosition().first) + " "
      + std::to_string(getPosition().second) + " "
      + typeToString() + " " +  getCodeString()
      + " " + getCodeString();
}