#include "QueryTokenizer.h"

std::string QueryTokenizer::preprocess(const std::string& word) {
    std::string res = "";
    bool inQuotes = false;

    for (int i = 0; i < word.length(); i++) {
        char c = word[i];
        if (c == '\"') {
            inQuotes = !inQuotes;
        }

        // If characters in quotes, do not account for whitespaces
        if ((inQuotes && !std::isspace(c)) || c == '.') {
            res += c;
        } else if (inQuotes && std::isspace(c)) {
            continue;
        // Handle the case where * is part of the clause name or # is part of attrname
        } else if (c == '*' || c == '#') {
            res += c;
            res += ' ';
        }
        // If char is not a whitespace or alphanumeric, insert a space inbetween, else just append char
        else if (isspace(c) == 0 && iswalnum(c) == 0 && c != '_' && c != '\"') {
            res += ' ';
            res += c;
            res += ' ';
        }
        else {
            res += c;
        }
    }

    return res;
}

std::vector<std::string> QueryTokenizer::tokenize(const std::string& query) {
    std::vector<std::string> res;

    // Split words based on whitespaces and newlines
    std::regex words_regex("[^\\s\\n]+");

    std::string processedQuery = preprocess(query);

    auto words_begin = std::sregex_iterator(processedQuery.begin(), processedQuery.end(), words_regex);
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