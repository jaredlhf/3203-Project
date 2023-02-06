#pragma once
#include <vector>
#include <string>

using namespace std;

class QueryTokenizer {
private:
	vector<string> splitSymbol(string word);

public:
	vector<string> tokenize(string query);
};