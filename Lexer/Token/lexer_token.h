#pragma once
#include <iostream>

namespace compiler{

enum class TokenType {
  kNone = 0,
  kInt,
  kFloat,
  kChar,
  kString,
  kIdentifier,
  kKeyword,
  kOperator,
  kEOF,
  kSeparator,
  kError,
};

typedef struct TokenPosition{
  size_t line, character;
  TokenPosition(size_t line,size_t character);
} TokenPosition;

enum class OperatorType {
  kLeftSquareBracket = 0,
  kRightSquareBracket,
  kLeftBracket,
  kRightBracket,
  kDot,
  kArrow,
  kPlusPlus,
  kMinusMinus,
  kAmpersand,
  kStar,
  kPlus,
  kMinus,
  kTilda,
  kExclamationPoint,
  kSlash,
  kPercent,
  kDoubleArrowLeftBracket,
  kDoubleArrowRightBracket,
  kArrowLeftBracket,
  kArrowRightBracket,
  kLessOrEqual,
  kMoreOrEqual,
  kDoubleEqual,
  kUnEqual,
  kCaret,
  kVerticalLine,
  kDoubleAmpersand,
  kDoubleVerticalLine,
  kQuestionSign,
  kColon,
  kEqual,
  kStarEqual,
  kSlashEqual,
  kPercentEqual,
  kPlusEqual,
  kMinusEqual,
  kDoubleArrowLeftBracketEqual,
  kDoubleArrowRightBracketEqual,
  kAmpersandEqual,
  kCaretEqual,
  kVerticalLineEqual,
  kComma,
  kNumberSign,
  kDoubleNumberSign,
  kColonArrowRightBracket,
  kLeftFigureBracket,
  kRightFigureBracket,
  kSemicolon,
};

enum class KeywordType {
  kAuto = 0,
  kDouble,
  kInt,
  kStruct,
  kBreak,
  kElse,
  kLong,
  kSwitch,
  kCase,
  kEnum,
  kRegister,
  kTypedef,
  kChar,
  kExtern,
  kReturn,
  kUnion,
  kConst,
  kFloat,
  kShort,
  kUnsigned,
  kContinue,
  kFor,
  kSigned,
  kVoid,
  kDefault,
  kGoto,
  kSizeof,
  kVolatile,
  kDo,
  kIf,
  kStatic,
  kWhile,
};

class LexerToken{
 private:
  TokenType tokenType;
//  std::pair<size_t, size_t> tokenPosition;
  compiler::TokenPosition tokenPosition;
  std::string tokenCodeString;

 protected:
  std::string typeToString();

 public:
  LexerToken(compiler::TokenPosition position,
             std::string codeString,
             compiler::TokenType type);
  TokenType getType();
  compiler::TokenPosition getPosition();
  std::string getCodeString();
  virtual std::string toString();

};


class IntLexerToken: public LexerToken{
 private:
  int tokenValue;

 public:
  IntLexerToken(compiler::TokenPosition position, std::string codeString, TokenType type, int value);
  int getValue();
  std::string toString() override;

};

class FloatLexerToken: public LexerToken{
 private:
  double tokenValue;

 public:
  FloatLexerToken(compiler::TokenPosition position, std::string codeString, TokenType type, double value);
  double getValue();
  std::string toString() override;

};

class StringLexerToken: public LexerToken{
 private:
  std::string tokenValue;

 public:
  StringLexerToken(compiler::TokenPosition position, std::string codeString, TokenType type, std::string value);
  std::string getValue();
  std::string toString() override;

};

class CharLexerToken: public LexerToken{
 private:
  char tokenValue;

 public:
  CharLexerToken(compiler::TokenPosition position, std::string codeString, TokenType type, char value);
  char getValue();
  std::string toString() override;

};

class KeywordLexerToken: public LexerToken{
 private:
  compiler::KeywordType tokenValue;

 public:
  KeywordLexerToken(compiler::TokenPosition, std::string codeString, TokenType type, compiler::KeywordType value);
  compiler::KeywordType getValue();
  std::string toString() override;

};

class OperatorLexerToken: public LexerToken{
 private:
  compiler::OperatorType tokenValue;

 public:
  OperatorLexerToken(compiler::TokenPosition, std::string codeString, TokenType type, compiler::OperatorType value);
  compiler::OperatorType getValue();
  std::string toString() override;

};

}