#include <iostream>

#include "AttributeStore.h"

/* Print Attribute*/
/*---------------------------------------------------------------------------------------------*/
PrintAttribute::PrintAttribute() : attrStore{} {}
PrintAttribute::PrintAttribute(std::unordered_map<int, std::string> attrStore) : attrStore{ attrStore } {}

void PrintAttribute::addAttr(std::string attribute, int lineNum) {
	this->attrStore[lineNum] = attribute;
}

std::string PrintAttribute::getAttr(int lineNum) {
	if (this->attrStore.find(lineNum) != this->attrStore.end()) {
		return this->attrStore[lineNum];
	}
	else {
		return {};
	}
}

/* Read Attribute*/
/*---------------------------------------------------------------------------------------------*/
ReadAttribute::ReadAttribute() : attrStore{} {}
ReadAttribute::ReadAttribute(std::unordered_map<int, std::string> attrStore): attrStore{ attrStore } {}

void ReadAttribute::addAttr(std::string attribute, int lineNum) {
	this->attrStore[lineNum] = attribute;
 
}

std::string ReadAttribute::getAttr(int lineNum) {
	if (this->attrStore.find(lineNum) != this->attrStore.end()) {
		return this->attrStore[lineNum];
	}
	else {
		return {};
	}
}

/* Call Attribute*/
/*---------------------------------------------------------------------------------------------*/
CallAttribute::CallAttribute() : attrStore{} {}
CallAttribute::CallAttribute(std::unordered_map<int, std::string> attrStore) : attrStore{ attrStore } {}

void CallAttribute::addAttr(std::string attribute, int lineNum) {
	this->attrStore[lineNum] = attribute;
 
}

std::string CallAttribute::getAttr(int lineNum) {
	if (this->attrStore.find(lineNum) != this->attrStore.end()) {
		return this->attrStore[lineNum];
	}
	else {
		return {};
	}
}