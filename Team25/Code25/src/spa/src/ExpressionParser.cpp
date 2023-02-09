#include <string>
#include <regex>
#include <stack>
#include <sstream>
#include <iostream>
#include "ExpressionParser.h"

using namespace std;

std::regex terms("(\\w+)");
std::regex validExpression("^(?:[\\(\\s]*(\\w+)[\\s\\)]*)(?:\\s*[+\\*\\-%\\/]\\s*(?:[\\(\\s]*(\\w+)[\\s\\)]*))*$");
std::regex validRelExpression("^(?:[\\(\\s]*(\\w+)[\\s\\)]*)(?:\\s*([\\<>]|[<>!=]=)\\s*(?:[\\(\\s]*(\\w+)[\\s\\)]*))*$");

bool ExpressionParser::isNumber(std::string str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}


bool ExpressionParser::isName(std::string variable)
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

bool ExpressionParser::checkParenthesis(std::string expr) {
    std::stack<char> stack;

    for (size_t i = 0; i < expr.length(); i++) {
        if (expr.at(i) == '(') {
            stack.push('(');
        }
        else if (expr.at(i) == ')') {
            if (stack.empty()) {
                return false;
            }
            else {
                stack.pop();
            }
        }
    }

    if (stack.empty()) {
        return true;
    }
    else {
        return false;
    }
}

bool ExpressionParser::isExpr(std::string expr) {
    if (regex_match(expr, validExpression)) {
        if (checkParenthesis(expr)) {
            std::smatch result;

            while (std::regex_search(expr, result, terms)) {
                bool isValidName = isName(result[0]);
                bool isValidInteger = isNumber(result[0]);
                if (!isValidName && !isValidInteger) {
                    return false;
                }
                expr = result.suffix().str();
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool ExpressionParser::isRelExpr(std::string expr) {
    if (regex_match(expr, validRelExpression)) {
        if (checkParenthesis(expr)) {
            std::smatch result;

            while (std::regex_search(expr, result, terms)) {
                bool isValidName = isName(result[0]);
                bool isValidInteger = isNumber(result[0]);
                bool isValidExpr = isExpr(result[0]);
                if (!isValidName && !isValidInteger && !isValidExpr) {
                    return false;
                }
                expr = result.suffix().str();
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
};

bool ExpressionParser::isCondExpr(std::string expr) {
    char firstChar = expr.at(0);
    // for ! case
    if (firstChar == '!') {
        // erase ! char
        expr.erase(expr.begin());
        if (expr.at(0) == '(' && expr.at(expr.length() - 1) == ')') {
            //erase first (
            expr.erase(expr.begin());
            //erase last )
            expr.pop_back();
            return isRelExpr((expr));
        } else {
            throw std::invalid_argument("Invalid parenthesis in conditional expression");
        }
    // for && case
    } else if (expr.find("&&") != std::string::npos) {
        if (expr.at(0) == '(' && expr.at(expr.length() - 1) == ')') {
            std::size_t andPos = expr.find("&&");
            //erase first (
            expr.erase(expr.begin());
            //erase last )
            expr.pop_back();
            std::string firstSub = expr.substr(0, andPos - 1);
            std::string secondSub = expr.substr(andPos + 1);
            return isRelExpr(firstSub) && isRelExpr((secondSub));
        } else {
            throw std::invalid_argument("Invalid parenthesis in conditional expression");
        }
    // for || case
    } else if (expr.find("||") != std::string::npos){
        if (expr.at(0) == '(' && expr.at(expr.length() - 1) == ')') {
            std::size_t orPos = expr.find("||");
            //erase first (
            expr.erase(expr.begin());
            //erase last )
            expr.pop_back();
            std::string firstSub = expr.substr(0, orPos - 1);
            std::string secondSub = expr.substr(orPos + 1);
            return isRelExpr(firstSub) && isRelExpr((secondSub));
        } else {
            throw std::invalid_argument("Invalid parenthesis in conditional expression");
        }
    } else {
        return isRelExpr(expr);
    }
}