#include <unordered_set>
#include "QueryEvaluator.h"

using namespace std;

// Adds the data from the parser into the class attributes
void QueryEvaluator::handleParserResponse(ParserResponse& response) {
	vector<vector<string>> rawDeclarations = response.getDeclarations();
	for (vector<string>& row : rawDeclarations) {
		string decType = row[0];
		for (int i = 1; i < row.size(); i++) {
			if (row[i] == ",") {
				continue;
			}
			string varName = row[i];
			declarations.insert({varName, Synonym::create(decType, varName)});
		}
	}

	string resultName = response.getSynonym();
	cerr << resultName << endl;
	resultSynonym = declarations[resultName];
}

list<string> QueryEvaluator::evaluate(ParserResponse response, PkbRetriever* pkbRetriever) {
	list<string> result;
	handleParserResponse(response);

	unordered_set<string> resSet = (*pkbRetriever).getAllVar();
	for (const string& variable : resSet) {
		resultSynonym.addMatchingResult(variable);
	}

	for (const string& answer : resultSynonym.getMatches()) {
		result.push_back(answer);
	}

	return result;
}