#include "lexer_parser.h"

compiler::LexerParser::LexerParser(std::string fileName):codeReader(fileName){
  std::string keywords[32] = {"auto","double","int","struct",
                              "break","else","long","switch",
                              "case","enum","register","typedef",
                              "char","extern","return","union",
                              "const","float","short","unsigned",
                              "continue","for","signed","void",
                              "default","goto","sizeof","volatile",
                              "do","if","static","while"};
  compiler::KeywordType keywordTypes[32] = {compiler::KeywordType::kAuto, compiler::KeywordType::kDouble,
                                            compiler::KeywordType::kInt, compiler::KeywordType::kStruct,
                                            compiler::KeywordType::kBreak, compiler::KeywordType::kElse,
                                            compiler::KeywordType::kLong, compiler::KeywordType::kSwitch,
                                            compiler::KeywordType::kCase, compiler::KeywordType::kEnum,
                                            compiler::KeywordType::kRegister, compiler::KeywordType::kTypedef,
                                            compiler::KeywordType::kChar, compiler::KeywordType::kExtern,
                                            compiler::KeywordType::kReturn, compiler::KeywordType::kUnion,
                                            compiler::KeywordType::kConst, compiler::KeywordType::kFloat,
                                            compiler::KeywordType::kShort, compiler::KeywordType::kUnsigned,
                                            compiler::KeywordType::kContinue, compiler::KeywordType::kFor,
                                            compiler::KeywordType::kSigned, compiler::KeywordType::kVoid,
                                            compiler::KeywordType::kDefault, compiler::KeywordType::kGoto,
                                            compiler::KeywordType::kSizeof, compiler::KeywordType::kVolatile,
                                            compiler::KeywordType::kDo, compiler::KeywordType::kIf,
                                            compiler::KeywordType::kStatic, compiler::KeywordType::kWhile};
  std::string operators[48] = {"[", "]", "(", ")", ".", "->", "++", "--", "&", "*", "+", "-",
                               "~", "!", "/", "%", "<<", ">>", "<", ">", "<=",
                               ">=", "==", "!=", "^", "|", "&&", "||", "?", ":", "=", "*=",
                               "/=", "%=", "+=", "-=", "<<=", ">>=", "&=",
                               "^=", "|=", ",", "#", "##", ":>", "{", "}", ";"};

  compiler::OperatorType operatorTypes[48] = {compiler::OperatorType::kLeftSquareBracket, compiler::OperatorType::kRightSquareBracket,
                                              compiler::OperatorType::kLeftBracket, compiler::OperatorType::kRightBracket,
                                              compiler::OperatorType::kDot, compiler::OperatorType::kArrow,
                                              compiler::OperatorType::kPlusPlus, compiler::OperatorType::kMinusMinus,
                                              compiler::OperatorType::kAmpersand, compiler::OperatorType::kStar,
                                              compiler::OperatorType::kPlus, compiler::OperatorType::kMinus,
                                              compiler::OperatorType::kTilda, compiler::OperatorType::kExclamationPoint,
                                              compiler::OperatorType::kSlash, compiler::OperatorType::kPercent,
                                              compiler::OperatorType::kDoubleArrowLeftBracket, compiler::OperatorType::kDoubleArrowRightBracket,
                                              compiler::OperatorType::kArrowLeftBracket, compiler::OperatorType::kArrowRightBracket,
                                              compiler::OperatorType::kLessOrEqual, compiler::OperatorType::kMoreOrEqual,
                                              compiler::OperatorType::kDoubleEqual, compiler::OperatorType::kUnEqual,
                                              compiler::OperatorType::kCaret, compiler::OperatorType::kVerticalLine,
                                              compiler::OperatorType::kDoubleAmpersand, compiler::OperatorType::kDoubleVerticalLine,
                                              compiler::OperatorType::kQuestionSign, compiler::OperatorType::kColon,
                                              compiler::OperatorType::kEqual, compiler::OperatorType::kStarEqual,
                                              compiler::OperatorType::kSlashEqual, compiler::OperatorType::kPercentEqual,
                                              compiler::OperatorType::kPlusEqual, compiler::OperatorType::kMinusEqual,
                                              compiler::OperatorType::kDoubleArrowLeftBracketEqual, compiler::OperatorType::kDoubleArrowRightBracketEqual,
                                              compiler::OperatorType::kAmpersandEqual, compiler::OperatorType::kCaretEqual,
                                              compiler::OperatorType::kVerticalLineEqual, compiler::OperatorType::kComma,
                                              compiler::OperatorType::kNumberSign, compiler::OperatorType::kDoubleNumberSign,
                                              compiler::OperatorType::kColonArrowRightBracket, compiler::OperatorType::kLeftFigureBracket,
                                              compiler::OperatorType::kRightFigureBracket, compiler::OperatorType::kSemicolon,};

  for (size_t i = 0; i < 32; i++){
    keywordDictionary[keywords[i]] = keywordTypes[i];
  }
  for (size_t i = 0; i < 48; i++){
    operatorDictionary[operators[i]] = operatorTypes[i];
  }

  nowToken = nextToken();
}

compiler::TokenShareType compiler::LexerParser::getToken() {
  return nowToken;
}



compiler::TokenShareType compiler::LexerParser::nextToken() {
  if (codeReader.getCodeChar() <= ' '){
    codeReader.nextSignificantChar();
  }

  if (codeReader.getCodeChar() == -1){
    nowToken = getEofToken();
    return nowToken;
  } else if (operatorDictionary.count(std::string(1, codeReader.getCodeChar()))){
    nowToken = getOperatorToken();
    return nowToken;
  } else if (codeReader.getCodeChar() == '\''){
    nowToken = getCharToken();
    return nowToken;
  } else if (codeReader.getCodeChar() == '\"'){
    nowToken = getStringToken();
    return nowToken;
  } else if (isNoNumber(codeReader.getCodeChar())) {
    nowToken = getIdentifierOrKeywordOrLToken();
    return nowToken;
  } else if (isNumber(codeReader.getCodeChar())) {
    nowToken = getIntOrFloatToken();
    return nowToken;
  }


  nowToken = getErrorToken();
  codeReader.nextSignificantChar();
  return nowToken;
}



compiler::TokenShareType compiler::LexerParser::getEofToken() {
  return TokenShareType(new StringLexerToken(codeReader.getPosition() ,"", compiler::TokenType::kEOF, "EOF"));
}

compiler::TokenShareType compiler::LexerParser::getErrorToken() {
  return TokenShareType(new StringLexerToken(codeReader.getPosition() ,"", compiler::TokenType::kError, "Error"));
}


bool compiler::LexerParser::isNumber(char sign) {
  return sign >= '0' && sign <= '9';
}

bool compiler::LexerParser::isNoNumber(char sign) {
  return (sign >= 'a' && sign <= 'z') || (sign >= 'A' && sign <= 'Z') || sign == '_';
}


compiler::TokenShareType compiler::LexerParser::getOperatorToken() {
  std::string codeString = "";
  auto position = codeReader.getPosition();
  codeString.push_back(codeReader.getCodeChar());
  codeReader.nextCodeChar();
  if (isNumber(codeReader.getCodeChar())) {
    return getIntOrFloatToken(position, codeString);
  }
  if (codeReader.getCodeChar() == '*'){
    multiLineCommentSkip(position);
    return nextToken();
  }
  if (codeReader.getCodeChar() == '/'){
    lineCommentSkip();
    return nextToken();
  }
  while (operatorDictionary.count(codeString + codeReader.getCodeChar())){
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
  }
  return TokenShareType(new OperatorLexerToken(position ,codeString,
                                             compiler::TokenType::kOperator, operatorDictionary[codeString]));
}

void compiler::LexerParser::lineCommentSkip() {
  while (codeReader.getCodeChar() != '\n' && codeReader.getCodeChar() != -1){
    codeReader.nextCodeChar();
  }
  codeReader.nextCodeChar();
}

void compiler::LexerParser::multiLineCommentSkip(std::pair<size_t,size_t> &position) {
  while (codeReader.getCodeChar() != -1){
    codeReader.nextCodeChar();
    if (codeReader.getCodeChar() == '*'){
      codeReader.nextCodeChar();
      if (codeReader.getCodeChar() == '/'){
        codeReader.nextCodeChar();
        return;
      }
    }
  }

  if (codeReader.getCodeChar() == -1){
    std::cout << "Not a closed comment on "+ std::to_string(position.first) + " "
        + std::to_string(position.second) + ".";
    exit(1);
  }
}


int compiler::LexerParser::octalToDecimal(std::string octal) {
  int result = 0;
  for (auto i : octal){
    result *= 8;
    result += octalToDecimal(i);
  }
  return result;
}

int compiler::LexerParser::octalToDecimal(char octal) {
  if (octal >= '0' && octal <= '7'){
    return octal - 48;
  }
  return -1;
}

int compiler::LexerParser::hexToDecimal(std::string hex) {
  int result = 0;
  for (auto i : hex){
    result *= 16;
    result += hexToDecimal(i);
  }
  return result;
}

int compiler::LexerParser::hexToDecimal(char hex) {
  hex = tolower(hex);
  if (hex >= '0' && hex <= '9'){
    return hex - 48;
  } else if (hex <= 'f' && hex >= 'a'){
    return hex - 97 + 10;
  }
  return -1;
}


char compiler::LexerParser::getEscapeSequence(std::pair<size_t, size_t> position, std::string &codeString) {
  std::string escapeSequence = "";
  escapeSequence.push_back(codeReader.getCodeChar());
  codeString.push_back(codeReader.getCodeChar());
  if (codeReader.getCodeChar() != '\\') {
    std::cout << "Unknown escape sequence: " + escapeSequence + "on " + std::to_string(position.first) + " "
        + std::to_string(position.second);
    exit(1);
  }

  codeReader.nextCodeChar();
  escapeSequence.push_back(codeReader.getCodeChar());
  codeString.push_back(codeReader.getCodeChar());
  switch (codeReader.getCodeChar()) {
    case 'n':{
      codeReader.nextCodeChar();
      return '\n';
    }
    case 't':{
      codeReader.nextCodeChar();
      return '\t';
    }
    case 'v':{
      codeReader.nextCodeChar();
      return '\v';
    }
    case 'b':{
      codeReader.nextCodeChar();
      return '\b';
    }
    case 'r':{
      codeReader.nextCodeChar();
      return '\r';
    }
    case 'f':{
      codeReader.nextCodeChar();
      return '\f';
    }
    case 'a':{
      codeReader.nextCodeChar();
      return '\a';
    }
    case '\'':{
      codeReader.nextCodeChar();
      return '\'';
    }
    case '\"':{
      codeReader.nextCodeChar();
      return '\"';
    }
    case '\\':{
      codeReader.nextCodeChar();
      return '\\';
    }
    case '\?':{
      codeReader.nextCodeChar();
      return '\?';
    }
    case 'x':{
      std::string hexNumber = "";
      codeReader.nextCodeChar();
      for (size_t i = 0; i < 3; i++){


        if (hexToDecimal(codeReader.getCodeChar()) == -1){
          if (!i){
            std::cout << escapeSequence + "used with no following hex digits on " + std::to_string(position.first) + " "
                + std::to_string(position.second) ;
            exit(1);
          }

          break;
        }
        hexNumber.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
      }
      codeString += hexNumber;
      escapeSequence += hexNumber;
      int hexInt = hexToDecimal(hexNumber);
      if (hexInt < 0  || hexInt > 128){
        std::cout << escapeSequence << "out of range on " << position.first << " "
            << std::to_string(position.second) ;
        exit(1);
      }
      return char(hexInt);
    }
    default:{
      if (octalToDecimal(codeReader.getCodeChar()) != -1){
        std::string octalNumber = "";
        octalNumber.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
        for (size_t i = 0; i < 2; i++){
          if (hexToDecimal(codeReader.getCodeChar()) == -1){
            if (!i){
              std::cout << escapeSequence + "used with no following octal digits on " + std::to_string(position.first) + " "
                  + std::to_string(position.second) ;
              exit(1);
            }

            break;
          }
          escapeSequence.push_back(codeReader.getCodeChar());
          codeString.push_back(codeReader.getCodeChar());
          octalNumber.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
        }
        int octalInt = octalToDecimal(octalNumber);
        if (octalInt < 0  || octalInt > 128){
          std::cout << escapeSequence + "out of range on " + std::to_string(position.first) + " "
              + std::to_string(position.second) ;
          exit(1);
        }


        return char(octalInt);
      }
      std::cout << "Unknown escape sequence: " + escapeSequence + " on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
  }
}

compiler::TokenShareType compiler::LexerParser::getLToken() {
  std::string codeString = "L";
  auto position = codeReader.getPosition();
  if (codeReader.getCodeChar() == '\''){
    return getCharToken(position, codeString);
  }
  return getStringToken(position, codeString);
}

compiler::TokenShareType compiler::LexerParser::getCharToken() {
  return getCharToken(codeReader.getPosition(),"");
}


compiler::TokenShareType compiler::LexerParser::getCharToken(std::pair<size_t, size_t> position, std::string codeString) {
  if (codeReader.getCodeChar() != '\''){
    std::cout << "Unknown constant char on " + std::to_string(position.first) + " "
        + std::to_string(position.second);
    exit(1);
  }
  codeString.push_back(codeReader.getCodeChar());
  codeReader.nextCodeChar();
  char value;
  switch (codeReader.getCodeChar()) {
    case '\'':{
      std::cout << "Empty constant char on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    case '\n':{
      std::cout << "Unknown constant char on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    case -1:{
      std::cout << "Unknown constant char on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    case '/':{
      std::cout << "Unknown constant char on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    case '\\':{
      value = getEscapeSequence(codeReader.getPosition(),codeString);
      break;
    }
    default:{
      codeString.push_back(codeReader.getCodeChar());
      value = codeReader.getCodeChar();
      codeReader.nextCodeChar();
      break;
    }
  }

  if (codeReader.getCodeChar() == '\''){
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextSignificantChar();
    return TokenShareType(new CharLexerToken(position ,codeString,
                                               compiler::TokenType::kChar, value));
  }
  std::cout << "Multi-char constant char on " + std::to_string(position.first) + " "
      + std::to_string(position.second);
  exit(1);
}

compiler::TokenShareType compiler::LexerParser::getStringToken() {
  return getStringToken(codeReader.getPosition(),"");
}


compiler::TokenShareType compiler::LexerParser::getStringToken(std::pair<size_t, size_t> position, std::string codeString) {
  if (codeReader.getCodeChar() != '\"'){
    std::cout << "Unknown string on " + std::to_string(position.first) + " "
        + std::to_string(position.second);
    exit(1);
  }
  codeString.push_back(codeReader.getCodeChar());
  codeReader.nextCodeChar();
  std::string value = "";
  for (;codeReader.getCodeChar() != '\"';){
    switch (codeReader.getCodeChar()) {
      case '\n':{
        std::cout << "Unknown string on " + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }
      case -1:{
        std::cout << "Unknown string on " + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }
      case '\\':{
        value.push_back(getEscapeSequence(codeReader.getPosition(),codeString));
        break;
      }
      default:{
        value.push_back(codeReader.getCodeChar());
        codeString.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
        break;
      }
    }
  }
  codeString.push_back(codeReader.getCodeChar());
  codeReader.nextCodeChar();
  return TokenShareType(new StringLexerToken(position ,codeString,
                                           compiler::TokenType::kString, value));
}

compiler::TokenShareType compiler::LexerParser::getIdentifierOrKeywordOrLToken() {
  auto position = codeReader.getPosition();
  std::string value = "";
  std::string codeString = "";
  if (codeReader.getCodeChar() == 'L'){
    value.push_back(codeReader.getCodeChar());
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
    if (codeReader.getCodeChar() == '\'' || codeReader.getCodeChar() == '\"')
      return getLToken();
  }
  for (;isNoNumber(codeReader.getCodeChar()) || isNumber(codeReader.getCodeChar());){
    value.push_back(codeReader.getCodeChar());
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
  }

  if (keywordDictionary.count(value)){
    return TokenShareType(new KeywordLexerToken(position ,codeString,
                                               compiler::TokenType::kKeyword, keywordDictionary[value]));
  }
  return TokenShareType(new StringLexerToken(position ,codeString,
                                             compiler::TokenType::kIdentifier, value));
}


compiler::TokenShareType compiler::LexerParser::getIntOrFloatToken() {
  return getIntOrFloatToken(codeReader.getPosition(), "");
}

compiler::TokenShareType compiler::LexerParser::getIntOrFloatToken(std::pair<size_t,size_t> position, std::string codeString) {
  bool isOctal = true;
  std::string value = "";

  if (!codeString.empty()){
    for (;isNumber(codeReader.getCodeChar());) {
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
    if (tolower(codeReader.getCodeChar()) == 'e'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
      if (codeReader.getCodeChar() == '+' || codeReader.getCodeChar() == '-'){
        codeString.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
      }
      if (isNumber(codeReader.getCodeChar())){
        for (;isNumber(codeReader.getCodeChar());) {
          codeString.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
        }
      } else {
        std::cout << "Exponent has no digits" + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }
    }
    if (tolower(codeReader.getCodeChar()) == 'l' || tolower(codeReader.getCodeChar()) == 'f'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
    if (codeReader.getCodeChar() == '.'){
      std::cout << "To many decimal points in number on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    if (isNoNumber(codeReader.getCodeChar())){
      std::cout << "Unknown float number on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    return TokenShareType(new FloatLexerToken(position ,codeString,
                                               TokenType::kFloat, std::stof(codeString)));
  }

  if (codeReader.getCodeChar() == '0'){
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
    if (tolower(codeReader.getCodeChar()) == 'x'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
      if (hexToDecimal(codeReader.getCodeChar()) == -1){
        std::cout << "Invalid int suffix on " + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }
      for (;hexToDecimal(codeReader.getCodeChar()) != -1;) {
        value.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
      }
      codeString += value;
      if (tolower(codeReader.getCodeChar()) == 'l'){
        codeString.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
        if (tolower(codeReader.getCodeChar()) == 'u'){
          codeString.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
        }
      } else {
        if (tolower(codeReader.getCodeChar()) == 'u'){
          codeString.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
          if (tolower(codeReader.getCodeChar()) == 'l'){
            codeString.push_back(codeReader.getCodeChar());
            codeReader.nextCodeChar();
          }
        }
      }
      if (isNoNumber(codeReader.getCodeChar())){
        std::cout << "Invalid int suffix on " + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }
      if (codeReader.getCodeChar() == '.'){
        std::cout << "Invalid int on " + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }

      return TokenShareType(new IntLexerToken(position ,codeString,
                                              TokenType::kInt, hexToDecimal(value)));
    }
    for (;isNumber(codeReader.getCodeChar());) {
      if (octalToDecimal(codeReader.getCodeChar()) == -1){
        isOctal = false;
      }
      codeString.push_back(codeReader.getCodeChar());
      value.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
  }

  for (;isNumber(codeReader.getCodeChar());) {
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
  }

  if (codeReader.getCodeChar() == '.'){
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
    for (;isNumber(codeReader.getCodeChar());) {
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }

    if (tolower(codeReader.getCodeChar()) == 'e'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
      if (codeReader.getCodeChar() == '+' || codeReader.getCodeChar() == '-'){
        codeString.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
      }
      if (isNumber(codeReader.getCodeChar())){
        for (;isNumber(codeReader.getCodeChar());) {
          codeString.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
        }
      } else {
        std::cout << "Exponent has no digits" + std::to_string(position.first) + " "
            + std::to_string(position.second);
        exit(1);
      }
    }
    if (tolower(codeReader.getCodeChar()) == 'l' || tolower(codeReader.getCodeChar()) == 'f'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
    if (codeReader.getCodeChar() == '.'){
      std::cout << "To many decimal points in number on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    if (isNoNumber(codeReader.getCodeChar())){
      std::cout << "Invalid float suffix on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    return TokenShareType(new FloatLexerToken(position ,codeString,
                                              TokenType::kFloat, std::stof(codeString)));
  }

  if (tolower(codeReader.getCodeChar()) == 'e'){
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
    if (codeReader.getCodeChar() == '+' || codeReader.getCodeChar() == '-'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
    if (isNumber(codeReader.getCodeChar())){
      for (;isNumber(codeReader.getCodeChar());) {
        codeString.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
      }
    } else {
      std::cout << "Exponent has no digits" + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    if (tolower(codeReader.getCodeChar()) == 'l' || tolower(codeReader.getCodeChar()) == 'f'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
    if (codeReader.getCodeChar() == '.'){
      std::cout << "To many decimal points in number on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    if (isNoNumber(codeReader.getCodeChar())){
      std::cout << "Invalid float suffix on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
    return TokenShareType(new FloatLexerToken(position ,codeString,
                                              TokenType::kFloat, std::stof(codeString)));
  }

  if (tolower(codeReader.getCodeChar()) == 'l'){
    codeString.push_back(codeReader.getCodeChar());
    codeReader.nextCodeChar();
    if (tolower(codeReader.getCodeChar()) == 'u'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
    }
  } else {
    if (tolower(codeReader.getCodeChar()) == 'u'){
      codeString.push_back(codeReader.getCodeChar());
      codeReader.nextCodeChar();
      if (tolower(codeReader.getCodeChar()) == 'l'){
        codeString.push_back(codeReader.getCodeChar());
        codeReader.nextCodeChar();
      }
    }
  }

  if (codeString[0] == '0'){
    if (isOctal){
      return TokenShareType(new IntLexerToken(position ,codeString,
                                              TokenType::kInt, octalToDecimal(value)));
    } else {
      std::cout << "Invalid octal number on " + std::to_string(position.first) + " "
          + std::to_string(position.second);
      exit(1);
    }
  }



  if (isNoNumber(codeReader.getCodeChar())){
    std::cout << "Invalid int suffix on " + std::to_string(position.first) + " "
        + std::to_string(position.second);
    exit(1);
  }
  return TokenShareType(new IntLexerToken(position ,codeString,
                                            TokenType::kInt, std::stoi(codeString)));
}