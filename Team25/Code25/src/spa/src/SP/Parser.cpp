#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>


#include "Parser.h"
ExpressionParser expressionParser;
std::regex value("(\\w+)");

Parser::Parser(std::shared_ptr<Tokenizer> t, std::shared_ptr<PkbPopulator> populator) {
    this->tokenizer = t;
    this->pkbPopulator = populator;
};

bool Parser::isNumber(const std::string& str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}

bool Parser::isValidVariableName(std::string variable)
{
    if (!((variable[0] >= 'a' && variable[0] <= 'z')
          || (variable[0] >= 'A' && variable[0] <= 'Z')
          || variable[0] == '_'))
        return false;
    for (int i = 1; i < variable.length(); i++) {
        if (!((variable[i] >= 'a' && variable[i] <= 'z')
              || (variable[i] >= 'A' && variable[i] <= 'Z')
              || (variable[i] >= '0' && variable[i] <= '9')
              || variable[i] == '_'))
            return false;
    }
    return true;
}

//std::string Parser::getNextToken() {
//    std::string next = this->tokens.front();
//    tokens.erase(tokens.begin());
//    return next;
//}

std::string Parser::expect(std::shared_ptr<Token> expectedToken) {
    std::string next = tokenizer->getNextToken();
    if (!expectedToken->isEqual(next)) {
        std::cout << "error: unexpected token, got: " << next << std::endl;

        throw 1;
    }
    return next;
}

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
    expect(std::make_shared<Procedure>());
    expect(std::make_shared<Name>());
    expect(std::make_shared<LeftBrace>());
    StmtLstNode stmtLst = parseStmtLst();
    ProcedureNode node = ProcedureNode(stmtLst);
    expect(std::make_shared<RightBrace>());
    return node;
}

StmtLstNode Parser::parseStmtLst() {
    std::vector<StmtNode> StmtLsts;
    do {
        StmtNode sn = parseStmt();
        StmtLsts.push_back(sn);
    } while(!RightBrace().isEqual(tokenizer->peek()));
    StmtLstNode node = StmtLstNode(StmtLsts);
    return node;
}

StmtNode Parser::parseStmt() {
    AssignNode a("a","a");
    if (isValidVariableName(tokenizer->peek())) {
        parseAssign();
    }
    return StmtNode(a);
}


void Parser::parseAssign() {
    std::string lhs = expect(std::make_shared<Name>());
    //pkb populate lhs
    pkbPopulator->addVar(lhs);
    expect(std::make_shared<Equal>());
    std::string rhs = "";
    vector<string> rhsTokens;
    while(tokenizer->peek() != ";") {
        std::string next = tokenizer->getNextToken();
        rhs = rhs + next;
        rhsTokens.push_back(next);

    }
    if(Parser::expressionParser.isExpr((rhs))) {
        std::smatch result;
        std::vector<std::string> variableVector;
        for (string token: rhsTokens) {
            std::regex_search(token, result, value);
            variableVector.push_back(result[0]);
        }
        for (string entity: variableVector)
            if (isValidVariableName((entity))) {
                pkbPopulator->addVar(entity);
            } else if (isNumber(entity)) {
                pkbPopulator->addConst(std::stoi(entity));
            }
    } else {
        throw std::invalid_argument("Invalid expression ");
    }

    expect(std::make_shared<Semicolon>());
}



