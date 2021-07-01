#include "lexer_parser.h"

compiler::LexerParser::LexerParser(std::string fileName):codeReader(fileName){
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
    case '.': return 2;
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
      return getOperatorToken(position, codeString);
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