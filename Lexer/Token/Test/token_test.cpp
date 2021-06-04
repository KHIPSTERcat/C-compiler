#include "../lexer_token.h"
#include "../../../Catch/catch.h"

#define CATCH_CONFIG_MAIN


TEST_CASE( "IntLexerToken", "[token]" ) {
  std::pair<size_t, size_t> pos(1,3);
  compiler::IntLexerToken testToken(pos,"0x123", compiler::TokenType::kInt, 0x123);
  SECTION("getPosition()") {
    REQUIRE(testToken.getPosition().first == pos.first);
    REQUIRE(testToken.getPosition().second == pos.second);
  }
  SECTION("getType()") {
    REQUIRE(testToken.getType() == compiler::TokenType::kInt);
  }
  SECTION("getCodeString()") {
    REQUIRE(testToken.getCodeString() == "0x123");
  }
  SECTION("getValue()") {
    REQUIRE(testToken.getValue() == 0x123);
  }
  SECTION("getPosition()") {
    REQUIRE(testToken.toString() == "1 3 INT 291 0x123");
  }
}

TEST_CASE( "FloatLexerToken", "[token]" ) {
  std::pair<size_t, size_t> pos(12,3);
  compiler::FloatLexerToken testToken(pos,"0.5", compiler::TokenType::kFloat, 0.5);
  SECTION("getPosition()") {
    REQUIRE(testToken.getPosition().first == pos.first);
    REQUIRE(testToken.getPosition().second == pos.second);
  }
  SECTION("getType()") {
    REQUIRE(testToken.getType() == compiler::TokenType::kFloat);
  }
  SECTION("getCodeString()") {
    REQUIRE(testToken.getCodeString() == "0.5");
  }
  SECTION("getValue()") {
    REQUIRE(testToken.getValue() == 0.5);
  }
  SECTION("getPosition()") {
    REQUIRE(testToken.toString() == "12 3 FLOAT 0.500000 0.5");
  }
}

TEST_CASE( "CharLexerToken", "[token]" ) {
  std::pair<size_t, size_t> pos(1,5);
  compiler::CharLexerToken testToken(pos,"'f'", compiler::TokenType::kChar, 'f');
  SECTION("getPosition()") {
    REQUIRE(testToken.getPosition().first == pos.first);
    REQUIRE(testToken.getPosition().second == pos.second);
  }
  SECTION("getType()") {
    REQUIRE(testToken.getType() == compiler::TokenType::kChar);
  }
  SECTION("getCodeString()") {
    REQUIRE(testToken.getCodeString() == "'f'");
  }
  SECTION("getValue()") {
    REQUIRE(testToken.getValue() == 'f');
  }
  SECTION("getPosition()") {
    REQUIRE(testToken.toString() == "1 5 CHAR f 'f'");
  }
}

TEST_CASE( "StringLexerToken", "[token]" ) {
  std::pair<size_t, size_t> pos(10,30);
  compiler::StringLexerToken testToken(pos,"abac", compiler::TokenType::kString, "abac");
  SECTION("getPosition()") {
    REQUIRE(testToken.getPosition().first == pos.first);
    REQUIRE(testToken.getPosition().second == pos.second);
  }
  SECTION("getType()") {
    REQUIRE(testToken.getType() == compiler::TokenType::kString);
  }
  SECTION("getCodeString()") {
    REQUIRE(testToken.getCodeString() == "abac");
  }
  SECTION("getValue()") {
    REQUIRE(testToken.getValue() == "abac");
  }
  SECTION("getPosition()") {
    REQUIRE(testToken.toString() == "10 30 STRING abac abacr");
  }
}