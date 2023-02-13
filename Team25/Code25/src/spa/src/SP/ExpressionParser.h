#pragma once
#include <string>

using namespace std;

class ExpressionParser {

    bool isName(std::string var);
    bool isNumber(std::string var);
public:
    int matchingBracket(std::string str);
    bool checkParenthesis(std::string expr);
    bool isExpr(std::string expr);
    bool isRelExpr(std::string expr);
    bool isCondExpr(std::string expr);
    bool parseCondExpr(std::string expr);
};

