#include <stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

#include "VariableStore.h"

class PkbRetriever{
private:
	VariableStore* varStorage;
public:
	PkbRetriever(VariableStore* varStore);
	std::unordered_set<std::string> getAllVar();
	bool has(std::string varName);
};