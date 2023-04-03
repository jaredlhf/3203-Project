#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "../SP/CFGNode.h"

class CFGStore {
private:
	std::unordered_map<std::string, std::shared_ptr<CFGNode>> procCfgStore;

public:
	CFGStore();

	void addCFGNode(std::string procName, std::shared_ptr<CFGNode> node);
	std::shared_ptr<CFGNode> getCFGNode(std::string procName);
	std::vector<std::shared_ptr<CFGNode>> getNextNodes(std::shared_ptr<CFGNode> currNode);
};