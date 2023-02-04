#include <stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

#include "placeHolder.h"

class PkbRetriever{
private:
	VarStorage* varStorage;
public:
	PkbRetriever(VarStorage* varStore);
	std::unordered_set<std::string>* getAllVar();
	bool checkVar(std::string varName);
};