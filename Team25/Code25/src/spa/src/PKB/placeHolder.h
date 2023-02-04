#pragma once

#include <unordered_set>
#include <string>

class VarStorage {
public:
	VarStorage() {};
	void VarStorage::addVar(std::string varName) {
	};

	std::unordered_set<std::string>* VarStorage::getAllVar() {
		std::unordered_set<std::string>* result{};
		return result;
	};

	bool VarStorage::checkVar(std::string varName) {
		return true;
	};
};