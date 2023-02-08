#include <vector>
#include <unordered_set>
#include <string>
#include <regex>
#include <iostream>
#include "QueryTokenizer.h"

using namespace std;

vector<string> QueryTokenizer::splitSymbol(string word) {
    vector<string> res;
    unordered_set<char> prefixes{'('};
    unordered_set<char> suffixes{ ')', ',', ';'};

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

vector<string> QueryTokenizer::tokenize(string query) {
    vector<string> res;

    // Split words based on whitespaces and newlines
    regex words_regex("[^\\s\\n]+");

    auto words_begin = sregex_iterator(query.begin(), query.end(), words_regex);
    auto words_end = sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        string curr = (*i).str();
        vector<string> toAdd = splitSymbol(curr);
        res.insert(res.end(), toAdd.begin(), toAdd.end());
    }

    return res;
}