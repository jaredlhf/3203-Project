#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbRetriever.h"
#include "placeHolder.h"

/*
 * Constructor class for PkbRetriever
 * param: VarStorage* varStore
 */
PkbRetriever::PkbRetriever(VarStorage* varStore) {
	this->varStorage = varStore;
};

std::vector<std::string>* PkbRetriever::getAllVar() {
	return this->varStorage->getAllVar();
}

bool PkbRetriever::checkVar(std::string varName) {
	return this->varStorage->checkVar(varName);
}