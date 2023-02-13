#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>


#include "Parser.h"

//ExpressionParser expressionParser;
//std::regex value("(\\w+)");

Parser::Parser(std::shared_ptr<Tokenizer> t, std::shared_ptr<PkbPopulator> populator) {
    this->tokenizer = t;
    this->pkbPopulator = populator;
    this->utils = std::make_shared<ParserUtils>(t);
};


void Parser::parseProgram() {

    do {
        if (tokenizer->getTokens().empty()) {
            throw std::invalid_argument("error: no procedures found");
        } else {
            parseProcedure();
        }
    } while (!tokenizer->getTokens().empty());
}


ProcedureNode Parser::parseProcedure() {
    utils->expect(std::make_shared<Procedure>());
    utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<LeftBrace>());
    StmtLstNode stmtLst = StmtParser::parseStmtLst(this->utils, this->tokenizer);
    ProcedureNode node = ProcedureNode(stmtLst);
    utils->expect(std::make_shared<RightBrace>());
    return node;
}

//StmtLstNode Parser::parseStmtLst() {
//    std::vector<StmtNode> StmtLsts;
//    do {
//        StmtNode sn = parseStmt();
//        StmtLsts.push_back(sn);
//    } while(!RightBrace().isEqual(tokenizer->peek()));
//    StmtLstNode node = StmtLstNode(StmtLsts);
//    return node;
//}

//StmtNode Parser::parseStmt() {
//    AssignNode a("a","a");
////    if (Token::isValidName(tokenizer->peek())) {
////        //parseAssign();
////    }
//    StmtParser::parseStmt(tokenizer->peek(), this->utils, this->tokenizer);
////    std::shared_ptr<StmtParser> sp = StmtParser::createStmtParser(tokenizer->peek());
////    sp->parse(this->utils, this->tokenizer);
//
//    return StmtNode(a);
//}



//void Parser::parseAssign() {
//    std::string lhs = expect(std::make_shared<Name>());
//    //pkb populate lhs
//    pkbPopulator->addVar(lhs);
//    expect(std::make_shared<Equal>());
//    std::string rhs = "";
//    vector<string> rhsTokens;
//    while(tokenizer->peek() != ";") {
//        std::string next = tokenizer->getNextToken();
//        rhs = rhs + next;
//        rhsTokens.push_back(next);
//
//    }
//    if(Parser::expressionParser.verifyExpr((rhs))) {
//        std::smatch result;
//        std::vector<std::string> variableVector;
//        for (string token: rhsTokens) {
//            std::regex_search(token, result, value);
//            variableVector.push_back(result[0]);
//        }
//        for (string entity: variableVector)
//            if (Token::isValidName((entity))) {
//                pkbPopulator->addVar(entity);
//            } else if (Token::isNumber(entity)) {
//                pkbPopulator->addConst(std::stoi(entity));
//            }
//    } else {
//        throw std::invalid_argument("Invalid expression ");
//    }
//
//    expect(std::make_shared<Semicolon>());
//}




