#include "../Catch/catch.h"
#include "code_reader.h"
#define CATCH_CONFIG_MAIN

compiler::CodeReader Reader("input.txt");

TEST_CASE( "Reader Test", "[reader]" ) {

  SECTION("getCodeChar()"){
    REQUIRE( Reader.getCodeChar() == 'a' );
    REQUIRE( Reader.getPosition().first == 1);
    REQUIRE( Reader.getPosition().second == 1);
    Reader.nextCodeChar();
    REQUIRE( Reader.getCodeChar() == 's' );
    Reader.nextCodeChar();
    REQUIRE( Reader.getPosition().first == 1);
    REQUIRE( Reader.getPosition().second == 3);
    REQUIRE( Reader.getCodeChar() == ' ' );
  }
  SECTION("nextSignificantChar()"){
    Reader.nextSignificantChar();
    REQUIRE( Reader.getCodeChar() == '2' );
    Reader.nextSignificantChar();
    REQUIRE( Reader.getCodeChar() == '3' );
    Reader.nextSignificantChar();
    REQUIRE( Reader.getCodeChar() == '1' );
  }
  SECTION("nextSignificantChar() -> nextCodeChar()"){
    Reader.nextCodeChar();
    REQUIRE( Reader.getPosition().first == 2);
    REQUIRE( Reader.getPosition().second == 2);
    REQUIRE( Reader.getCodeChar() == '2' );
  }

  SECTION("End of File"){
    Reader.nextCodeChar();
    REQUIRE( Reader.getCodeChar() == -1 );
    Reader.nextSignificantChar();
    REQUIRE( Reader.getCodeChar() == -1 );
  }

}