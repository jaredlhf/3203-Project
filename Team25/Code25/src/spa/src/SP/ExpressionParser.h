#pragma once
#include <string>

using namespace std;

class ExpressionParser {
    static bool checkParenthesis(std::string expr);
    static bool isName(std::string var);
    static bool isNumber(std::string var);
public:
    static bool verifyExpr(std::string expr);
};

