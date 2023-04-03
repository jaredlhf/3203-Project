#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "AbstractionStore.h"

/* Storage class for Next relationship between two statements.
In Next(s1, s2), LeftStmt is s1 and RightStmt is s2.*/
class NextStore : public StmtStmtStore {
private:
	std::unordered_map<int, std::unordered_set<int>> leftStmtStore;
	std::unordered_map<int, std::unordered_set<int>> rightStmtStore;
public:
	NextStore();
	NextStore(std::unordered_map<int, std::unordered_set<int>> leftStmtStore, std::unordered_map<int, std::unordered_set<int>> rightStmtStore);

	void addNext(int leftStmt, int rightStmt);
	std::unordered_set<int> getLeftStmt(int rightStmt);
	std::unordered_set<int> getRightStmt(int leftStmt);
	std::unordered_set<int> getAllLeft() override;
	std::unordered_set<int> getAllRight() override;

	std::unordered_set<int> getRightStmtStar(int leftStmt);
	std::unordered_set<int> getLeftStmtStar(int rightStmt);
};