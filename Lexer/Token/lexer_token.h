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
  std::pair<size_t, size_t> tokenPosition;
  std::string tokenCodeString;

 protected:
  std::string typeToString();

 public:
  LexerToken(std::pair<size_t, size_t> position,
             std::string codeString,
             compiler::TokenType type);
  TokenType getType();
  std::pair<size_t, size_t> getPosition();
  std::string getCodeString();
  virtual std::string toString();

};


class IntLexerToken: public LexerToken{
 private:
  int tokenValue;

 public:
  IntLexerToken(std::pair<size_t, size_t> position, std::string codeString, TokenType type, int value);
  int getValue();
  std::string toString() override;

};

class FloatLexerToken: public LexerToken{
 private:
  float tokenValue;

 public:
  FloatLexerToken(std::pair<size_t, size_t> position, std::string codeString, TokenType type, float value);
  float getValue();
  std::string toString() override;

};

class StringLexerToken: public LexerToken{
 private:
  std::string tokenValue;

 public:
  StringLexerToken(std::pair<size_t, size_t> position, std::string codeString, TokenType type, std::string value);
  std::string getValue();
  std::string toString() override;

};

class CharLexerToken: public LexerToken{
 private:
  char tokenValue;

 public:
  CharLexerToken(std::pair<size_t, size_t> position, std::string codeString, TokenType type, char value);
  char getValue();
  std::string toString() override;

};

class KeywordLexerToken: public LexerToken{
 private:
  compiler::KeywordType tokenValue;

 public:
  KeywordLexerToken(std::pair<size_t, size_t> position, std::string codeString, TokenType type, compiler::KeywordType value);
  compiler::KeywordType getValue();
  std::string toString() override;

};

class OperatorLexerToken: public LexerToken{
 private:
  compiler::OperatorType tokenValue;

 public:
  OperatorLexerToken(std::pair<size_t, size_t> position, std::string codeString, TokenType type, compiler::OperatorType value);
  compiler::OperatorType getValue();
  std::string toString() override;

};

}