#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "AbstractionStore.h"

/* Storage class for Follows relationship between two statements. 
In Follows(s1, s2), LeftStmt is s1 and RightStmt is s2.*/
class FollowsStore : public StmtStmtStore {
private:
	std::unordered_map<int, int> leftStmtStore;
	std::unordered_map<int, int> rightStmtStore;
public:
	FollowsStore();
	FollowsStore(std::unordered_map<int, int> leftStmtStore, std::unordered_map<int, int> rightStmtStore);

	void addFollows(int leftStmt, int rightStmt);
	int getLeftStmt(int rightStmt);
	int getRightStmt(int leftStmt);
	bool hasLeftStmt(int lineNum) override;
	bool hasRightStmt(int lineNum) override;
	std::unordered_set<int> getAllLeft() override;
	std::unordered_set<int> getAllRight() override;
	void clear() override;
};