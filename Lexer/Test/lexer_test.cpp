#include "../lexer_parser.h"

int main(){

  compiler::LexerParser  a("input.txt");
  std::cout<<(a.nextToken())->toString() << std::endl;
  std::cout<<(a.nextToken())->toString();
  return 0;
}