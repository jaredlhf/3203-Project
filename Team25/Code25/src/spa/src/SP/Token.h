#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

class Token {
public:
    static bool isValidName(const std::string& variable);
    static bool isNumber(const std::string& str);
};

#endif