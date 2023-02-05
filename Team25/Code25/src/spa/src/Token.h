#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

#include "Parser.h"

class Token {
public:
    virtual bool isValidToken(string tokenString) const;
};

class Procedure: public Token {
public:
    bool isValidToken(string tokenString) const override;
};

class Name: public Token {
public:
    bool isValidToken(string tokenString) const override;
};

class LeftBrace: public Token {
public:
    bool isValidToken(string tokenString) const override;
};

class RightBrace: public Token {
public:
    bool isValidToken(string tokenString) const override;
};

class Statement: public Token {
public:
    bool isValidToken(string tokenString) const override;
};

#endif