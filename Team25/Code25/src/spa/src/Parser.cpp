#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Parser.h"




std::string Parser::getNextToken() {
    std::string next = this->tokens.front();
    tokens.erase(tokens.begin());
    return next;
}

void Parser::expect(std::shared_ptr<Token> expectedToken) {
    std::string next = getNextToken();
    if (!expectedToken->isEqual(next)) {
        std::cout << "error: unexpected token, got: " << next << std::endl;

        throw 1;
    }
}

void Parser::parseProgram(std::vector<std::string> tokenList) {
    this->tokens = tokenList;

    do {
        if (tokens.empty()) {
            std::cout << "error: no procedures found" << std::endl;
            throw 1;
        } else {
            parseProcedure();
        }
    } while (!tokens.empty());
}


ProcedureNode Parser::parseProcedure() {
    std::cout << tokens.front() << std::endl;
    expect(std::make_shared<Procedure>());
    std::cout << "done procedure" << std::endl;
    expect(std::make_shared<Name>());
    std::cout << "done name" << std::endl;
    expect(std::make_shared<LeftBrace>());
    std::cout << "done left brace" << std::endl;
    StmtLstNode stmtLst = parseStmtLst();
    std::cout << "done parseStmtLst" << std::endl;
    ProcedureNode node = ProcedureNode(stmtLst);
    expect(std::make_shared<RightBrace>());
    return node;
}

StmtLstNode Parser::parseStmtLst() {
    std::vector<StmtNode> StmtLsts;
//    do {
//        //StmtNode sn = parseStmt();
//        //StmtLsts.push_back(sn);
//    } while(!RightBrace().isEqual(tokens.front()));
    StmtLstNode node = StmtLstNode(StmtLsts);
    return node;
}



