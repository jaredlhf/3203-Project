#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Tokenizer {
  vector<string> tokens;

public:
  vector<string> getTokens();
  void setTokens(vector<string> tokens);
  vector<string> tokenize(const string &str);
  string expect(const string &spa, const string &str);
  string getNextToken();
  string peek();
  string peekTwice();
};