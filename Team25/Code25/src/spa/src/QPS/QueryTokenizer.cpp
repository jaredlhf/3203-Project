#include "QueryTokenizer.h"

std::vector<std::string> QueryTokenizer::splitSymbol(std::string word) {
    std::vector<std::string> res;
    std::unordered_set<char> prefixes{'('};
    std::unordered_set<char> suffixes{ ')', ',', ';'};

    // Add prefixes if any and remove prefix from word
    if (prefixes.find(word[0]) != prefixes.end()) {
        res.push_back(word.substr(0, 1));
        word = word.substr(1, word.size() - 1);
    }

    if (suffixes.find(word[word.size() - 1]) != suffixes.end()) {
        res.push_back(word.substr(0, word.size() - 1));
        res.push_back(word.substr(word.size() - 1, 1));
    }
    else {
        res.push_back(word);
    }

    return res;
}

std::vector<std::string> QueryTokenizer::tokenize(const std::string& query) {
    std::vector<std::string> res;

    // Split words based on whitespaces and newlines
    std::regex words_regex("[^\\s\\n]+");

    auto words_begin = std::sregex_iterator(query.begin(), query.end(), words_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::string curr = (*i).str();
        std::vector<std::string> toAdd = splitSymbol(curr);
        res.insert(res.end(), toAdd.begin(), toAdd.end());
    }

    return res;
}