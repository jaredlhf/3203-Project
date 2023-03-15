#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "AbstractionStore.h"

class ModifiesProcStore : public ProcVarStore {
private:
  std::unordered_map<std::string, std::unordered_set<std::string>> procStore;
  std::unordered_map<std::string, std::unordered_set<std::string>> varStore;

public:
  ModifiesProcStore();
  ModifiesProcStore(
      std::unordered_map<std::string, std::unordered_set<std::string>>
          procStore,
      std::unordered_map<std::string, std::unordered_set<std::string>>
          varStore);

  void addModifiesProc(std::string procName, std::string varName);
  std::unordered_set<std::string> getVar(std::string procName) override;
  std::unordered_set<std::string> getProc(std::string varName) override;
  bool hasVar(std::string varName) override;
  bool hasProc(std::string procName) override;
  std::unordered_set<std::string> getAllVar() override;
  std::unordered_set<std::string> getAllProc() override;
};
