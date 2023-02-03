#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

class VarStorage;

class PkbPopulator {
private:
	VarStorage* varStorage;

public:
	void addVar(std::string varName);
	std::vector<std::string>* getAllVar();
	bool checkVar();
};