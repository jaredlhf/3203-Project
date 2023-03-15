#include "ExpressionParser.h"
#include "Token.h"
#include <algorithm>
#include <regex>
#include <stack>
#include <string>

using namespace std;

bool ExpressionParser::checkParenthesis(const std::string &expr) {
  std::stack<char> stack;

  for (int i = 0; i < expr.length(); i++) {
    if (expr.at(i) == '(') {
      stack.push('(');
    } else if (expr.at(i) == ')') {
      if (stack.empty()) {
        return false;
      } else {
        stack.pop();
      }
    }
  }
  if (stack.empty()) {
    return true;
  } else {
    return false;
  }
}

int ExpressionParser::matchingBracket(const std::string &str) {
  int count = 1;
  int pos = 1;
  for (char c : str) {
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

bool ExpressionParser::isExpr(std::string str) {
  // regex for char string
  std::regex term("(\\w+)");
  std::regex exprRegex("^(?:[\\(\\s]*(\\w+)[\\s\\)]*)(?:\\s*[+\\*\\-%\\/"
                       "]\\s*(?:[\\(\\s]*(\\w+)[\\s\\)]*))*$");
  if (regex_match(str, exprRegex)) {
    if (checkParenthesis(str)) {
      std::smatch result;
      while (std::regex_search(str, result, term)) {
        // check if char string is a valid name or number
        if (!(Token::isValidName(result[0]) || Token::isNumber(result[0]))) {
          return false;
        }
        str = result.suffix().str();
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool ExpressionParser::isRelExpr(const std::string &expr) {
  std::vector<string> single_rel_ops({">", "<"});
  std::vector<string> double_rel_ops({">=", "<=", "==", "!="});
  int index;
  if (checkParenthesis(expr)) {
    for (string i : double_rel_ops) {
      if (expr.find(i) != std::string::npos) {
        index = expr.find(i);
        std::string rhs = expr.substr(0, index);
        std::string lhs = expr.substr(index + 2);
        return (isExpr(rhs) && isExpr(lhs));
      }
    }
    for (string i : single_rel_ops) {
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
    return true;
  } else if (expr[0] == '!') {
    // erase !
    expr.erase(expr.begin());

    if (checkParenthesis(expr)) {
      int bracket = matchingBracket(expr.substr(1));
      // remove ()
      expr.erase(bracket);
      expr.erase(expr.begin());
      return isCondExpr((expr));
    }
    return false;
  }
  // for && case
  if ((expr.find("&&") != std::string::npos)) {
    if (checkParenthesis(expr.substr(0, expr.find("&&")))) {
      index = expr.find("&&");
      std::string firstSub = expr.substr(0, index);
      if (firstSub.at(0) == '(' && firstSub.at(firstSub.length() - 1) == ')') {
        // erase first (
        firstSub.erase(firstSub.begin());
        // erase last )
        firstSub.pop_back();
      }
      std::string secondSub = expr.substr(index + 2);
      if (secondSub.at(0) == '(' &&
          secondSub.at(secondSub.length() - 1) == ')') {
        // erase first (
        secondSub.erase(secondSub.begin());
        // erase last )
        secondSub.pop_back();
      }
      return isCondExpr(firstSub) && isCondExpr((secondSub));
    }
  }
  // for || case
  if ((expr.find("||") != std::string::npos)) {
    if (checkParenthesis(expr.substr(0, expr.find("||")))) {
      index = expr.find("||");
      std::string firstSub = expr.substr(0, index);
      if (firstSub.at(0) == '(' && firstSub.at(firstSub.length() - 1) == ')') {
        // erase first (
        firstSub.erase(firstSub.begin());
        // erase last )
        firstSub.pop_back();
      }
      std::string secondSub = expr.substr(index + 2);
      if (secondSub.at(0) == '(' &&
          secondSub.at(secondSub.length() - 1) == ')') {
        // erase first (
        secondSub.erase(secondSub.begin());
        // erase last )
        secondSub.pop_back();
      }
      return isCondExpr(firstSub) && isCondExpr((secondSub));
    }
  }
  return false;
}