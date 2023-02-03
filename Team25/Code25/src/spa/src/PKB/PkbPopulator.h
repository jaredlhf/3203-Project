#include<stdio.h>
#include <vector>
#include <string>

using namespace std;



class PkbPopulator {
	class VarStorage;
private:
	VarStorage* varStorage;
public:
	PkbPopulator(VarStorage* varStorage) {
	};
	void addVar(std::string varName);
	std::vector<std::string>* getAllVar();
	bool checkVar(std::string varName);
};