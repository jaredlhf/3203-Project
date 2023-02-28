#pragma once
#include <string>

using namespace std;

class ExpressionParser {
public:
    static int matchingBracket(const std::string& str);
    static bool checkParenthesis(const std::string& expr);
    static bool isExpr(const std::string& expr);
    static bool isRelExpr(const std::string& expr);
    static bool isCondExpr(const std::string& expr);
};

