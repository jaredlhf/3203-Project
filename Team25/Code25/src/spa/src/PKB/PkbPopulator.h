#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "VariableStore.h"

class PkbPopulator {

private:
	VariableStore* varStorage;
public:
	PkbPopulator(VariableStore* varStore);
	void addVar(std::string varName);
};