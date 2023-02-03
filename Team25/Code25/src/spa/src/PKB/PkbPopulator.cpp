#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"
/*Place holder for VarStorage declaration*/
struct PkbPopulator::VarStorage {
public:
	void VarStorage::addVar(std::string varName) {

	};
	std::vector<std::string>* VarStorage::getAllVar() {

	};
	bool VarStorage::checkVar(std::string varName) {

	};
};

/*
TODO: ADD constructor method
*/
PkbPopulator::PkbPopulator(VarStorage* varStore) {
	varStorage = varStore;
}




void PkbPopulator::addVar(std::string varName) {
	this->varStorage->addVar(varName);
};

std::vector<std::string>* PkbPopulator::getAllVar() {
	return this->varStorage->getAllVar();
}

bool PkbPopulator::checkVar(std::string varName) {
	return this->varStorage->checkVar(varName);
}


 