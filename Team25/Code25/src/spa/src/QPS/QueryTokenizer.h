#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <regex>
#include "constants/Constants.h"


class QueryTokenizer {
private:
	std::string preprocess(const std::string& word);

public:
	std::vector<std::string> tokenize(const std::string& query);
};