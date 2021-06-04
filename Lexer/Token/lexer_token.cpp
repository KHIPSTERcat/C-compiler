#include "lexer_token.h"

std::pair<size_t, size_t> compiler::LexerToken::getPosition() {
  return tokenPosition;
}

std::string compiler::LexerToken::getCodeString() {
  return tokenCodeString;
}

TokenType compiler::LexerToken::getType() {
  return tokenType;
}

compiler::IntLexerToken::IntLexerToken(std::pair<size_t, size_t> position,
                                       std::string codeString,
                                       compiler::TokenType type,
                                       int value): tokenType(type),
                                       tokenPosition(position),
                                       tokenCodeString(codeString),
                                       tokenValue(value){
}

int compiler::IntLexerToken::getValue() {
  return tokenValue;
}

compiler::FloatLexerToken::FloatLexerToken(std::pair<size_t, size_t> position,
                                           std::string codeString,
                                           compiler::TokenType type,
                                           float value): tokenType(type),
                                           tokenPosition(position),
                                           tokenCodeString(codeString),
                                           tokenValue(value) {

}

float compiler::FloatLexerToken::getValue() {
  return tokenValue;
}

compiler::CharLexerToken::CharLexerToken(std::pair<size_t, size_t> position,
                                         std::string codeString,
                                         compiler::TokenType type,
                                         char value): tokenType(type),
                                         tokenPosition(position),
                                         tokenCodeString(codeString),
                                         tokenValue(value) {

}

float compiler::FloatLexerToken::getValue() {
  return tokenValue;
}

compiler::StringLexerToken::StringLexerToken(std::pair<size_t, size_t> position,
                                             std::string codeString,
                                             compiler::TokenType type,
                                             std::string value): tokenType(type),
                                             tokenPosition(position),
                                             tokenCodeString(codeString),
                                             tokenValue(value) {

}

std::string compiler::StringLexerToken::getValue() {
  return tokenValue;
}