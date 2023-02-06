#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

#include "Token.h"
#include "Tokenizer.h"
#include "TNode.h"
#include "ExpressionParser.h"


class Parser {
public:
    void parseProgram(vector<string> tokenList);
private:
    ExpressionParser expressionParser;
    std::vector<std::string> tokens;
    std::string expect(std::shared_ptr<Token> expectedToken);
    std::string getNextToken();
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
    StmtNode parseStmt();
    void parseAssign();
    std::string parseAssignExpr();
    bool isValidVariableName(string str);
    bool isNumber(string str);
};

#endif

