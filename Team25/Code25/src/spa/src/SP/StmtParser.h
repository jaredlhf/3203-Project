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
    virtual std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) = 0;
    static std::shared_ptr<StmtParser> createStmtParser(std::string stmtType);
    static std::shared_ptr<StmtNode> parseStmt(std::string stmtType, std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc);
    static StmtLstNode parseStmtLst(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer,const std::string& proc);
};

class AssignParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) override;
};

class PrintParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) override;
};

class CallParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) override;
};

class WhileParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) override;
};

class IfParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) override;
};

class ReadParser: public StmtParser {
public:
    std::shared_ptr<StmtNode> parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) override;
};

#endif //STMTPARSER_H
