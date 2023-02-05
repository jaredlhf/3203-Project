#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

using namespace std;

#include "Tokenizer.h"
#include "TNode.h"
#include "Token.h"

class Parser {
public:
    static bool isValidName(string variable);
    void parseProgram(vector<string> tokenList);
private:
    vector<string> tokens;
    void expect(const Token &expectedToken);
    string getNextToken();
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
    StmtNode parseStmt()
};

#endif