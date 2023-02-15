#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <iostream>
#include "../constants/Constants.h"

class ParserUtils {
    public:
        static bool isValidIntegerString(const std::string& s);
        static bool isValidNaming(const std::string& s);
        static bool isDesignEntityToken(const std::string& s);
        static std::string removeQuotations(const std::string& s);
        static bool isValidEntRef(const std::string& s);
        static bool isValidExpression(std::vector<std::string> s);
};