#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "placeHolder.h"

class PkbPopulator {

private:
	VarStorage* varStorage;
public:
	PkbPopulator(VarStorage* varStore);
	void addVar(std::string varName);
};