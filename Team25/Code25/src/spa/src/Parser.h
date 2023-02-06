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
    void parseStatement(vector<string> str);
    void parseAssign(vector<string> str);
    bool isValidVariableName(string str);
    bool isNumber(string str);
private:
    std::vector<std::string> tokens;
    void expect(std::shared_ptr<Token> expectedToken);
    std::string getNextToken();
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
    StmtNode parseStmt();
};

#endif

