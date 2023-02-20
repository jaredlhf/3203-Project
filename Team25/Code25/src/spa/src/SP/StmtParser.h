#ifndef STMTPARSER_H
#define STMTPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "TNode.h"
#include "SPParserUtils.h"
#include "Tokenizer.h"
#include "ExpressionParser.h"

class StmtParser {
public:
    virtual std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) = 0;
    static std::shared_ptr<StmtParser> createStmtParser(std::string stmtType);
    static std::shared_ptr<StmtNode> parseStmt(std::string stmtType, std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer);
    static StmtLstNode parseStmtLst(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer);
};

class AssignParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) override;
};

class PrintParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) override;
};

class CallParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) override;
};

class WhileParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) override;
};

class IfParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) override;
};

class ReadParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) override;
};



#endif //STMTPARSER_H
