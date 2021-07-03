#include "../lexer_parser.h"

int main(){


  compiler::LexerParser  a("input.txt");
  std::cout<<(a.getToken())->toString() << std::endl;
  while (a.getToken()->getType() != compiler::TokenType::kEOF){
    std::cout<<(a.nextToken())->toString() << std::endl;
  }


  return 0;
}