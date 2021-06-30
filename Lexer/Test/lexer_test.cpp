#include "../lexer_parser.h"

int main(){

  compiler::LexerParser  a("input.txt");
  while (a.getToken()->getType() != compiler::TokenType::kEOF){
    std::cout<<(a.nextToken())->toString() << std::endl;
  }


  return 0;
}