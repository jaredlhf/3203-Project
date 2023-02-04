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
private:
    vector<string> tokens;
    void expect(const Token &expectedToken);
    string getNextToken();
    bool isValidProcedure();
    ProcedureNode parseProcedure();
    StmtLstNode parseStmtLst();
};

#endif