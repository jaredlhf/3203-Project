#include "Token.h"

bool Token::isValidName(const std::string& var) {
    for (int i = 0; i < var.length(); i++) {
        if (i == 0 && !isalpha(var[i])) {
            return false;
        }
        if (!isalpha(var[i]) && !isdigit(var[i])) {
            return false;
        }
    }
    return true;
}

bool Token::isNumber(const std::string& str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}
