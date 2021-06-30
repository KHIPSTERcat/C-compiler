#include "lexer_parser.h"

compiler::LexerParser::LexerParser(std::string fileName):codeReader(fileName){
  std::pair<size_t, size_t> pos(1,3);
  nowToken = TokenShareType(new CharLexerToken(pos,"0x123", compiler::TokenType::kInt, 'f'));
}

compiler::TokenShareType compiler::LexerParser::getToken() {
  return nowToken;
}

compiler::TokenShareType compiler::LexerParser::nextToken() {
  if (codeReader.getCodeChar() < 33){
    codeReader.nextSignificantChar();
  }

  if (codeReader.getCodeChar() == -1){
    nowToken = getEofToken();
    return nowToken;
  } else if (operatorType(codeReader.getCodeChar())){
    nowToken = getOperatorToken();
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

compiler::TokenShareType compiler::LexerParser::getOperatorToken(std::pair<size_t, size_t> position, std::string codeString) {
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

void compiler::LexerParser::commentSkip(std::pair<size_t,size_t> position) {
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