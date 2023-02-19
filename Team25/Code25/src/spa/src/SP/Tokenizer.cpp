#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Tokenizer.h"

void Tokenizer::setTokens( vector<string> tok ) {
    tokens = tok;
};

vector<string> Tokenizer::getTokens() {
    return this->tokens;
}

string Tokenizer::peek() {
    return this->tokens.front();
}

string Tokenizer::getNextToken() {
    string next = this->tokens.front();
    tokens.erase(tokens.begin());
    return next;
}

vector<string> Tokenizer::tokenize(const string &str) {

    string next;
    vector<string> result;
    const char delimiters_Args[] = {'\t', '\n', ' '};
    std::vector<char> delimiters(delimiters_Args, std::end(delimiters_Args));
    const char identifiers_args[] = {'{', '}','(', ')', ';',  '+', '-','*', '/', '%', };
    std::vector<char> identifiers(identifiers_args, std::end(identifiers_args));
    const char double_identifiers_args[] = {'=',  '>', '<', '!', '&', '|'};
    std::vector<char> double_identifiers(double_identifiers_args, std::end(double_identifiers_args));
    const char second_operator_args[] = { '&', '|', '='};
    std::vector<char> second_operator(second_operator_args, std::end(second_operator_args));
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        char curr = *it;
        if (std::count(delimiters.begin(), delimiters.end(), curr))  {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else if (std::count(identifiers.begin(), identifiers.end(), curr)) {
            std::string id = std::string(1, curr);
            if (!next.empty()) {
                result.push_back(next);
                result.push_back(id);
                next.clear();
            } else {
                result.push_back(id);
            }
        } else if (std::count(double_identifiers.begin(), double_identifiers.end(), curr)) {
            std::string id = std::string(1, curr);
            if (!next.empty() && (std::count(second_operator.begin(), second_operator.end(), *(it + 1)))) {
                result.push_back(next);
                next.clear();
                result.push_back((id + *(it + 1)));
                it++;
            } else if (!(next.empty()) && !(std::count(second_operator.begin(), second_operator.end(), *(it + 1)))) {
                result.push_back(next);
                result.push_back(id);
                next.clear();
            } else if (!std::count(second_operator.begin(), second_operator.end(), *(it + 1))) {
                result.push_back(id);
            } else {
                result.push_back(id + *(it + 1));
                it++;
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);

    setTokens(result);
    return result;
}
