#include <string>
#include <regex>
#include <stack>
#include <sstream>
#include <iostream>
#include "ExpressionParser.h"

using namespace std;

std::regex terms("(\\w+)");
std::regex validExpression("^(?:[\\(\\s]*(\\w+)[\\s\\)]*)(?:\\s*[+\\*\\-%\\/]\\s*(?:[\\(\\s]*(\\w+)[\\s\\)]*))*$");

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

int ExpressionParser::matchingBracket(std::string str) {
    int count = 1;
    int pos = 1;
    for (char &c: str) {
        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
            if (count == 0) {
                return pos;
            }
        }
        pos++;
    }
}

//bool ExpressionParser::removeMatchingBracket(std::string expr,int start, int end) {
//
//}

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
    std::vector<string> single_rel_ops({">", "<" });
    std::vector<string> double_rel_ops({ ">=", "<=", "==", "!="});
    int index;
    if (checkParenthesis(expr)) {
//        expr.erase(std::remove(expr.begin(), expr.end(), '('), expr.end());
//        expr.erase(std::remove(expr.begin(), expr.end(), ')'), expr.end());
        for (string i: double_rel_ops) {
            if (expr.find(i) != std::string::npos) {
                index = expr.find(i);
                std::string rhs = expr.substr(0, index);
                std::string lhs = expr.substr(index + 2);
                return (isExpr(rhs) && isExpr(lhs));
            }
        }
        for (string i: single_rel_ops) {
            if (expr.find(i) != std::string::npos) {
                index = expr.find(i);
                std::string rhs = expr.substr(0, index);
                std::string lhs = expr.substr(index + 1);
                return (isExpr(rhs) && isExpr(lhs));
            }
        }
    }
    return false;
};

bool ExpressionParser::isCondExpr(std::string expr) {
    int index;
    // remove ()
    // for ! case
    if (isRelExpr(expr)) {
//        std::cout<<expr<<endl;
//        std::cout<<"test"<<endl;
        return true;
    } else if (expr[0] == '!') {
        //erase !
        expr.erase(expr.begin());
        int bracket = matchingBracket(expr.substr(1));
        //remove ()
        expr.erase(bracket);
        expr.erase(expr.begin());
//        std::cout << bracket << endl;
//        std::cout << expr << " test1 " << endl;
        return isCondExpr((expr));
        // for && case
    }
    if ((expr.find("&&") != std::string::npos)) {
        if (checkParenthesis(expr.substr(0, expr.find("&&")))) {
            index = expr.find("&&");
            std::string firstSub = expr.substr(0, index);
            if (firstSub.at(0) == '(' && firstSub.at(firstSub.length() - 1) == ')') {
                //erase first (
                firstSub.erase(firstSub.begin());
                //erase last )
                firstSub.pop_back();
            }
            std::string secondSub = expr.substr(index + 2);
            if (secondSub.at(0) == '(' && secondSub.at(secondSub.length() - 1) == ')') {
                //erase first (
                secondSub.erase(secondSub.begin());
                //erase last )
                secondSub.pop_back();
            }
//            std::cout << expr << " test2 " << endl;
//            std::cout << firstSub << endl;
//            std::cout << secondSub << endl;
            return isCondExpr(firstSub) && isCondExpr((secondSub));
        }
    }
    // for || case
    if ((expr.find("||") != std::string::npos)) {
        if (checkParenthesis(expr.substr(0, expr.find("||")))) {
            index = expr.find("||");
            std::string firstSub = expr.substr(0, index);
            if (firstSub.at(0) == '(' && firstSub.at(firstSub.length() - 1) == ')') {
                //erase first (
                firstSub.erase(firstSub.begin());
                //erase last )
                firstSub.pop_back();
            }
            std::string secondSub = expr.substr(index + 2);
            if (secondSub.at(0) == '(' && secondSub.at(secondSub.length() - 1) == ')') {
                //erase first (
                secondSub.erase(secondSub.begin());
                //erase last )
                secondSub.pop_back();
            }
//            std::cout << expr << " test3 " << endl;
//            std::cout << firstSub << endl;
//            std::cout << secondSub << endl;
            return isCondExpr(firstSub) && isCondExpr((secondSub));
        }
    }
}