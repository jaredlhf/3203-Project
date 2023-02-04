#pragma once

#include <vector>
#include <string>

class VarStorage {
public:
	VarStorage() {};
	void VarStorage::addVar(std::string varName) {
	};

	std::vector<std::string>* VarStorage::getAllVar() {
		std::vector<std::string>* result{};
		return result;
	};

	bool VarStorage::checkVar(std::string varName) {
		return true;
	};
};