#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "AbstractionStore.h"

/* Storage class for Parent* relationship between direct and indirect parents and children 
In Parent*(s1, s2), Parent star is s1 and Children star is s2.*/
class ParentStarStore : public StmtStmtStarStore {
private:
	std::unordered_map<int, std::unordered_set<int>> leftStmtStar;
	std::unordered_map<int, std::unordered_set<int>> rightStmtStar;
public:
	ParentStarStore();
	ParentStarStore(std::unordered_map<int, std::unordered_set<int>> leftStmtStar, std::unordered_map<int, std::unordered_set<int>> rightStmtStar);

	void addParentStar(int leftStmt, int rightStmt);
	std::unordered_set<int> getLeftStar(int rightStmt) override;
	std::unordered_set<int> getRightStar(int leftStmt) override;
	bool hasLeftStmt(int lineNum) override;
	bool hasRightStmt(int lineNum) override;
	std::unordered_set<int> getAllLeft() override;
	std::unordered_set<int> getAllRight() override;
};