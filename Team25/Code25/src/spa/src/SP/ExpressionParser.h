#pragma once
#include <string>

using namespace std;

class ExpressionParser {
    bool checkParenthesis(std::string expr);
    bool isName(std::string var);
    bool isNumber(std::string var);
public:
    bool verifyExpr(std::string expr);
};

