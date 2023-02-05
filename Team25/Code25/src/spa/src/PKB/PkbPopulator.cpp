#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"
#include "VariableStore.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(VariableStore* varStore) {
	this->varStorage = varStore;
};


void PkbPopulator::addVar(std::string varName) {
	this->varStorage->addVar(varName);
};



 