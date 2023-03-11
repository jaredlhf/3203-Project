#include <iostream>

#include "AttributeStore.h"

/* Print Attribute*/
/*---------------------------------------------------------------------------------------------*/
PrintAttribute::PrintAttribute() : attrStore{}, stmtStore{} {}
PrintAttribute::PrintAttribute(std::unordered_map<int, std::string> attrStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore) 
	: attrStore{ attrStore }, stmtStore{ stmtStore } {}

void PrintAttribute::addAttr(std::string attribute, int lineNum) {
	this->attrStore[lineNum] = attribute;
	this->stmtStore[attribute].emplace(lineNum);
}

std::string PrintAttribute::getAttr(int lineNum) {
	if (hasStmt(lineNum)) {
		return attrStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> PrintAttribute::getStmt(std::string attribute) {
	if (hasAttr(attribute)) {
		return stmtStore[attribute];
	}
	else {
		return {};
	}
}

bool PrintAttribute::hasAttr(std::string attribute) {
	if (stmtStore.find(attribute) != stmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool PrintAttribute::hasStmt(int lineNum) {
	if (attrStore.find(lineNum) != attrStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> PrintAttribute::getAllAttr() {
	std::unordered_set<std::string> attrList;
	for (const auto& [key, value] : attrStore) {
		attrList.insert(value);
	}
	return attrList;
}

std::unordered_set<int> PrintAttribute::getAllStmt() {
	std::unordered_set<int> stmtList;
	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}

/* Read Attribute*/
/*---------------------------------------------------------------------------------------------*/
ReadAttribute::ReadAttribute() : attrStore{}, stmtStore{} {}
ReadAttribute::ReadAttribute(std::unordered_map<int, std::string> attrStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore)
	: attrStore{ attrStore }, stmtStore{ stmtStore } {}

void ReadAttribute::addAttr(std::string attribute, int lineNum) {
	this->attrStore[lineNum] = attribute;
	this->stmtStore[attribute].emplace(lineNum);
}

std::string ReadAttribute::getAttr(int lineNum) {
	if (hasStmt(lineNum)) {
		return attrStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ReadAttribute::getStmt(std::string attribute) {
	if (hasAttr(attribute)) {
		return stmtStore[attribute];
	}
	else {
		return {};
	}
}

bool ReadAttribute::hasAttr(std::string attribute) {
	if (stmtStore.find(attribute) != stmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ReadAttribute::hasStmt(int lineNum) {
	if (attrStore.find(lineNum) != attrStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> ReadAttribute::getAllAttr() {
	std::unordered_set<std::string> attrList;
	for (const auto& [key, value] : attrStore) {
		attrList.insert(value);
	}
	return attrList;
}

std::unordered_set<int> ReadAttribute::getAllStmt() {
	std::unordered_set<int> stmtList;
	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}

/* Call Attribute*/
/*---------------------------------------------------------------------------------------------*/
CallAttribute::CallAttribute() : attrStore{}, stmtStore{} {}
CallAttribute::CallAttribute(std::unordered_map<int, std::string> attrStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore) 
	: attrStore{ attrStore }, stmtStore{ stmtStore } {}

void CallAttribute::addAttr(std::string attribute, int lineNum) {
	this->attrStore[lineNum] = attribute;
	this->stmtStore[attribute].emplace(lineNum);
}

std::string CallAttribute::getAttr(int lineNum) {
	if (hasStmt(lineNum)) {
		return attrStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> CallAttribute::getStmt(std::string attribute) {
	if (hasAttr(attribute)) {
		return stmtStore[attribute];
	}
	else {
		return {};
	}
}

bool CallAttribute::hasAttr(std::string attribute) {
	if (stmtStore.find(attribute) != stmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool CallAttribute::hasStmt(int lineNum) {
	if (attrStore.find(lineNum) != attrStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> CallAttribute::getAllAttr() {
	std::unordered_set<std::string> attrList;
	for (const auto& [key, value] : attrStore) {
		attrList.insert(value);
	}
	return attrList;
}

std::unordered_set<int> CallAttribute::getAllStmt() {
	std::unordered_set<int> stmtList;
	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}