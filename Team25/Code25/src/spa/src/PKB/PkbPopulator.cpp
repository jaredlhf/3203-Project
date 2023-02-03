#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"

VarStorage* varStorage;

/*
TODO: ADD constructor method
*/
PkbPopulator(VarStorage* varStorage)




void PkbPopulator::addVar(std::string varName) {
	this->varStorage->addVar(varName);
};

std::vector<std::string>* PkbPopulator::getAllVar() {
	return this->varStorage->getAllVar();
}

bool PkbPopulator::checkVar(std::string varName) {
	return this->varStorage->checkVar(varName);
}


 