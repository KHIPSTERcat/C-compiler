#include "../lexer_token.h"


int main(){
  compiler::IntLexerToken token(std::pair<size_t, size_t>(1,1),"int",compiler::TokenType::kInt,10);
  std::string a = std::to_string(token.getPosition().first) + " " + std::to_string(token.getPosition().second) + " " + std::to_string(token.getValue()) + " " + token.getCodeString();
  std::cout<<a << std::endl << token.toString();
}