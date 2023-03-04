#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "AbstractionStore.h"

class CallsStore : public ProcProcStore {
private:
	std::unordered_map<std::string, std::string> leftProcStore;
	std::unordered_map<std::string, std::string> rightProcStore;
public:
	CallsStore();
	CallsStore(std::unordered_map<std::string, std::string> leftProcStore, std::unordered_map<std::string, std::string> rightProcStore);

	void addCalls(std::string leftProc, std::string rightProc);
	std::string getLeftProc(std::string rightProc);
	std::string getRightProc(std::string leftProc);
	bool hasLeftProc(std::string procName) override;
	bool hasRightProc(std::string procName) override;
	std::unordered_set<std::string> getAllLeft() override;
	std::unordered_set<std::string> getAllRight() override;
};