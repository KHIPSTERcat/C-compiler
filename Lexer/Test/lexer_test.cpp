#include "../lexer_parser.h"
#include "../../Catch/catch.h"
#include <fstream>
#define CATCH_CONFIG_MAIN

TEST_CASE( "Lexer", "[lexer]" ) {
  size_t n = 6;

  for (size_t i = 1; i <= n; i++){
    compiler::LexerParser  a(std::to_string(i) + "input.txt");
    std::ofstream out(std::to_string(i) + "result.txt");
    out<<(a.getToken())->toString() << std::endl;
    while (a.getToken()->getType() != compiler::TokenType::kEOF){
      out<<(a.nextToken())->toString() << std::endl;
    }
    out.close();

    std::ifstream in1(std::to_string(i) + "output.txt");
    std::ifstream in2(std::to_string(i) + "result.txt");
    char char1, char2;
    bool flag = true;
    while(!in1.eof() && !in2.eof()){
      in1 >> char1;
      in2 >> char2;
      if (char1 != char2){
        flag = false;
      }
    }
    if (!in1.eof() || !in2.eof()) {
      flag = false;
    }
    SECTION(std::to_string(i) + "result.txt") {
      REQUIRE(flag);
    }
    in1.close();
    in2.close();
  }

}