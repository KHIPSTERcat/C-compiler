#include "lexer_parser.h"

compiler::LexerParser::LexerParser(std::string fileName):codeReader(fileName){
  dictionary["auto"] = compiler::TokenType::kKeyword;
  dictionary["double"] = compiler::TokenType::kKeyword;
  dictionary["int"] = compiler::TokenType::kKeyword;
  dictionary["struct"] = compiler::TokenType::kKeyword;
  dictionary["break"] = compiler::TokenType::kKeyword;
  dictionary["else"] = compiler::TokenType::kKeyword;
  dictionary["long"] = compiler::TokenType::kKeyword;
  dictionary["switch"] = compiler::TokenType::kKeyword;
  dictionary["case"] = compiler::TokenType::kKeyword;
  dictionary["enum"] = compiler::TokenType::kKeyword;
  dictionary["register"] = compiler::TokenType::kKeyword;
  dictionary["typedef"] = compiler::TokenType::kKeyword;
  dictionary["char"] = compiler::TokenType::kKeyword;
  dictionary["extern"] = compiler::TokenType::kKeyword;
  dictionary["return"] = compiler::TokenType::kKeyword;
  dictionary["union"] = compiler::TokenType::kKeyword;
  dictionary["const"] = compiler::TokenType::kKeyword;
  dictionary["float"] = compiler::TokenType::kKeyword;
  dictionary["short"] = compiler::TokenType::kKeyword;
  dictionary["unsigned"] = compiler::TokenType::kKeyword;
  dictionary["continue"] = compiler::TokenType::kKeyword;
  dictionary["for"] = compiler::TokenType::kKeyword;
  dictionary["signed"] = compiler::TokenType::kKeyword;
  dictionary["void"] = compiler::TokenType::kKeyword;
  dictionary["default"] = compiler::TokenType::kKeyword;
  dictionary["goto"] = compiler::TokenType::kKeyword;
  dictionary["sizeof"] = compiler::TokenType::kOperator;
  dictionary["volatile"] = compiler::TokenType::kKeyword;
  dictionary["do"] = compiler::TokenType::kKeyword;
  dictionary["if"] = compiler::TokenType::kKeyword;
  dictionary["static"] = compiler::TokenType::kKeyword;
  dictionary["while"] = compiler::TokenType::kKeyword;
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
  } else if (operatorType(codeReader.getCodeChar())){
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

int compiler::LexerParser::operatorType(char sign) {
  switch (sign) {
    case '!': return 14;
    case '#': return 9;
    case '%': return 14;
    case '&': return 11;
    case '(': return 1;
    case ')': return 1;
    case '*': return 12;
    case '+': return 4;
    case ',': return 1;
    case '-': return 5;
    case '.': return 15;
    case ':': return 10;
    case ';': return 1;
    case '<': return 7;
    case '>': return 6;
    case '=': return 3;
    case '?': return 2;
    case '/': return 13;
    case ']': return 1;
    case '[': return 1;
    case '{': return 1;
    case '}': return 1;
    case '^': return 14;
    case '~': return 2;
    case '|': return 8;
    default: return 0;
  }
}

bool compiler::LexerParser::isNumber(char sign) {
  if (sign >= '0' && sign <= '9') return true;
  return false;
}

bool compiler::LexerParser::isNoNumber(char sign) {
  if ((sign >= 'a' && sign <= 'z') || (sign >= 'A' && sign <= 'Z') || sign == '_') return true;
  return false;
}

compiler::TokenShareType compiler::LexerParser::getOperatorToken(std::pair<size_t, size_t> &position, std::string &codeString) {
  codeString.push_back(codeReader.getCodeChar());
  codeReader.nextCodeChar();
  switch (operatorType(codeReader.getCodeChar())) {
    case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                       compiler::TokenType::kOperator, codeString));
    case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                       compiler::TokenType::kOperator, codeString));
    default: {
      std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
          + std::to_string(position.second) + "!";
      exit(1);
    }
  }
}

compiler::TokenShareType compiler::LexerParser::getOperatorToken() {
  std::string codeString = "";
  auto position = codeReader.getPosition();
  codeString.push_back(codeReader.getCodeChar());
  switch (operatorType(codeReader.getCodeChar())) {
    case 1: {
      codeReader.nextCodeChar();
      return TokenShareType(new StringLexerToken(position ,codeString, compiler::TokenType::kOperator, codeString));
    }

    case 2: {
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 3:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 4:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        case 4:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 5:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        case 5:{
          return getOperatorToken(position, codeString);
        }
        case 6:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 6:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        case 6:{
          codeString.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
          switch (operatorType(codeReader.getCodeChar())) {
            case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                               compiler::TokenType::kOperator, codeString));
            case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                               compiler::TokenType::kOperator, codeString));
            case 3:{
              return getOperatorToken(position, codeString);
            }
            default: {
              std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
                  + std::to_string(position.second) + "!";
              exit(1);
            }
          }
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 7:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        case 7:{
          codeString.push_back(codeReader.getCodeChar());
          codeReader.nextCodeChar();
          switch (operatorType(codeReader.getCodeChar())) {
            case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                               compiler::TokenType::kOperator, codeString));
            case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                               compiler::TokenType::kOperator, codeString));
            case 3:{
              return getOperatorToken(position, codeString);
            }
            default: {
              std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
                  + std::to_string(position.second) + "!";
              exit(1);
            }
          }
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 8:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        case 8:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 9:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 9:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 10:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 6:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 11:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        case 11:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 12:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 13:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }

        case 12:{
          commentSkip(position);
          return nextToken();
        }

        case 13:{
          lineCommentSkip();
          return nextToken();
        }

        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 14:{
      codeReader.nextCodeChar();
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 3:{
          return getOperatorToken(position, codeString);
        }
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

    case 15: {
      codeReader.nextCodeChar();
      if (isNumber(codeReader.getCodeChar())){
        return getIntOrFloatToken(position,codeString);
      }
      switch (operatorType(codeReader.getCodeChar())) {
        case 0: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        case 1: return TokenShareType(new StringLexerToken(position ,codeString,
                                                           compiler::TokenType::kOperator, codeString));
        default: {
          std::cout <<  "Operator Error on " + std::to_string(position.first) + " "
              + std::to_string(position.second) + "!";
          exit(1);
        }
      }
    }

  }


}


void compiler::LexerParser::lineCommentSkip() {
  while (codeReader.getCodeChar() != '\n' && codeReader.getCodeChar() != -1){
    codeReader.nextCodeChar();
  }
  codeReader.nextCodeChar();
}

void compiler::LexerParser::commentSkip(std::pair<size_t,size_t> &position) {
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
        std::cout << escapeSequence + "out of range on " + std::to_string(position.first) + " "
            + std::to_string(position.second) ;
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
      case '/':{
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
  return TokenShareType(new StringLexerToken(position ,codeString,
                                             getIdentifierType(value), value));
}

compiler::TokenType compiler::LexerParser::getIdentifierType(std::string &identifier) {
  if (dictionary.count(identifier)){
    return dictionary[identifier];
  }
  return compiler::TokenType::kIdentifier;
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