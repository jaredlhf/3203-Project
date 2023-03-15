#pragma once

#include "constants/Constants.h"
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

class QueryTokenizer {
private:
  std::string preprocess(const std::string &word);

public:
  std::vector<std::string> tokenize(const std::string &query);
};