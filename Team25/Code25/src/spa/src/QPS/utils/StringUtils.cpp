#include "StringUtils.h"
#include <algorithm>

bool StringUtils::isValidInt(const std::string &s) {
  if (s.size() == 0 || s == "") {
    return false;
  }

  if (s[0] == '-' && s.size() == 1) {
    return false;
  }

  if (!(s[0] == '-' || std::isdigit(s[0]))) {
    return false;
  }

  for (int i = 1; i < s.size(); i++) {
    if (!std::isdigit(s[i])) {
      return false;
    }
  }

  return true;
}

/*
        Introduce space between special characters in the string
        E.g. "x+(z*y1)+1" -> "x +  ( z * y1 )  + 1" */
std::string StringUtils::spaceifyString(const std::string &s) {
  std::string res = "";
  for (const char c : s) {
    if (!std::isalnum(c)) {
      res += ' ';
      res += c;
      res += ' ';
    } else {
      res += c;
    }
  }

  return res;
}

std::vector<std::string> StringUtils::splitString(const std::string &s) {
  std::vector<std::string> res;

  // Split words based on whitespaces and newlines
  std::regex words_regex("[^\\s\\n\\t]+");

  auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
  auto words_end = std::sregex_iterator();

  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::string curr = (*i).str();
    if (curr.length() < 1) {
      continue;
    }

    res.push_back(curr);
  }

  return res;
}

std::string StringUtils::addBrackets(const std::string &s) {
  std::string res;
  res += '(' + s + ')';

  return res;
}

/*
        Returns true if the particular IDENT token is found in an operation
   string
*/
bool StringUtils::tokenInOp(const std::string &opStr,
                            const std::string &token) {
  std::vector<std::string> opTokens =
      StringUtils::splitString(StringUtils::spaceifyString(opStr));
  return std::find(opTokens.begin(), opTokens.end(), token) != opTokens.end();
}

/*
        Returns true if the particular string is made up of decimal digits or
   letters
*/

bool StringUtils::isDigitLetters(std::string &s) {
  for (const char c : s) {
    if (!std::isalnum(c)) {
      return false;
    }
  }
  return true;
}

/*
        Creates postfix notation expression string when given an prefix notation
   expression string
*/
std::string StringUtils::createPostFixNotation(const std::string &infix) {
  std::string result;
  std::stack<std::string> opStack;
  // string is split and placed in order into a vector
  std::vector<std::string> spacifiedInfix =
      StringUtils::splitString(StringUtils::spaceifyString(infix));

  for (std::string str : spacifiedInfix) {
    // if its an expression
    if (StringUtils::isDigitLetters(str)) {
      // add brackets around it and append to result
      result.append(StringUtils::addBrackets(str));
    }
    // if its a spacing
    else if (str == " " || str == "\t") {
      // ignore spacing
    } else if (str == "(") {
      opStack.push(str);
    } else if (str == ")") {
      while (!opStack.empty() && opStack.top() != "(") {
        result.append(opStack.top());
        opStack.pop();
      }
      opStack.pop();
    }
    // if its an operator or brackets
    else {
      // add all operators on opStack to string
      while (!opStack.empty() && opStack.top() != "(" &&
             StringUtils::opPrecedence(str) <=
                 StringUtils::opPrecedence(opStack.top())) {
        result.append(opStack.top());
        opStack.pop();
      }
      opStack.push(str);
    }
  }

  while (!opStack.empty()) {
    result.append(opStack.top());
    opStack.pop();
  }
  return result;
}

/*
        Returns an integer to represent the precedence of operations, higher
   integer has higher precedence
*/

int StringUtils::opPrecedence(std::string &op) {
  if (op == "+" || op == "-") {
    return 1;
  } else if (op == "*" || op == "/") {
    return 2;
  } else {
    return 0;
  }
}

/*
        Returns true if postFix(arg1) exists in fullPostFix(arg2)
*/

bool StringUtils::postFixInFullpostFix(const std::string &postFix,
                                       const std::string &fullPostFix) {
  if (fullPostFix.find(postFix) != std::string::npos) {
    return true;
  }
  return false;
}
