#include "../lexer_token.h"
#include "../../../Catch/catch.h"

#define CATCH_CONFIG_MAIN


TEST_CASE( "LexerToken", "[token]" ) {
  std::pair<size_t, size_t> pos(1,3);
  compiler::LexerToken testToken(pos,"0x123", compiler::TokenType::kInt);
  SECTION("getPosition()") {
    REQUIRE(testToken.toString() == "All is fine(No)");
  }
}

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
    REQUIRE(testToken.toString() == "10 30 STRING abac abac");
  }

}

TEST_CASE( "typeToString", "[token]" ) {
  std::pair<size_t, size_t> pos(10,30);
  compiler::StringLexerToken testToken0(pos,"abac", compiler::TokenType::kFloat, "abac");
  SECTION("kFloat") {
    REQUIRE(testToken0.toString() == "10 30 FLOAT abac abac");
  }
  compiler::StringLexerToken testToken1(pos,"abac", compiler::TokenType::kInt, "abac");
  SECTION("kInt") {
    REQUIRE(testToken1.toString() == "10 30 INT abac abac");
  }
  compiler::StringLexerToken testToken2(pos,"abac", compiler::TokenType::kIdentifier, "abac");
  SECTION("kIdentifier") {
    REQUIRE(testToken2.toString() == "10 30 INDENTIFIER abac abac");
  }
  compiler::StringLexerToken testToken3(pos,"abac", compiler::TokenType::kString, "abac");
  SECTION("kString") {
    REQUIRE(testToken3.toString() == "10 30 STRING abac abac");
  }
  compiler::StringLexerToken testToken4(pos,"abac", compiler::TokenType::kSeparator, "abac");
  SECTION("kSeparator") {
    REQUIRE(testToken4.toString() == "10 30 SEPARATOR abac abac");
  }
  compiler::StringLexerToken testToken5(pos,"abac", compiler::TokenType::kKeyword, "abac");
  SECTION("kKeyword") {
    REQUIRE(testToken5.toString() == "10 30 KEYWORD abac abac");
  }
  compiler::StringLexerToken testToken6(pos,"abac", compiler::TokenType::kEOF, "abac");
  SECTION("kEOF") {
    REQUIRE(testToken6.toString() == "10 30 EOF abac abac");
  }
  compiler::StringLexerToken testToken7(pos,"abac", compiler::TokenType::kOperator, "abac");
  SECTION("kOperator") {
    REQUIRE(testToken7.toString() == "10 30 OPERATOR abac abac");
  }
  compiler::StringLexerToken testToken8(pos,"abac", compiler::TokenType::kChar, "abac");
  SECTION("kChar") {
    REQUIRE(testToken8.toString() == "10 30 CHAR abac abac");
  }
  compiler::StringLexerToken testToken9(pos,"abac", compiler::TokenType::kNone, "abac");
  SECTION("kNone") {
    REQUIRE(testToken9.toString() == "10 30 NONE abac abac");
  }
  compiler::StringLexerToken testToken10(pos,"abac", compiler::TokenType::kError, "abac");
  SECTION("kError") {
    REQUIRE(testToken10.toString() == "10 30 ERROR abac abac");
  }
}