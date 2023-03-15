#include <algorithm>
#include <iostream>
#include <stdio.h>

#include "CallsStarStore.h"

CallsStarStore::CallsStarStore() : leftProcStar{}, rightProcStar{} {}

CallsStarStore::CallsStarStore(
    std::unordered_map<std::string, std::unordered_set<std::string>>
        leftProcStar,
    std::unordered_map<std::string, std::unordered_set<std::string>>
        rightProcStar)
    : leftProcStar{leftProcStar}, rightProcStar{rightProcStar} {}

void CallsStarStore::addCallsStar(std::string leftProc, std::string rightProc) {
  rightProcStar[leftProc].emplace(rightProc);
  leftProcStar[rightProc].emplace(leftProc);
}

std::unordered_set<std::string>
CallsStarStore::getLeftStar(std::string rightProc) {
  if (hasRightProc(rightProc)) {
    return leftProcStar[rightProc];
  } else {
    return {};
  }
}

std::unordered_set<std::string>
CallsStarStore::getRightStar(std::string leftProc) {
  if (hasLeftProc(leftProc)) {
    return rightProcStar[leftProc];
  } else {
    return {};
  }
}

bool CallsStarStore::hasLeftProc(std::string procName) {
  if (rightProcStar.find(procName) != rightProcStar.end()) {
    return true;
  } else {
    return false;
  }
}

bool CallsStarStore::hasRightProc(std::string procName) {
  if (leftProcStar.find(procName) != leftProcStar.end()) {
    return true;
  } else {
    return false;
  }
}

std::unordered_set<std::string> CallsStarStore::getAllLeft() {
  std::unordered_set<std::string> leftProcList;
  for (const auto &[key, value] : leftProcStar) {
    leftProcList.insert(value.begin(), value.end());
  }
  return leftProcList;
}

std::unordered_set<std::string> CallsStarStore::getAllRight() {
  std::unordered_set<std::string> rightProcList;
  for (const auto &[key, value] : rightProcStar) {
    rightProcList.insert(value.begin(), value.end());
  }
  return rightProcList;
}
