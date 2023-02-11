#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <regex>
#include <iostream>


class QueryTokenizer {
private:
	std::vector<std::string> splitSymbol(std::string word);

public:
	std::vector<std::string> tokenize(const std::string& query);
};