#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

#include "Token.h"
#include "Tokenizer.h"
#include "TNode.h"


class Parser {
public:
    void parseProgram(vector<string> tokenList);
private:
    std::vector<std::string> tokens;
    void expect(std::shared_ptr<Token> expectedToken);
    std::string getNextToken();
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
    StmtNode parseStmt();
    void parseAssign();
    bool isValidVariableName(string str);
    bool isNumber(string str);
};

#endif

