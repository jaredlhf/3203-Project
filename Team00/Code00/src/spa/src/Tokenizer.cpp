#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

vector<string> tokenize(const string& str) {
    string next;
    vector<string> result;

    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        if (*it == ' ') {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

string expect(const string& spa, const string& str) {
    vector<string> tokens = tokenize(spa);
        if (tokens.front() == str) {
            return tokens.front();
        } else {
            throw std::invalid_argument("Expected " + str + " instead of " + tokens.front());
        }
}