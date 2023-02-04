#pragma once

#include <string>

using namespace std;

#include "Parser.h"

class Token {
public:
    virtual bool isValidToken(string tokenString) const;
};

class Procedure: public Token {
    bool isValidToken(string tokenString) const override;
};

class Name: public Token {
    bool isValidToken(string tokenString) const override;
};

class LeftBrace: public Token {
    bool isValidToken(string tokenString) const override;
};

class RightBrace: public Token {
    bool isValidToken(string tokenString) const override;
};

