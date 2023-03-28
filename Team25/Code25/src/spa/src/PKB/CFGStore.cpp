#include<stdio.h>
#include <iostream>

#include "CFGStore.h"

CFGStore::CFGStore() : procCfgStore{} {}

void CFGStore::addCFGNode(std::string procName, std::shared_ptr<CFGNode> node) {
	procCfgStore[procName] = node;
}


std::shared_ptr<CFGNode> CFGStore::getCFGNode(std::string procName) {
	if (procCfgStore.find(procName) != procCfgStore.end()) {
		return procCfgStore[procName];
	}
	else {
		return {};
	}
}

std::vector<std::shared_ptr<CFGNode>> CFGStore::getAllCFGNodes() {
	std::vector<std::shared_ptr<CFGNode>> nodeLst;
	for (const auto& [key, value] : procCfgStore) {
		nodeLst.push_back(value);
	}
	return nodeLst;
}

std::vector<std::shared_ptr<CFGNode>> CFGStore::getNextNodes(std::shared_ptr<CFGNode> currNode) {
	return currNode->getAllNextNodes();
}

std::vector<int> CFGStore::getLineNo(std::shared_ptr<CFGNode> currNode) const {
	return currNode->getLineNo();
}