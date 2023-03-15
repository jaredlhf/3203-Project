#ifndef STMTPARSER_H
#define STMTPARSER_H

#include "CFGNode.h"
#include "ExpressionParser.h"
#include "ParserDTO.h"
#include "SPParserUtils.h"
#include "TNode.h"
#include "Tokenizer.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class StmtParser {
public:
  virtual std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                           std::shared_ptr<Tokenizer> tokenizer,
                                           const std::string &proc) = 0;
  static std::shared_ptr<StmtParser> createStmtParser(std::string firstToken,
                                                      std::string secondToken);
  static std::shared_ptr<ParserDTO>
  parseStmt(std::string firstToken, std::string secondToken,
            std::shared_ptr<SPParserUtils> utils,
            std::shared_ptr<Tokenizer> tokenizer, const std::string &proc);
  static std::shared_ptr<ParserDTO>
  parseStmtLst(std::shared_ptr<SPParserUtils> utils,
               std::shared_ptr<Tokenizer> tokenizer, const std::string &proc);
};

class AssignParser : public StmtParser {
public:
  std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                   std::shared_ptr<Tokenizer> tokenizer,
                                   const std::string &proc) override;
};

class PrintParser : public StmtParser {
public:
  std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                   std::shared_ptr<Tokenizer> tokenizer,
                                   const std::string &proc) override;
};

class CallParser : public StmtParser {
public:
  std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                   std::shared_ptr<Tokenizer> tokenizer,
                                   const std::string &proc) override;
};

class WhileParser : public StmtParser {
public:
  std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                   std::shared_ptr<Tokenizer> tokenizer,
                                   const std::string &proc) override;
};

class IfParser : public StmtParser {
public:
  std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                   std::shared_ptr<Tokenizer> tokenizer,
                                   const std::string &proc) override;
};

class ReadParser : public StmtParser {
public:
  std::shared_ptr<ParserDTO> parse(std::shared_ptr<SPParserUtils> utils,
                                   std::shared_ptr<Tokenizer> tokenizer,
                                   const std::string &proc) override;
};

#endif // STMTPARSER_H
