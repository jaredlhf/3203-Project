#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

#include "Token.h"
#include "Tokenizer.h"
#include "TNode.h"
#include "ExpressionParser.h"
#include "PKB/PkbPopulator.h"


class Parser {
public:
    void parseProgram(vector<string> tokenList, std::shared_ptr<PkbPopulator> populator);
private:
    ExpressionParser expressionParser;
    std::shared_ptr<PkbPopulator> pkbPopulator;
    std::vector<std::string> tokens;


    std::string expect(std::shared_ptr<Token> expectedToken);
    std::string getNextToken();
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
    StmtNode parseStmt();
    void parseAssign();
    std::string parseAssignExpr();
    bool isValidVariableName(string str);
    bool isNumber(const string& str);
};

#endif

