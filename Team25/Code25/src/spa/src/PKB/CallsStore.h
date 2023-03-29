#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "AbstractionStore.h"

class CallsStore : public ProcProcStore {
private:
	std::unordered_map<std::string, std::unordered_set<std::string>> leftProcStore;
	std::unordered_map<std::string, std::unordered_set<std::string>> rightProcStore;
public:
	CallsStore();
	CallsStore(std::unordered_map<std::string, std::unordered_set<std::string>> leftProcStore, std::unordered_map<std::string, std::unordered_set<std::string>> rightProcStore);

	void addCalls(std::string leftProc, std::string rightProc);
	std::unordered_set<std::string> getLeftProc(std::string rightProc);
	std::unordered_set<std::string> getRightProc(std::string leftProc);
	std::unordered_set<std::string> getAllLeft() override;
	std::unordered_set<std::string> getAllRight() override;
};