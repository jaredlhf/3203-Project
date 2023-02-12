#ifndef STMTPARSER_H
#define STMTPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "TNode.h"
#include "Parser.h"

class StmtParser {
public:
    virtual TNode parse(std::shared_ptr<Parser> parser) = 0;
    static std::shared_ptr<StmtParser> createStmtParser(std::string stmtType);
    static TNode parseStmt(std::string stmtType, std::shared_ptr<Parser> parser);
};

class AssignParser: public StmtParser {
public:
    TNode parse(std::shared_ptr<Parser> parser) override;
};

class PrintParser: public StmtParser {
public:
    TNode parse(std::shared_ptr<Parser> parser) override;
};

class CallParser: public StmtParser {
public:
    TNode parse(std::shared_ptr<Parser> parser) override;
};

class WhileParser: public StmtParser {
public:
    TNode parse(std::shared_ptr<Parser> parser) override;
};

class IfParser: public StmtParser {
public:
    TNode parse(std::shared_ptr<Parser> parser) override;
};

class ReadParser: public StmtParser {
public:
    TNode parse(std::shared_ptr<Parser> parser) override;
};



#endif //STMTPARSER_H
