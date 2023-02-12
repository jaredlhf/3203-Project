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
    Parser(std::shared_ptr<Tokenizer> t, std::shared_ptr<PkbPopulator> populator);
    void parseProgram();
private:
    friend class AssignParser;
    ExpressionParser expressionParser;
    std::shared_ptr<PkbPopulator> pkbPopulator;
    std::shared_ptr<Tokenizer> tokenizer;


    std::string expect(std::shared_ptr<Token> expectedToken);
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
    StmtNode parseStmt();
    void parseAssign();
    std::string parseAssignExpr();

};

#endif

