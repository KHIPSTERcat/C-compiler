#pragma once

#include "../Lexer/lexer_parser.h"
#include <iostream>
#include <memory>
#include <map>

namespace compiler{
  class AnalyzerTreeNode{
   private:
   public:
  };

class ExpressionTreeNode: public AnalyzerTreeNode{
 private:
 public:
};

class LiteralTreeNode: public ExpressionTreeNode{
 private:
  std::shared_ptr<LexerToken> token;
 public:
  LiteralTreeNode(std::shared_ptr<LexerToken> token):token(token);

  const std::shared_ptr<LexerToken> getToken;
};

class IntLiteralTreeNode: public LiteralTreeNode{
 private:
 public:
  IntLiteralTreeNode(std::shared_ptr<IntLexerToken> token);
};

class FloatLiteralTreeNode: public LiteralTreeNode{
 private:
 public:
  FloatLiteralTreeNode(std::shared_ptr<IntLexerToken> token);
};

class StringLiteralTreeNode: public LiteralTreeNode{
 private:
 public:
  StringLiteralTreeNode(std::shared_ptr<IntLexerToken> token);
};

class CharLiteralTreeNode: public LiteralTreeNode{
 private:
 public:
  CharLiteralTreeNode(std::shared_ptr<IntLexerToken> token);
};





}