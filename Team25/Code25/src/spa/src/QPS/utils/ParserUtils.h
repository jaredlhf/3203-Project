#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <iostream>
#include "../constants/Constants.h"
#include "../constants/Synonym.h"
#include "../constants/Wildcard.h"
#include "../constants/Value.h"

class ParserUtils {
    public:
        static bool isValidIntegerString(const std::string& s);
        static bool isValidNaming(const std::string& s);
        static bool isDesignEntityToken(const std::string& s);
        static bool isRelRefToken(const std::string& s);
        static std::string removeQuotations(const std::string& s);
        static std::shared_ptr<Entity> getValidEntRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static std::shared_ptr<Entity> getValidStmtRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations);
        static bool isValidExpression(std::vector<std::string> s);
};