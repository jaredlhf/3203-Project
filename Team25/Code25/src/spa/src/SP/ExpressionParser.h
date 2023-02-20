#pragma once
#include <string>

using namespace std;

class ExpressionParser {
    static bool isName(std::string var);
    static bool isNumber(std::string var);
public:
    static int matchingBracket(std::string str);
    static bool checkParenthesis(std::string expr);
    static bool isExpr(std::string expr);
    static bool isRelExpr(std::string expr);
    static bool isCondExpr(std::string expr);
};

