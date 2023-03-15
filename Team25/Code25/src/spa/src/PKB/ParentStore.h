#pragma once

#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

#include "AbstractionStore.h"

/* Storage class for Parent relationship between two statements.
In Parent(s1, s2), LeftStmt is s1 and RightStmt is s2.*/
class ParentStore : public StmtStmtStore {
private:
  std::unordered_map<int, int> leftStmtStore;
  std::unordered_map<int, std::unordered_set<int>> rightStmtStore;

public:
  ParentStore();
  ParentStore(std::unordered_map<int, int> leftStmtStore,
              std::unordered_map<int, std::unordered_set<int>> rightStmtStore);

  void addParent(int leftStmt, int rightStmt);
  int getLeftStmt(int rightStmt);
  std::unordered_set<int> getRightStmt(int leftStmt);
  bool hasLeftStmt(int lineNum) override;
  bool hasRightStmt(int lineNum) override;
  std::unordered_set<int> getAllLeft() override;
  std::unordered_set<int> getAllRight() override;
};