#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "placeHolder.h"

class PkbRetriever{
private:
	VarStorage* varStorage;
public:
	PkbRetriever(VarStorage* varStore);
	std::vector<std::string>* getAllVar();
	bool checkVar(std::string varName);
};