#ifndef STMTPARSER_H
#define STMTPARSER_H

#include <string>
#include "TNode.h"

class StmtParser {
public:
    virtual TNode parse() = 0;
};

class AssignParser: public StmtParser {
public:
    TNode parse() override;
};

class PrintParser: public StmtParser {
public:
    TNode parse() override;
};

class CallParser: public StmtParser {
public:
    TNode parse() override;
};

class WhileParser: public StmtParser {
public:
    TNode parse() override;
};

class IfParser: public StmtParser {
public:
    TNode parse() override;
};

class ReadParser: public StmtParser {
public:
    TNode parse() override;
};

class StmtParserFactory {
public:
    static std::shared_ptr<StmtParser> createStmtParser(std::string stmtType) {
        if (stmtType == "read") {
            return std::make_shared<ReadParser>();
        } else if (stmtType == "print") {
            return std::make_shared<PrintParser>();
        } else if (stmtType == "call") {
            return std::make_shared<CallParser>();
        } else if (stmtType == "while") {
            return std::make_shared<WhileParser>();
        } else if (stmtType == "if") {
            return std::make_shared<IfParser>();
        } else if (stmtType == "assign") {
            return std::make_shared<AssignParser>();
        } else {
            throw std::invalid_argument("Not a statement keyword");
        }
    }
};


#endif //STMTPARSER_H
