#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"
#include "placeHolder.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(VarStorage* varStore) {
	this->varStorage = varStore;
};


void PkbPopulator::addVar(std::string varName) {
	this->varStorage->addVar(varName);
};



 