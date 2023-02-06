#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

#include "Parser.h"

bool isValidVariableName(string variable)
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

bool isNumber(string str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}

void parseAssign(vector<string> tokens) {
    std::regex terms("(\\w+)");
    std::smatch result;
    std::vector<std::string> variableVector;
    for (string token: tokens) {
        std::regex_search(token, result, terms);
            variableVector.push_back(result[0]);
    }

    for (string entity: variableVector)
        if (isValidVariableName((entity))) {
            std::cout<< entity << " variable" << endl;
        } else if (isNumber(entity)) {
            std::cout<< entity << " constant" << endl;
        }
}

void parseStatement(vector<string> tokens) {
    if (isValidVariableName(tokens.front())){
        parseAssign(tokens);
    } else if (tokens.front() == "if") {

    } else if (tokens.front() == "while") {

    } else if (tokens.front() == "print") {

    } else if (tokens.front() == "read") {

    } else {
        throw std::invalid_argument("Invalid statement");
    }
}

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




