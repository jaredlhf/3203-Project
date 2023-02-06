#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

#include "Parser.h"
ExpressionParser expressionParser;
std::regex value("(\\w+)");

bool Parser::isNumber(string str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}

bool Parser::isValidVariableName(string variable)
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

std::string Parser::getNextToken() {
    std::string next = this->tokens.front();
    tokens.erase(tokens.begin());
    return next;
}

std::string Parser::expect(std::shared_ptr<Token> expectedToken) {
    std::string next = getNextToken();
    if (!expectedToken->isEqual(next)) {
        std::cout << "error: unexpected token, got: " << next << std::endl;

        throw 1;
    }
    return next;
}

void Parser::parseProgram(std::vector<std::string> tokenList, PkbPopulator* populator) {
    this->tokens = tokenList;
    this->pkbPopulator = populator;

    do {
        if (tokens.empty()) {
            throw std::invalid_argument("error: no procedures found");
        } else {
            parseProcedure();
        }
    } while (!tokens.empty());
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
    } while(!RightBrace().isEqual(tokens.front()));
    StmtLstNode node = StmtLstNode(StmtLsts);
    return node;
}

StmtNode Parser::parseStmt() {
    AssignNode a("a","a");
    if (isValidVariableName(tokens.front())) {
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
    while(tokens.front() != ";") {
        rhs = rhs + tokens.front();
        rhsTokens.push_back((tokens.front()));
        tokens.erase(tokens.begin());
    }
    if(Parser::expressionParser.verifyExpr((rhs))) {
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



